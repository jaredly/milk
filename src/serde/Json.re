
open Longident;
open Parsetree;
open Ast_helper;
open Asttypes;
open TypeMap;

open Helpers;

let preamble = [];
let makeJson = (kind, contents) => Exp.construct(Location.mknoloc(Ldot(Lident("Json"), kind)), contents);
let jsonObject = items => makeJson("Object", Some(makeList(items)));
let jsonArray = items => makeJson("Array", Some(items));

let sourceTransformer = (~source, ~transformers, ~input) => switch source {
  | DigTypes.NotFound => MakeSerializer.failer("Source not found")
  | Public((moduleName, modulePath, name)) =>
    let ident = makeIdent(Lident(MakeSerializer.transformerName(~moduleName, ~modulePath, ~name)))
    switch transformers {
      | [] => MakeSerializer.maybeCall(ident, input)
      | _ => Exp.apply(ident, {
        let args = transformers->Belt.List.map(expr => (Nolabel, expr));
        switch input {
          | None => args
          | Some(input) => args @ [(Nolabel, input)]
        }
      })
    }
  | Builtin("array") =>
    switch transformers {
      | [tr] =>
        MakeSerializer.withMaybeVariable(
          input,
          value => [%expr Json.Array(
            Belt.List.fromArray(Belt.Array.map([%e value], [%e tr]))
          )]
        )
      | _ => failwith("Array must have an argument transformer")
    }
    // [%expr (transformer, array) => Json.Array(
    //   Belt.List.fromArray(Belt.Array.map(array, transformer))
    // )]
  | Builtin("list") =>
    switch transformers {
      | [tr] =>
        MakeSerializer.withMaybeVariable(
          input,
          value => [%expr
            Json.Array(Belt.List.map([%e value], [%e tr]))
          ]
        )
      | _ => failwith("List must have an argument transformer")
    }
    // [%expr (transformer, list) => Json.Array(Belt.List.map(list, transformer))]
  | Builtin("string") => MakeSerializer.withMaybeVariable(input, value => [%expr Json.String([%e value])])
  | Builtin("bool") => MakeSerializer.withMaybeVariable(input, value => [%expr [%e value] ? Json.True : Json.False])
  | Builtin("int") => MakeSerializer.withMaybeVariable(input, value => [%expr Json.Number(float_of_int([%e value]))])
  | Builtin("float") => MakeSerializer.withMaybeVariable(input, value => [%expr Json.Number([%e value])])
  | Builtin("option") => 
    switch transformers {
      | [tr] => MakeSerializer.withMaybeVariable(input, value => [%expr switch [%e value] {
        | None => Json.Null
        | Some(v) => [%e tr](v)
      }])
      | _ => failwith("List must have an argument transformer")
    }
    // [%expr (transformer) => fun
    // | None => Json.Null
    // | Some(v) => transformer(v)]
  | Builtin(name) => failer("Builtin: " ++ name)
};

let target = [%type: Json.t];

let serializeTransformer =
  MakeSerializer.{
    wrapWithVersion: [%expr
      (version, payload) =>
        switch (payload) {
        | Json.Object(items) =>
          Json.Object(items @ [(schemaPropertyName, Json.Number(float_of_int(version)))])
        | _ => Json.Array([Json.Number(float_of_int(version)), payload])
        }
    ],
    source: sourceTransformer,
    list: jsonArray,
    tuple: exps => makeJson("Array", Some(makeList(exps))),
    record: (~renames, items) => {
      let hasOptionals = items->Belt.List.some(((_, _, isOptional)) => isOptional);
      // jsonObject(
        let items = items->Belt.List.map(((label, expr, isOptional)) =>
        (
          Exp.tuple([
            Exp.constant(Pconst_string(MakeDeserializer.getRename(~renames, label), None)),
            expr,
          ]),
          isOptional
        )
        );
        let contents = items->Belt.List.reduceReverse( 
          Exp.construct(Location.mknoloc(Lident("[]")), None),
          (rest, (expr, isOptional)) => {
            if (isOptional) {
              [%expr {
                let rest = [%e rest];
                switch ([%e expr]) {
                  | (_, Json.Null) => rest
                  | x => [x, ...rest]
                }
              }]
            } else {
              Exp.construct(Location.mknoloc(Lident("::")), Some(Exp.tuple([
                expr, rest
              ])))
            }
          }
         );
         [%expr Json.Object([%e contents])]
      // )
    },
    constructor: (~renames, name, args) =>
      makeJson(
        "Array",
        Some(
          makeList(
            [
              makeJson(
                "String",
                Some(
                  Exp.constant(Pconst_string(MakeDeserializer.getRename(~renames, name), None)),
                ),
              ),
            ]
            @ args,
          ),
        ),
      ),
  };

let declSerializer = MakeSerializer.decl(serializeTransformer);










