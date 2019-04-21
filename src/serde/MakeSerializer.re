
open Longident;
open TypeMap;

let makeLident = (~moduleName, ~modulePath, ~name) => {
  Lident(OutputType.makeLockedTypeName(moduleName, modulePath, name))
};

let transformerName = (~moduleName, ~modulePath, ~name) =>
  "serialize_" ++
  Str.global_replace(
    Str.regexp_string("-"),
    "__",
    moduleName,
  )  ++ "__" ++ String.concat("__", modulePath) ++ "__" ++ name;

open Parsetree;
open Ast_helper;
open Asttypes;
open SharedTypes.SimpleType;

let makeIdent = lident => Exp.ident(Location.mknoloc(lident));
let loc = Location.none;

/**
  Takes a list of attributes
  returns a list of (attrname, ast to transform that attr)
 */
let serializeRecord = (~valueName, attributes, serializeExpr) => {
  let loc = Location.none;
  attributes->Belt.List.map(((label, expr)) => (
    label,
    serializeExpr(~input=Exp.field(makeIdent(Lident(valueName)), Location.mknoloc(Lident(label))), expr)
  ))
};

/**
  Returns an AST of a `switch` to transform the variant
 */
let serializeVariant = (constructors, serializeExpr, makeVariant) => {
  constructors->Belt.List.map(((name, args, _result)) =>
    Exp.case(
      Pat.construct(
        Location.mknoloc(Lident(name)),
        switch (args) {
        | [] => None
        | [_] => Some(Pat.var(Location.mknoloc("arg0")))
        | many =>
          Some(
            Pat.tuple(
              many->Belt.List.mapWithIndex((index, _) =>
                Pat.var(Location.mknoloc("arg" ++ string_of_int(index)))
              ),
            ),
          )
        },
      ),
      makeVariant(
        name,
        args->Belt.List.mapWithIndex((index, arg) =>
          serializeExpr(
            ~input=makeIdent(Lident("arg" ++ string_of_int(index))),
            arg
          ),
        ),
      ),
    )
  );
};

// let serializeExpr

/*
Soooo things we can have:

A serializer takes (a type) and returns (a function that takes that type, along with any typ vbl transformers, and returns the thing in question)

for a record type (with vbls) and 

  type expr('source) =
    | Variable(string)
    | AnonVariable
    | RowVariant(list((string, option(expr('source)))), bool)
    | Reference('source, list(expr('source)))
    | Tuple(list(expr('source)))
    | Fn(list((option(string), expr('source))), expr('source))
    | Other

  type body('source) =
    | Open
    | Abstract
    | Expr(expr('source))
    | Record(list((string, expr('source))))
    | Variant(list((string, list(expr('source)), option(expr('source)))))

*/



let variableTransformerName = name => name ++ "Transformer";

