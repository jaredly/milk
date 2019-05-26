
open Longident;
open Parsetree;
open Ast_helper;
open Asttypes;
open TypeMap;

open Helpers;

let preamble = [];

// let makeJson = (kind, contents) => Exp.construct(Location.mknoloc(Ldot(Lident("Ezjsonm"), kind)), contents);
// let jsonObject = items => makeJson("Object", Some(makeList(items)));
// let jsonArray = items => makeJson("Array", Some(items));
let target = [%type:
  [ `Null
  | `Bool(bool)
  | `Float(float)
  | `String(string)
  | `A(list(target))
  | `O(list((string, target))) ]
];

let sourceTransformer = (~source, ~transformers, ~input) => {
  let body = switch source {
// let sourceTransformer = source => switch source {
  | DigTypes.NotFound => MakeSerializer.failer("Not found")
  | Public((moduleName, modulePath, name)) =>
    makeIdent(Lident(MakeSerializer.transformerName(~moduleName, ~modulePath, ~name)))
  | Builtin("array") =>
    [%expr (transformer, array) => `A(
      Array.to_list(Array.map(transformer, array))
    )]
  | Builtin("list") =>
    [%expr (transformer, list) => `A(List.map(transformer, list))]
  | Builtin("string") => [%expr s => `String(s)]
  | Builtin("bool") => [%expr b => `Bool(b)]
  | Builtin("unit") => [%expr b => `Null]
  | Builtin("int") => [%expr i => `Float(float_of_int(i))]
  | Builtin("float") => [%expr f => `Float(f)]
  | Builtin("option") =>  [%expr (transformer) => fun
    | None => `Null
    | Some(v) => transformer(v)]
  | Builtin(name) => failer("Builtin: " ++ name)
};
  switch transformers {
    | [] => MakeSerializer.maybeCall(body, input)
    | tr => MakeSerializer.maybeCall(Exp.apply(body, tr->Belt.List.map(expr => (Nolabel, expr))), input)
  }
};