let sourceTransformer = source => switch source {
  | DigTypes.NotFound => failer("Not found")
  | Public((moduleName, modulePath, name)) =>
    makeIdent(Lident(MakeDeserializer.transformerName(~moduleName, ~modulePath, ~name)))
  | Builtin("array") =>
    [%expr
      (transformer, array) => switch (array) {
        | Json.Array(items) =>
          let rec loop = (collected, items) => switch items {
            | [] => Ok(Belt.List.reverse(collected))
            | [one, ...rest] => switch (transformer(one)) {
              | Error(error) => Error(["array element", ...error])
              | Ok(value) => loop([value, ...collected], rest)
            }
          };
          switch (loop([], items)) {
            | Error(error) => Error(error)
            | Ok(value) => Ok(Belt.List.toArray(value))
          }
        | _ => Error(["expected an array"])
      }
    ];
  | Builtin("list") =>
    [%expr
      (transformer, list) => switch (list) {
        | Json.Array(items) =>
          let rec loop = (collected, items) => switch items {
            | [] => Ok(Belt.List.reverse(collected))
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
      | Json.String(string) => Ok(string)
      | _ => Error(["epected a string"])
    }]
  | Builtin("bool") => [%expr bool => switch (bool) {
    | Json.True => Ok(true)
    | Json.False => Ok(false)
    | _ => Error(["Expected a bool"])
  }]
  | Builtin("int") =>
    [%expr number => switch (number) {
      | Json.Number(number) => Ok(int_of_float(number))
      | _ => Error(["Expected a float"])
    }]
  | Builtin("float") => [%expr number => switch (number) {
    | Json.Number(number) => Ok(number)
    | _ => Error(["Expected a float"])
  }]
  | Builtin("option") =>
    [%expr (transformer, option) => switch (option) {
      | Json.Null => Ok(None)
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


let deserializeTransformer = {
  MakeDeserializer.source: sourceTransformer,
  parseVersion: [%expr
    json => switch json {
      | Json.Object(items) => switch (items->Belt.List.getAssoc(schemaPropertyName, (==))) {
        | Some(Json.Number(schemaVersion)) => [@implicit_arity]Ok((int_of_float(schemaVersion), json))
        | Some(_) => Error("Invalid schema version - expected number")
        | None => Error("No " ++ schemaPropertyName)
      }
      | Json.Array([Json.Number(version), payload]) => [@implicit_arity]Ok((int_of_float(version), payload))
      | _ => Error("Not wrapped in a version")
    }
  ],
  tuple: (value, patArgs, body) => [%expr json => switch ([%e value]) {
    | Json.Array([%p makePatList(patArgs)]) => [%e body]
    | _ => Error(["Expected array"])
  }],
  list: (transformer, list) => {
    [%expr
      switch ([%e list]) {
        | Json.Array(items) =>
          let transformer = [%e transformer];
          let rec loop = (collected, items) => switch items {
            | [] => Ok(Belt.List.reverse(collected))
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
        switch (Belt.List.getAssoc(items, [%e MakeDeserializer.expString(attrName)], (==))) {
        | None =>
          if%e (isOptional) {
            %expr
            inner(None);
          } else {
            %expr
            Error([[%e MakeDeserializer.expString("No attribute '" ++ attrName ++ "'")]]);
          }
        | Some(json) =>
          switch ([%e inner](json)) {
          | Error(error) =>
            Error([[%e MakeDeserializer.expString("attribute '" ++ attrName ++ "'")], ...error])
          | Ok(data) => inner(data)
          }
        };
      };
    });
    [%expr record => switch (record) {
      | Json.Object(items) => [%e body]
      | _ => Error(["Expected an object"])
    }]
  },
  variant: (~renames, constructors) => {

    let cases =
      constructors->Belt.List.map(((name, argCount, argTransformer)) => {
        let constrName = MakeDeserializer.getRename(~renames, name);
        let pat =
          Pat.construct(
            Location.mknoloc(Ldot(Lident("Json"), "Array")),
            Some(
              makePatList([
                [%pat? Json.String([%p Pat.var(Location.mknoloc("tag"))])],
                ...MakeDeserializer.range(argCount, index =>
                     Pat.var(Location.mknoloc("arg" ++ string_of_int(index)))
                   ),
              ]),
            ),
          );
        Exp.case(
          if (argCount == 0) {
            Pat.or_(
              pat,
              [%pat? Json.String(tag)]
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
          Exp.case([%pat? Json.Array([Json.String(tag), ..._])], [%expr Error(["Invalid constructor: " ++ tag])]),
          Exp.case(Pat.any(), MakeDeserializer.expError("Expected an array"))
        ])
      )
    )
  }
};


let declDeserializer = MakeDeserializer.decl(deserializeTransformer);