type transformer('source) = {
  wrapWithVersion: Parsetree.expression,
  source: ('source) => Parsetree.expression,
  list: (Parsetree.expression) => Parsetree.expression,
  tuple: (list(Parsetree.expression)) => Parsetree.expression,
  record: (~renames: list((string, string)), list((string, Parsetree.expression))) => Parsetree.expression,
  constructor: (~renames: list((string, string)), string, list(Parsetree.expression)) => Parsetree.expression,
};

// let failer = message => Exp.fun_(Nolabel, None, Pat.any(),
// Exp.apply(Exp.ident(Location.mknoloc(Lident("print_endline"))), [
//   (Nolabel, Exp.constant(Pconst_string(message, None)))
// ]));

let failer = message => failwith("Unserializable: " ++ message);

let rec makeList = items => switch items {
  | [] => Exp.construct(Location.mknoloc(Lident("[]")), None)
  | [one, ...rest] => Exp.construct(Location.mknoloc(Lident("::")), Some(Exp.tuple([
    one, makeList(rest)
  ])))
}

let call = (fn, vbl) => [%expr [%e fn]([%e vbl])];
let maybeCall = (fn, input) => switch input {
  | None => fn
  | Some(input) => call(fn, input)
};
let fnOrLet = (body, input, pattern) => switch input {
  | None => Exp.fun_(Nolabel, None, pattern, body)
  | Some(input) => [%expr {
    let [%p pattern] = [%e input];
    [%e body]
  }]
};

let rec forExpr = (~input, ~renames, transformer, t) => switch t {
  | Variable(string) =>
    let fn = makeIdent(Lident(variableTransformerName(string)));
    maybeCall(fn, input)
  | AnonVariable => failer("Anon variable")
  | Reference(source, args) =>
    switch (source, args) {
      | (DigTypes.Builtin("list"), [arg]) =>
        let name = switch input {
          | Some(i) => i
          | None => [%expr list]
        };
        let body = transformer.list(
          [%expr Belt.List.map([%e name], [%e forExpr(~input=None, ~renames, transformer, arg)])]
        );
        switch input {
          | Some(i) => body
          | None => [%expr list => [%e body]]
        }
      | _ =>
        maybeCall(switch args {
          | [] => transformer.source(source)
          | args => Exp.apply(
            transformer.source(source),
            args->Belt.List.map(arg => (Nolabel, forExpr(~input=None, ~renames, transformer, arg)))
          )
        }, input)
    }
  | Tuple(items) =>
    let rec loop = (i, items) => switch items {
      | [] => ([], [])
      | [arg, ...rest] =>
        let name = "arg" ++ string_of_int(i);
        let (pats, exps) = loop(i + 1, rest);
        ([
          Pat.var(Location.mknoloc(name)),
          ...pats
        ], [
          forExpr(~input=Some(Exp.ident(Location.mknoloc(Lident(name)))), ~renames, transformer, arg),
          ...exps
        ])
    };
    let (pats, exps) = loop(0, items);
    fnOrLet(
      transformer.tuple(exps),
      input,
      Pat.tuple(pats)
    )
  | RowVariant(rows, _closed) =>
  let cases = 
        rows->Belt.List.map(((name, arg)) => {
          Exp.case(
            Pat.variant(
              name,
              switch arg {
                | None => None
                | Some(arg) => Some([%pat? arg])
              }
            ),
            transformer.constructor(
              ~renames, name,
              switch arg {
                | None => []
                | Some(arg) =>
                  [forExpr(~input=Some([%expr arg]), ~renames, transformer, arg)]
              }
            )
          )
        });
    switch input {
      | None => [%expr constructor => [%e Exp.match([%expr constructor], cases)]]
      | Some(input) => Exp.match(input, cases)
    }
    // Exp.fun_(
    //   Nolabel,
    //   None,
    //   Pat.var(Location.mknoloc("constructor")),
    //   Exp.match(
    //     makeIdent(Lident("constructor")),
    //     cases
    //   )
    // )
  | _ => failer("not impl expr")
};

let forBody = (~helpers, ~renames, transformer, body, fullName, variables) => switch body {
  | Open => failer("Cannot transform an open type")
  | Abstract =>
    let moduleName = switch helpers {
      | None => failwith("Abstract type found, but no 'helpers' module specified for this engine")
      | Some(name) => name;
    };
    let body = makeIdent(Ldot(Lident(moduleName), fullName));
    switch (variables) {
      | [] => body
      | args => Exp.apply(body, args->Belt.List.map(
        arg => (Nolabel, makeIdent(Lident(switch arg {
          | Variable(string) => variableTransformerName(string)
          | AnonVariable => "ANON"
          | _ => "OTHER"
        })))
      ))
    }
  | Expr(e) =>
    forExpr(~input=Some([%expr value]), ~renames, transformer, e)
  | Record(items) =>
    [%expr record => [%e transformer.record(~renames, serializeRecord(
      ~valueName="record",
      items,
      (~input, expr) => forExpr(~input=Some(input), ~renames, transformer, expr)
    ))]]
  | Variant(constructors) =>
    [%expr
      constructor => [%e
        Exp.match(
          makeIdent(Lident("constructor")),
          serializeVariant(
            constructors,
            (~input, expr) => forExpr(~input=Some(input), ~renames, transformer, expr),
            transformer.constructor(~renames),
          ),
        )
      ]
    ];
};

let makeTypArgs = variables =>
      variables->Belt.List.mapWithIndex((index, _arg) => {
        "arg" ++ string_of_int(index)
      });

let declInner = (~helpers, ~renames, transformer, {variables, body}, fullName) => {
  let rec loop = vbls => switch vbls {
    | [] => forBody(~helpers, ~renames, transformer, body, fullName, variables)
    | [arg, ...rest] =>
      Exp.fun_(Nolabel, None, Pat.var(Location.mknoloc(
        switch arg {
          | Variable(string) => variableTransformerName(string)
          | AnonVariable => "ANON"
          | _ => "OTHER"
        }
      )), loop(rest))
  };

    loop(variables)
};

let decl = (~helpers, ~renames, transformer, ~moduleName, ~modulePath, ~name, decl) => {
  let lident = makeLident(~moduleName, ~modulePath, ~name);
  let typ = Typ.arrow(
        Nolabel,
        Typ.constr(
          Location.mknoloc(lident),
          decl.variables->makeTypArgs->Belt.List.map(Typ.var)
        ),
        [%type: target]
      );
  let rec loop = (i, vbls) => switch vbls {
    | [] => typ
    | [_, ...rest] => Typ.arrow(
      Nolabel,
      Typ.arrow(Nolabel, Typ.var("arg" ++ string_of_int(i)), [%type: target]),
      loop(i + 1, rest)
    )
  };
  let typ = loop(0, decl.variables);
  let typ = switch (decl.variables) {
    | [] => typ
    | _ => Typ.poly(
      makeTypArgs(decl.variables)->Belt.List.map(Location.mknoloc),
      typ
    )
  };
  let fullName = transformerName(~moduleName, ~modulePath, ~name);

  Vb.mk(
    Pat.constraint_(
      Pat.var(Location.mknoloc(fullName)),
      typ,
    ),
    declInner(~helpers, ~renames, transformer, decl, fullName)
  )
};