let serializeTransformer =
  MakeSerializer.{
    wrapWithVersion: [%expr
      (version, payload) =>
        switch (payload) {
        | `O(items) =>
          `O([(schemaPropertyName, `Float(float_of_int(version))), ...items])
        | _ => `A([`Float(float_of_int(version)), payload])
        }
    ],
    source: sourceTransformer,
    list: items => [%expr `A([%e items])],
    tuple: exps => [%expr `A([%e makeList(exps)])],
    record: (~renames, items) =>
      [%expr `O([%e 
        makeList(items->Belt.List.map(((label, expr, _isOptional)) =>
          Exp.tuple([
            Exp.constant(Pconst_string(MakeDeserializer.getRename(~renames, label), None)),
            expr,
          ])
        ))
      ])],
    constructor: (~renames, name, args) =>
      [%expr `A([%e makeList(
            [
              [%expr `String(
                  [%e Exp.constant(Pconst_string(MakeDeserializer.getRename(~renames, name), None))]
                )
              ]
            ]
            @ args,
          )])],
  };

let declSerializer = MakeSerializer.decl(serializeTransformer);

let sourceTransformer = source => switch source {
  | DigTypes.NotFound => failer("Not found")
  | Public((moduleName, modulePath, name)) =>
    makeIdent(Lident(MakeDeserializer.transformerName(~moduleName, ~modulePath, ~name)))
  | Builtin("array") =>
    [%expr
      (transformer, array) => switch (array) {
        | `A(items) =>
          let rec loop = (collected, items) => switch items {
            | [] => Ok(List.rev(collected))
            | [one, ...rest] => switch (transformer(one)) {
              | Error(error) => Error(["array element", ...error])
              | Ok(value) => loop([value, ...collected], rest)
            }
          };
          switch (loop([], items)) {
            | Error(error) => Error(error)
            | Ok(value) => Ok(Array.of_list(value))
          }
        | _ => Error(["expected an array"])
      }
    ];
  | Builtin("list") =>
    [%expr
      (transformer, list) => switch (list) {
        | `A(items) =>
          let rec loop = (collected, items) => switch items {
            | [] => Ok(List.rev(collected))
            | [one, ...rest] => switch (transformer(one)) {
              | Error(error) => Error(["list element", ...error])
              | Ok(value) => loop([value, ...collected], rest)
            }
          };
          loop([], items)
        | _ => Error(["expected an array"])
      }
    ];
  | Builtin("string") =>
    [%expr string => switch (string) {
      | `String(string) => Ok(string)
      | _ => Error(["epected a string"])
    }]
  | Builtin("bool") => [%expr bool => switch (bool) {
    | `Bool(true) => Ok(true)
    | `Bool(false) => Ok(false)
    | _ => Error(["Expected a bool"])
  }]
  | Builtin("int") =>
    [%expr number => switch (number) {
      | `Float(number) => Ok(int_of_float(number))
      | _ => Error(["Expected a float"])
    }]
  | Builtin("float") => [%expr number => switch (number) {
    | `Float(number) => Ok(number)
    | _ => Error(["Expected a float"])
  }]
  | Builtin("option") =>
    [%expr (transformer, option) => switch (option) {
      | `Null => Ok(None)
      | _ => switch (transformer(option)) {
        | Error(error) => Error(["optional value", ...error])
        | Ok(value) => Ok(Some(value))
      }
    }]
  | Builtin(name) => failer("Builtin: " ++ name)
};

let rec makePatList = items => switch items {
  | [] => Pat.construct(Location.mknoloc(Lident("[]")), None)
  | [one, ...rest] => Pat.construct(Location.mknoloc(Lident("::")), Some(Pat.tuple([
    one, makePatList(rest)
  ])))
};


let jsonT = [%type: Ezjsonm.value];

let deserializeTransformer = {
  MakeDeserializer.source: sourceTransformer,
  parseVersion: [%expr
    json => switch json {
      | `O(items) => switch (items |> List.assoc(schemaPropertyName)) {
        | exception Not_found => Error("No " ++ schemaPropertyName)
        | `Float(schemaVersion) => [@implicit_arity]Ok((int_of_float(schemaVersion), json))
        | _ => Error("Invalid " ++ schemaPropertyName ++ " - expected number")
      }
      | `A([`Float(version), payload]) => [@implicit_arity]Ok((int_of_float(version), payload))
      | _ => Error("Not wrapped in a version")
    }
  ],
  tuple: (value, patArgs, body) => [%expr json => switch ([%e value]) {
    | `A([%p makePatList(patArgs)]) => [%e body]
    | _ => Error(["Expected array"])
  }],
  list: (transformer, list) => {
    [%expr
      switch ([%e list]) {
        | `A(items) =>
          let transformer = [%e transformer];
          let rec loop = (collected, items) => switch items {
            | [] => Ok(List.rev(collected))
            | [one, ...rest] => switch (transformer(one)) {
              | Error(error) => Error(["list item", ...error])
              | Ok(value) => loop([value, ...collected], rest)
            }
          };
          loop([], items)
        | _ => Error(["expected an array"])
      }
    ];

  },
  record: (~renames, ~typ, items) =>  {
    let body =
      MakeDeserializer.ok(
        Exp.constraint_(
        Exp.record(
          items->Belt.List.map(((label, _, _)) => (Location.mknoloc(Lident(label)), makeIdent(Lident("attr_" ++ label)))),
          None,
        ),
        typ
        )
      );
    let body = items->Belt.List.reduce(body, (body, (label, inner, isOptional)) => {
      let attrName = MakeDeserializer.getRename(~renames, label);
      let pat = Pat.var(Location.mknoloc("attr_" ++ label));
      {
        let%expr inner = ([%p pat]) => [%e body];
        switch (items |> List.assoc([%e MakeDeserializer.expString(attrName)])) {
        | exception Not_found =>
          if%e (isOptional) {
            %expr
            inner(None);
          } else {
            %expr
            Error([[%e MakeDeserializer.expString("No attribute '" ++ attrName ++ "'")]]);
          }
        | json =>
          switch ([%e inner](json)) {
          | Error(error) =>
            Error([[%e MakeDeserializer.expString("attribute '" ++ attrName ++ "'")], ...error])
          | Ok(data) => inner(data)
          }
        };
      };
    });
    [%expr record => switch (record) {
      | `O(items) => [%e body]
      | _ => Error(["Expected an object"])
    }]
  },
  variant: (~renames, constructors) => {

    let cases =
      constructors->Belt.List.map(((name, argCount, argTransformer)) => {
        let constrName = MakeDeserializer.getRename(~renames, name);
        let pat =
          [%pat? `A([%p
              makePatList([
                [%pat? `String([%p Pat.var(Location.mknoloc("tag"))])],
                ...MakeDeserializer.range(argCount, index =>
                     Pat.var(Location.mknoloc("arg" ++ string_of_int(index)))
                   ),
              ])
          ])];
        Exp.case(
          if (argCount == 0) {
            Pat.or_(
              pat,
              [%pat? `String(tag)]
            )
          } else { pat },
          ~guard=
            Exp.apply(
              makeIdent(Lident("=")),
              [
                (
                  Nolabel,
                  Exp.constant(Pconst_string(constrName, None)),
                ),
                (Nolabel, makeIdent(Lident("tag"))),
              ],
            ),
          argTransformer,
        );
      });

    Exp.fun_(
      Nolabel,
      None,
      Pat.var(Location.mknoloc("constructor")),
      Exp.match(
        makeIdent(Lident("constructor")),
        cases->Belt.List.concat([
          Exp.case([%pat? `A([`String(tag), ..._])], [%expr Error(["Invalid constructor: " ++ tag])]),
          Exp.case(Pat.any(), MakeDeserializer.expError("Expected an array"))
        ])
      )
    )
  }
};


let declDeserializer = MakeDeserializer.decl(deserializeTransformer);
