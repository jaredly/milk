[@ocaml.warning "-34"];
module Types1 = {
  type _Analyze__TopTypes__moduleName = string
  and _Asttypes__loc('a) =
    Asttypes.loc('a) = {
      txt: 'a,
      loc: _Location__t,
    }
  and _Location__t =
    Location.t = {
      loc_start: _Stdlib__lexing__position,
      loc_end: _Stdlib__lexing__position,
      loc_ghost: bool,
    }
  and _Parsetree__attribute = (_Asttypes__loc(string), _Parsetree__payload)
  and _Parsetree__attributes = list(_Parsetree__attribute)
  and _Parsetree__core_type = Parsetree.core_type
  and _Parsetree__expression = Parsetree.expression
  and _Parsetree__pattern = Parsetree.pattern
  and _Parsetree__payload =
    Parsetree.payload =
      | PStr(_Parsetree__structure)
      | PSig(_Parsetree__signature)
      | PTyp(_Parsetree__core_type)
      | PPat(_Parsetree__pattern, option(_Parsetree__expression))
  and _Parsetree__signature = Parsetree.signature
  and _Parsetree__structure = Parsetree.structure
  and _SharedTypes__SimpleType__body('source) =
    SharedTypes.SimpleType.body('source) =
      | Open
      | Abstract
      | Expr(_SharedTypes__SimpleType__expr('source))
      | Record(list((string, _SharedTypes__SimpleType__expr('source))))
      | Variant(
          list(
            (
              string,
              list(_SharedTypes__SimpleType__expr('source)),
              option(_SharedTypes__SimpleType__expr('source)),
            ),
          ),
        )
  and _SharedTypes__SimpleType__declaration('source) =
    SharedTypes.SimpleType.declaration('source) = {
      name: string,
      variables: list(_SharedTypes__SimpleType__expr('source)),
      body: _SharedTypes__SimpleType__body('source),
    }
  and _SharedTypes__SimpleType__expr('source) =
    SharedTypes.SimpleType.expr('source) =
      | Variable(string)
      | AnonVariable
      | RowVariant(
          list((string, option(_SharedTypes__SimpleType__expr('source)))),
          bool,
        )
      | Reference('source, list(_SharedTypes__SimpleType__expr('source)))
      | Tuple(list(_SharedTypes__SimpleType__expr('source)))
      | Fn(
          list((option(string), _SharedTypes__SimpleType__expr('source))),
          _SharedTypes__SimpleType__expr('source),
        )
      | Other
  and _Stdlib__hashtbl__t('a, 'b) = Stdlib__hashtbl.t('a, 'b)
  and _Stdlib__lexing__position =
    Stdlib__lexing.position = {
      pos_fname: string,
      pos_lnum: int,
      pos_bol: int,
      pos_cnum: int,
    }
  and _TypeMapSerde__Config__custom =
    TypeMapSerde__Config.custom = {
      module_: string,
      path: list(string),
      name: string,
      args: option(int),
    }
  and _TypeMapSerde__Config__engine =
    TypeMapSerde__Config.engine = | Rex_json | Bs_json | Ezjsonm | Yojson
  and _TypeMapSerde__Config__engineConfig =
    TypeMapSerde__Config.engineConfig = {
      output: string,
      helpers: option(string),
      options: option(_TypeMapSerde__Config__engineOptions),
    }
  and _TypeMapSerde__Config__engineOptions =
    TypeMapSerde__Config.engineOptions = {
      tailCall: bool,
      deserializeErrorMode: _TypeMapSerde__Config__errorMode,
    }
  and _TypeMapSerde__Config__engines =
    TypeMapSerde__Config.engines = {
      rex_json: option(_TypeMapSerde__Config__engineConfig),
      bs_json: option(_TypeMapSerde__Config__engineConfig),
      ezjsonm: option(_TypeMapSerde__Config__engineConfig),
      yojson: option(_TypeMapSerde__Config__engineConfig),
    }
  and _TypeMapSerde__Config__entry =
    TypeMapSerde__Config.entry = {
      file: string,
      type_: string,
      engines: option(list(_TypeMapSerde__Config__engine)),
      publicName: option(string),
      history: option(bool),
      minVersion: option(int),
    }
  and _TypeMapSerde__Config__errorMode =
    TypeMapSerde__Config.errorMode =
      | Result | TrackedExceptions | PlainExceptions
  and _TypeMapSerde__Config__serializableLockfile =
    _TypeMapSerde__Config__Locked__lockfile(
      _TypeMap__DigTypes__shortReference,
    )
  and _TypeMapSerde__Config__simpleDeclaration =
    _SharedTypes__SimpleType__declaration(
      _TypeMap__DigTypes__typeSource(_TypeMap__DigTypes__shortReference),
    )
  and _TypeMapSerde__Config__simpleExpr =
    _SharedTypes__SimpleType__expr(
      _TypeMap__DigTypes__typeSource(_TypeMap__DigTypes__shortReference),
    )
  and _TypeMapSerde__Config__t =
    TypeMapSerde__Config.t = {
      version: int,
      schemaPropertyName: option(string),
      minVersion: option(int),
      lockedTypes: option(string),
      engines: _TypeMapSerde__Config__engines,
      globalEngines: option(list(_TypeMapSerde__Config__engine)),
      entries: list(_TypeMapSerde__Config__entry),
      custom: list(_TypeMapSerde__Config__custom),
    }
  and _TypeMapSerde__Config__Locked__lockedConfig('reference) =
    TypeMapSerde__Config.Locked.lockedConfig('reference) = {
      entries: list(_TypeMapSerde__Config__Locked__lockedEntry),
      typeMap: _TypeMap__DigTypes__typeMap('reference),
    }
  and _TypeMapSerde__Config__Locked__lockedEntry =
    TypeMapSerde__Config.Locked.lockedEntry = {
      moduleName: string,
      modulePath: list(string),
      engines: list((_TypeMapSerde__Config__engine, int)),
      name: string,
    }
  and _TypeMapSerde__Config__Locked__lockfile('reference) =
    TypeMapSerde__Config.Locked.lockfile('reference) = {
      versions:
        array(_TypeMapSerde__Config__Locked__lockedConfig('reference)),
    }
  and _TypeMap__DigTypes__shortReference = (
    _Analyze__TopTypes__moduleName,
    list(string),
    string,
  )
  and _TypeMap__DigTypes__typeMap('reference) =
    _Stdlib__hashtbl__t(
      _TypeMap__DigTypes__shortReference,
      (
        _Parsetree__attributes,
        _SharedTypes__SimpleType__declaration(
          _TypeMap__DigTypes__typeSource('reference),
        ),
      ),
    )
  and _TypeMap__DigTypes__typeSource('reference) =
    TypeMap__DigTypes.typeSource('reference) =
      | Builtin(string) | Public('reference) | NotFound;
};
let currentVersion = 1;
type target = Json.t;
let schemaPropertyName = "milkSchemaVersion";
module Version1 = {
  open Types1;
  let rec deserialize_Analyze__TopTypes____moduleName:
    target => result(_Analyze__TopTypes__moduleName, list(string)) =
    value =>
      (
        string =>
          switch (string) {
          | Json.String(string) => Ok(string)
          | _ => Error(["epected a string"])
          }
      )(
        value,
      )
  and deserialize_Asttypes____loc:
    type arg0.
      (target => result(arg0, list(string)), target) =>
      result(_Asttypes__loc(arg0), list(string)) =
    (aTransformer, record) =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_loc => {
          let inner = attr_txt =>
            Ok({txt: attr_txt, loc: attr_loc}: _Asttypes__loc(arg0));
          switch (Belt.List.getAssoc(items, "txt", (==))) {
          | None => Error(["No attribute 'txt'"])
          | Some(json) =>
            switch (aTransformer(json)) {
            | Error(error) => Error(["attribute 'txt'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "loc", (==))) {
        | None => Error(["No attribute 'loc'"])
        | Some(json) =>
          switch (deserialize_Location____t(json)) {
          | Error(error) => Error(["attribute 'loc'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Error(["Expected an object"])
      }

  and deserialize_Location____t: target => result(_Location__t, list(string)) =
    record =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_loc_ghost => {
          let inner = attr_loc_end => {
            let inner = attr_loc_start =>
              Ok(
                {
                  loc_start: attr_loc_start,
                  loc_end: attr_loc_end,
                  loc_ghost: attr_loc_ghost,
                }: _Location__t,
              );
            switch (Belt.List.getAssoc(items, "loc_start", (==))) {
            | None => Error(["No attribute 'loc_start'"])
            | Some(json) =>
              switch (deserialize_Stdlib__lexing____position(json)) {
              | Error(error) => Error(["attribute 'loc_start'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Belt.List.getAssoc(items, "loc_end", (==))) {
          | None => Error(["No attribute 'loc_end'"])
          | Some(json) =>
            switch (deserialize_Stdlib__lexing____position(json)) {
            | Error(error) => Error(["attribute 'loc_end'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "loc_ghost", (==))) {
        | None => Error(["No attribute 'loc_ghost'"])
        | Some(json) =>
          switch (
            (
              bool =>
                switch (bool) {
                | Json.True => Ok(true)
                | Json.False => Ok(false)
                | _ => Error(["Expected a bool"])
                }
            )(
              json,
            )
          ) {
          | Error(error) => Error(["attribute 'loc_ghost'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Error(["Expected an object"])
      }
  and deserialize_Parsetree____attribute:
    target => result(_Parsetree__attribute, list(string)) =
    value =>
      (
        json =>
          switch (json) {
          | Json.Array([arg0, arg1]) =>
            switch (deserialize_Parsetree____payload(arg1)) {
            | Belt.Result.Ok(arg1) =>
              switch (
                (
                  deserialize_Asttypes____loc(string =>
                    switch (string) {
                    | Json.String(string) => Ok(string)
                    | _ => Error(["epected a string"])
                    }
                  )
                )(
                  arg0,
                )
              ) {
              | Belt.Result.Ok(arg0) => Ok((arg0, arg1))
              | Error(error) => Error(["tuple element 0", ...error])
              }
            | Error(error) => Error(["tuple element 1", ...error])
            }
          | _ => Error(["Expected array"])
          }
      )(
        value,
      )
  and deserialize_Parsetree____attributes:
    target => result(_Parsetree__attributes, list(string)) =
    value =>
      (
        list =>
          switch (list) {
          | Json.Array(items) =>
            let transformer = deserialize_Parsetree____attribute;
            let rec loop = (collected, items) =>
              switch (items) {
              | [] => Ok(Belt.List.reverse(collected))
              | [one, ...rest] =>
                switch (transformer(one)) {
                | Error(error) => Error(["list item", ...error])
                | Ok(value) => loop([value, ...collected], rest)
                }
              };
            loop([], items);
          | _ => Error(["expected an array"])
          }
      )(
        value,
      )
  and deserialize_Parsetree____core_type:
    target => result(_Parsetree__core_type, list(string)) = TransformHelpers.deserialize_Parsetree____core_type
  and deserialize_Parsetree____expression:
    target => result(_Parsetree__expression, list(string)) = TransformHelpers.deserialize_Parsetree____expression
  and deserialize_Parsetree____pattern:
    target => result(_Parsetree__pattern, list(string)) = TransformHelpers.deserialize_Parsetree____pattern
  and deserialize_Parsetree____payload:
    target => result(_Parsetree__payload, list(string)) =
    constructor =>
      switch (constructor) {
      | Json.Array([Json.String(tag), arg0]) when "PStr" == tag =>
        switch (deserialize_Parsetree____structure(arg0)) {
        | Belt.Result.Ok(arg0) => Ok(PStr(arg0): _Parsetree__payload)
        | Error(error) => Error(["constructor argument 0", ...error])
        }
      | Json.Array([Json.String(tag), arg0]) when "PSig" == tag =>
        switch (deserialize_Parsetree____signature(arg0)) {
        | Belt.Result.Ok(arg0) => Ok(PSig(arg0): _Parsetree__payload)
        | Error(error) => Error(["constructor argument 0", ...error])
        }
      | Json.Array([Json.String(tag), arg0]) when "PTyp" == tag =>
        switch (deserialize_Parsetree____core_type(arg0)) {
        | Belt.Result.Ok(arg0) => Ok(PTyp(arg0): _Parsetree__payload)
        | Error(error) => Error(["constructor argument 0", ...error])
        }
      | Json.Array([Json.String(tag), arg0, arg1]) when "PPat" == tag =>
        switch (
          (
            (
              (transformer, option) =>
                switch (option) {
                | Json.Null => Ok(None)
                | _ =>
                  switch (transformer(option)) {
                  | Error(error) => Error(["optional value", ...error])
                  | Ok(value) => Ok(Some(value))
                  }
                }
            )(
              deserialize_Parsetree____expression,
            )
          )(
            arg1,
          )
        ) {
        | Belt.Result.Ok(arg1) =>
          switch (deserialize_Parsetree____pattern(arg0)) {
          | Belt.Result.Ok(arg0) =>
            Ok([@implicit_arity] PPat(arg0, arg1): _Parsetree__payload)
          | Error(error) => Error(["constructor argument 0", ...error])
          }
        | Error(error) => Error(["constructor argument 1", ...error])
        }
      | Json.Array([Json.String(tag), ..._]) =>
        Error(["Invalid constructor: " ++ tag])
      | _ => Error(["Expected an array"])
      }
  and deserialize_Parsetree____signature:
    target => result(_Parsetree__signature, list(string)) = TransformHelpers.deserialize_Parsetree____signature
  and deserialize_Parsetree____structure:
    target => result(_Parsetree__structure, list(string)) = TransformHelpers.deserialize_Parsetree____structure
  and deserialize_SharedTypes__SimpleType__body:
    type arg0.
      (target => result(arg0, list(string)), target) =>
      result(_SharedTypes__SimpleType__body(arg0), list(string)) =
    (sourceTransformer, constructor) =>
      switch (constructor) {
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "Open" == tag =>
        Ok(Open: _SharedTypes__SimpleType__body(arg0))
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "Abstract" == tag =>
        Ok(Abstract: _SharedTypes__SimpleType__body(arg0))
      | Json.Array([Json.String(tag), arg0]) when "Expr" == tag =>
        switch (
          (deserialize_SharedTypes__SimpleType__expr(sourceTransformer))(
            arg0,
          )
        ) {
        | Belt.Result.Ok(arg0) =>
          Ok(Expr(arg0): _SharedTypes__SimpleType__body(arg0))
        | Error(error) => Error(["constructor argument 0", ...error])
        }
      | Json.Array([Json.String(tag), arg0]) when "Record" == tag =>
        switch (
          (
            list =>
              switch (list) {
              | Json.Array(items) =>
                let transformer = json =>
                  switch (json) {
                  | Json.Array([arg0, arg1]) =>
                    switch (
                      (
                        deserialize_SharedTypes__SimpleType__expr(
                          sourceTransformer,
                        )
                      )(
                        arg1,
                      )
                    ) {
                    | Belt.Result.Ok(arg1) =>
                      switch (
                        (
                          string =>
                            switch (string) {
                            | Json.String(string) => Ok(string)
                            | _ => Error(["epected a string"])
                            }
                        )(
                          arg0,
                        )
                      ) {
                      | Belt.Result.Ok(arg0) => Ok((arg0, arg1))
                      | Error(error) => Error(["tuple element 0", ...error])
                      }
                    | Error(error) => Error(["tuple element 1", ...error])
                    }
                  | _ => Error(["Expected array"])
                  };
                let rec loop = (collected, items) =>
                  switch (items) {
                  | [] => Ok(Belt.List.reverse(collected))
                  | [one, ...rest] =>
                    switch (transformer(one)) {
                    | Error(error) => Error(["list item", ...error])
                    | Ok(value) => loop([value, ...collected], rest)
                    }
                  };
                loop([], items);
              | _ => Error(["expected an array"])
              }
          )(
            arg0,
          )
        ) {
        | Belt.Result.Ok(arg0) =>
          Ok(Record(arg0): _SharedTypes__SimpleType__body(arg0))
        | Error(error) => Error(["constructor argument 0", ...error])
        }
      | Json.Array([Json.String(tag), arg0]) when "Variant" == tag =>
        switch (
          (
            list =>
              switch (list) {
              | Json.Array(items) =>
                let transformer = json =>
                  switch (json) {
                  | Json.Array([arg0, arg1, arg2]) =>
                    switch (
                      (
                        (
                          (transformer, option) =>
                            switch (option) {
                            | Json.Null => Ok(None)
                            | _ =>
                              switch (transformer(option)) {
                              | Error(error) =>
                                Error(["optional value", ...error])
                              | Ok(value) => Ok(Some(value))
                              }
                            }
                        )(
                          deserialize_SharedTypes__SimpleType__expr(
                            sourceTransformer,
                          ),
                        )
                      )(
                        arg2,
                      )
                    ) {
                    | Belt.Result.Ok(arg2) =>
                      switch (
                        (
                          list =>
                            switch (list) {
                            | Json.Array(items) =>
                              let transformer =
                                deserialize_SharedTypes__SimpleType__expr(
                                  sourceTransformer,
                                );
                              let rec loop = (collected, items) =>
                                switch (items) {
                                | [] => Ok(Belt.List.reverse(collected))
                                | [one, ...rest] =>
                                  switch (transformer(one)) {
                                  | Error(error) =>
                                    Error(["list item", ...error])
                                  | Ok(value) =>
                                    loop([value, ...collected], rest)
                                  }
                                };
                              loop([], items);
                            | _ => Error(["expected an array"])
                            }
                        )(
                          arg1,
                        )
                      ) {
                      | Belt.Result.Ok(arg1) =>
                        switch (
                          (
                            string =>
                              switch (string) {
                              | Json.String(string) => Ok(string)
                              | _ => Error(["epected a string"])
                              }
                          )(
                            arg0,
                          )
                        ) {
                        | Belt.Result.Ok(arg0) => Ok((arg0, arg1, arg2))
                        | Error(error) =>
                          Error(["tuple element 0", ...error])
                        }
                      | Error(error) => Error(["tuple element 1", ...error])
                      }
                    | Error(error) => Error(["tuple element 2", ...error])
                    }
                  | _ => Error(["Expected array"])
                  };
                let rec loop = (collected, items) =>
                  switch (items) {
                  | [] => Ok(Belt.List.reverse(collected))
                  | [one, ...rest] =>
                    switch (transformer(one)) {
                    | Error(error) => Error(["list item", ...error])
                    | Ok(value) => loop([value, ...collected], rest)
                    }
                  };
                loop([], items);
              | _ => Error(["expected an array"])
              }
          )(
            arg0,
          )
        ) {
        | Belt.Result.Ok(arg0) =>
          Ok(Variant(arg0): _SharedTypes__SimpleType__body(arg0))
        | Error(error) => Error(["constructor argument 0", ...error])
        }
      | Json.Array([Json.String(tag), ..._]) =>
        Error(["Invalid constructor: " ++ tag])
      | _ => Error(["Expected an array"])
      }

  and deserialize_SharedTypes__SimpleType__declaration:
    type arg0.
      (target => result(arg0, list(string)), target) =>
      result(_SharedTypes__SimpleType__declaration(arg0), list(string)) =
    (sourceTransformer, record) =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_body => {
          let inner = attr_variables => {
            let inner = attr_name =>
              Ok(
                {name: attr_name, variables: attr_variables, body: attr_body}:
                                                                    _SharedTypes__SimpleType__declaration(
                                                                    arg0,
                                                                    ),
              );
            switch (Belt.List.getAssoc(items, "name", (==))) {
            | None => Error(["No attribute 'name'"])
            | Some(json) =>
              switch (
                (
                  string =>
                    switch (string) {
                    | Json.String(string) => Ok(string)
                    | _ => Error(["epected a string"])
                    }
                )(
                  json,
                )
              ) {
              | Error(error) => Error(["attribute 'name'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Belt.List.getAssoc(items, "variables", (==))) {
          | None => Error(["No attribute 'variables'"])
          | Some(json) =>
            switch (
              (
                list =>
                  switch (list) {
                  | Json.Array(items) =>
                    let transformer =
                      deserialize_SharedTypes__SimpleType__expr(
                        sourceTransformer,
                      );
                    let rec loop = (collected, items) =>
                      switch (items) {
                      | [] => Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Error(error) => Error(["list item", ...error])
                        | Ok(value) => loop([value, ...collected], rest)
                        }
                      };
                    loop([], items);
                  | _ => Error(["expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Error(error) => Error(["attribute 'variables'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "body", (==))) {
        | None => Error(["No attribute 'body'"])
        | Some(json) =>
          switch (
            (deserialize_SharedTypes__SimpleType__body(sourceTransformer))(
              json,
            )
          ) {
          | Error(error) => Error(["attribute 'body'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Error(["Expected an object"])
      }

  and deserialize_SharedTypes__SimpleType__expr:
    type arg0.
      (target => result(arg0, list(string)), target) =>
      result(_SharedTypes__SimpleType__expr(arg0), list(string)) =
    (sourceTransformer, constructor) =>
      switch (constructor) {
      | Json.Array([Json.String(tag), arg0]) when "Variable" == tag =>
        switch (
          (
            string =>
              switch (string) {
              | Json.String(string) => Ok(string)
              | _ => Error(["epected a string"])
              }
          )(
            arg0,
          )
        ) {
        | Belt.Result.Ok(arg0) =>
          Ok(Variable(arg0): _SharedTypes__SimpleType__expr(arg0))
        | Error(error) => Error(["constructor argument 0", ...error])
        }
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "AnonVariable" == tag =>
        Ok(AnonVariable: _SharedTypes__SimpleType__expr(arg0))
      | Json.Array([Json.String(tag), arg0, arg1]) when "RowVariant" == tag =>
        switch (
          (
            bool =>
              switch (bool) {
              | Json.True => Ok(true)
              | Json.False => Ok(false)
              | _ => Error(["Expected a bool"])
              }
          )(
            arg1,
          )
        ) {
        | Belt.Result.Ok(arg1) =>
          switch (
            (
              list =>
                switch (list) {
                | Json.Array(items) =>
                  let transformer = json =>
                    switch (json) {
                    | Json.Array([arg0, arg1]) =>
                      switch (
                        (
                          (
                            (transformer, option) =>
                              switch (option) {
                              | Json.Null => Ok(None)
                              | _ =>
                                switch (transformer(option)) {
                                | Error(error) =>
                                  Error(["optional value", ...error])
                                | Ok(value) => Ok(Some(value))
                                }
                              }
                          )(
                            deserialize_SharedTypes__SimpleType__expr(
                              sourceTransformer,
                            ),
                          )
                        )(
                          arg1,
                        )
                      ) {
                      | Belt.Result.Ok(arg1) =>
                        switch (
                          (
                            string =>
                              switch (string) {
                              | Json.String(string) => Ok(string)
                              | _ => Error(["epected a string"])
                              }
                          )(
                            arg0,
                          )
                        ) {
                        | Belt.Result.Ok(arg0) => Ok((arg0, arg1))
                        | Error(error) =>
                          Error(["tuple element 0", ...error])
                        }
                      | Error(error) => Error(["tuple element 1", ...error])
                      }
                    | _ => Error(["Expected array"])
                    };
                  let rec loop = (collected, items) =>
                    switch (items) {
                    | [] => Ok(Belt.List.reverse(collected))
                    | [one, ...rest] =>
                      switch (transformer(one)) {
                      | Error(error) => Error(["list item", ...error])
                      | Ok(value) => loop([value, ...collected], rest)
                      }
                    };
                  loop([], items);
                | _ => Error(["expected an array"])
                }
            )(
              arg0,
            )
          ) {
          | Belt.Result.Ok(arg0) =>
            Ok(
              [@implicit_arity] RowVariant(arg0, arg1):
                                                         _SharedTypes__SimpleType__expr(
                                                           arg0,
                                                         ),
            )
          | Error(error) => Error(["constructor argument 0", ...error])
          }
        | Error(error) => Error(["constructor argument 1", ...error])
        }
      | Json.Array([Json.String(tag), arg0, arg1]) when "Reference" == tag =>
        switch (
          (
            list =>
              switch (list) {
              | Json.Array(items) =>
                let transformer =
                  deserialize_SharedTypes__SimpleType__expr(
                    sourceTransformer,
                  );
                let rec loop = (collected, items) =>
                  switch (items) {
                  | [] => Ok(Belt.List.reverse(collected))
                  | [one, ...rest] =>
                    switch (transformer(one)) {
                    | Error(error) => Error(["list item", ...error])
                    | Ok(value) => loop([value, ...collected], rest)
                    }
                  };
                loop([], items);
              | _ => Error(["expected an array"])
              }
          )(
            arg1,
          )
        ) {
        | Belt.Result.Ok(arg1) =>
          switch (sourceTransformer(arg0)) {
          | Belt.Result.Ok(arg0) =>
            Ok(
              [@implicit_arity] Reference(arg0, arg1):
                                                        _SharedTypes__SimpleType__expr(
                                                          arg0,
                                                        ),
            )
          | Error(error) => Error(["constructor argument 0", ...error])
          }
        | Error(error) => Error(["constructor argument 1", ...error])
        }
      | Json.Array([Json.String(tag), arg0]) when "Tuple" == tag =>
        switch (
          (
            list =>
              switch (list) {
              | Json.Array(items) =>
                let transformer =
                  deserialize_SharedTypes__SimpleType__expr(
                    sourceTransformer,
                  );
                let rec loop = (collected, items) =>
                  switch (items) {
                  | [] => Ok(Belt.List.reverse(collected))
                  | [one, ...rest] =>
                    switch (transformer(one)) {
                    | Error(error) => Error(["list item", ...error])
                    | Ok(value) => loop([value, ...collected], rest)
                    }
                  };
                loop([], items);
              | _ => Error(["expected an array"])
              }
          )(
            arg0,
          )
        ) {
        | Belt.Result.Ok(arg0) =>
          Ok(Tuple(arg0): _SharedTypes__SimpleType__expr(arg0))
        | Error(error) => Error(["constructor argument 0", ...error])
        }
      | Json.Array([Json.String(tag), arg0, arg1]) when "Fn" == tag =>
        switch (
          (deserialize_SharedTypes__SimpleType__expr(sourceTransformer))(
            arg1,
          )
        ) {
        | Belt.Result.Ok(arg1) =>
          switch (
            (
              list =>
                switch (list) {
                | Json.Array(items) =>
                  let transformer = json =>
                    switch (json) {
                    | Json.Array([arg0, arg1]) =>
                      switch (
                        (
                          deserialize_SharedTypes__SimpleType__expr(
                            sourceTransformer,
                          )
                        )(
                          arg1,
                        )
                      ) {
                      | Belt.Result.Ok(arg1) =>
                        switch (
                          (
                            (
                              (transformer, option) =>
                                switch (option) {
                                | Json.Null => Ok(None)
                                | _ =>
                                  switch (transformer(option)) {
                                  | Error(error) =>
                                    Error(["optional value", ...error])
                                  | Ok(value) => Ok(Some(value))
                                  }
                                }
                            )(
                              string =>
                              switch (string) {
                              | Json.String(string) => Ok(string)
                              | _ => Error(["epected a string"])
                              }
                            )
                          )(
                            arg0,
                          )
                        ) {
                        | Belt.Result.Ok(arg0) => Ok((arg0, arg1))
                        | Error(error) =>
                          Error(["tuple element 0", ...error])
                        }
                      | Error(error) => Error(["tuple element 1", ...error])
                      }
                    | _ => Error(["Expected array"])
                    };
                  let rec loop = (collected, items) =>
                    switch (items) {
                    | [] => Ok(Belt.List.reverse(collected))
                    | [one, ...rest] =>
                      switch (transformer(one)) {
                      | Error(error) => Error(["list item", ...error])
                      | Ok(value) => loop([value, ...collected], rest)
                      }
                    };
                  loop([], items);
                | _ => Error(["expected an array"])
                }
            )(
              arg0,
            )
          ) {
          | Belt.Result.Ok(arg0) =>
            Ok(
              [@implicit_arity] Fn(arg0, arg1):
                                                 _SharedTypes__SimpleType__expr(
                                                   arg0,
                                                 ),
            )
          | Error(error) => Error(["constructor argument 0", ...error])
          }
        | Error(error) => Error(["constructor argument 1", ...error])
        }
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "Other" == tag =>
        Ok(Other: _SharedTypes__SimpleType__expr(arg0))
      | Json.Array([Json.String(tag), ..._]) =>
        Error(["Invalid constructor: " ++ tag])
      | _ => Error(["Expected an array"])
      }

  and deserialize_Stdlib__hashtbl____t:
    'arg0 'arg1.
    (
      target => result('arg0, list(string)),
      target => result('arg1, list(string)),
      target
    ) =>
    result(_Stdlib__hashtbl__t('arg0, 'arg1), list(string))
   =
    (type arg1, type arg0) => (
      (aTransformer, bTransformer) =>
        TransformHelpers.deserialize_Stdlib__hashtbl____t(
          aTransformer,
          bTransformer,
        ):
        (
          target => result(arg0, list(string)),
          target => result(arg1, list(string)),
          target
        ) =>
        result(_Stdlib__hashtbl__t(arg0, arg1), list(string))
    )
  and deserialize_Stdlib__lexing____position:
    target => result(_Stdlib__lexing__position, list(string)) =
    record =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_pos_cnum => {
          let inner = attr_pos_bol => {
            let inner = attr_pos_lnum => {
              let inner = attr_pos_fname =>
                Ok(
                  {
                    pos_fname: attr_pos_fname,
                    pos_lnum: attr_pos_lnum,
                    pos_bol: attr_pos_bol,
                    pos_cnum: attr_pos_cnum,
                  }: _Stdlib__lexing__position,
                );
              switch (Belt.List.getAssoc(items, "pos_fname", (==))) {
              | None => Error(["No attribute 'pos_fname'"])
              | Some(json) =>
                switch (
                  (
                    string =>
                      switch (string) {
                      | Json.String(string) => Ok(string)
                      | _ => Error(["epected a string"])
                      }
                  )(
                    json,
                  )
                ) {
                | Error(error) => Error(["attribute 'pos_fname'", ...error])
                | Ok(data) => inner(data)
                }
              };
            };
            switch (Belt.List.getAssoc(items, "pos_lnum", (==))) {
            | None => Error(["No attribute 'pos_lnum'"])
            | Some(json) =>
              switch (
                (
                  number =>
                    switch (number) {
                    | Json.Number(number) => Ok(int_of_float(number))
                    | _ => Error(["Expected a float"])
                    }
                )(
                  json,
                )
              ) {
              | Error(error) => Error(["attribute 'pos_lnum'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Belt.List.getAssoc(items, "pos_bol", (==))) {
          | None => Error(["No attribute 'pos_bol'"])
          | Some(json) =>
            switch (
              (
                number =>
                  switch (number) {
                  | Json.Number(number) => Ok(int_of_float(number))
                  | _ => Error(["Expected a float"])
                  }
              )(
                json,
              )
            ) {
            | Error(error) => Error(["attribute 'pos_bol'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "pos_cnum", (==))) {
        | None => Error(["No attribute 'pos_cnum'"])
        | Some(json) =>
          switch (
            (
              number =>
                switch (number) {
                | Json.Number(number) => Ok(int_of_float(number))
                | _ => Error(["Expected a float"])
                }
            )(
              json,
            )
          ) {
          | Error(error) => Error(["attribute 'pos_cnum'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Error(["Expected an object"])
      }
  and deserialize_TypeMapSerde__Config____custom:
    target => result(_TypeMapSerde__Config__custom, list(string)) =
    record =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_args => {
          let inner = attr_name => {
            let inner = attr_path => {
              let inner = attr_module_ =>
                Ok(
                  {
                    module_: attr_module_,
                    path: attr_path,
                    name: attr_name,
                    args: attr_args,
                  }: _TypeMapSerde__Config__custom,
                );
              switch (Belt.List.getAssoc(items, "module", (==))) {
              | None => Error(["No attribute 'module'"])
              | Some(json) =>
                switch (
                  (
                    string =>
                      switch (string) {
                      | Json.String(string) => Ok(string)
                      | _ => Error(["epected a string"])
                      }
                  )(
                    json,
                  )
                ) {
                | Error(error) => Error(["attribute 'module'", ...error])
                | Ok(data) => inner(data)
                }
              };
            };
            switch (Belt.List.getAssoc(items, "path", (==))) {
            | None => Error(["No attribute 'path'"])
            | Some(json) =>
              switch (
                (
                  list =>
                    switch (list) {
                    | Json.Array(items) =>
                      let transformer = string =>
                        switch (string) {
                        | Json.String(string) => Ok(string)
                        | _ => Error(["epected a string"])
                        };
                      let rec loop = (collected, items) =>
                        switch (items) {
                        | [] => Ok(Belt.List.reverse(collected))
                        | [one, ...rest] =>
                          switch (transformer(one)) {
                          | Error(error) => Error(["list item", ...error])
                          | Ok(value) => loop([value, ...collected], rest)
                          }
                        };
                      loop([], items);
                    | _ => Error(["expected an array"])
                    }
                )(
                  json,
                )
              ) {
              | Error(error) => Error(["attribute 'path'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Belt.List.getAssoc(items, "name", (==))) {
          | None => Error(["No attribute 'name'"])
          | Some(json) =>
            switch (
              (
                string =>
                  switch (string) {
                  | Json.String(string) => Ok(string)
                  | _ => Error(["epected a string"])
                  }
              )(
                json,
              )
            ) {
            | Error(error) => Error(["attribute 'name'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "args", (==))) {
        | None => inner(None)
        | Some(json) =>
          switch (
            (
              (
                (transformer, option) =>
                  switch (option) {
                  | Json.Null => Ok(None)
                  | _ =>
                    switch (transformer(option)) {
                    | Error(error) => Error(["optional value", ...error])
                    | Ok(value) => Ok(Some(value))
                    }
                  }
              )(
                number =>
                switch (number) {
                | Json.Number(number) => Ok(int_of_float(number))
                | _ => Error(["Expected a float"])
                }
              )
            )(
              json,
            )
          ) {
          | Error(error) => Error(["attribute 'args'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Error(["Expected an object"])
      }
  and deserialize_TypeMapSerde__Config____engine:
    target => result(_TypeMapSerde__Config__engine, list(string)) =
    constructor =>
      switch (constructor) {
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "rex-json" == tag =>
        Ok(Rex_json: _TypeMapSerde__Config__engine)
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "Js.Json" == tag =>
        Ok(Bs_json: _TypeMapSerde__Config__engine)
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "ezjsonm" == tag =>
        Ok(Ezjsonm: _TypeMapSerde__Config__engine)
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "yojson" == tag =>
        Ok(Yojson: _TypeMapSerde__Config__engine)
      | Json.Array([Json.String(tag), ..._]) =>
        Error(["Invalid constructor: " ++ tag])
      | _ => Error(["Expected an array"])
      }
  and deserialize_TypeMapSerde__Config____engineConfig:
    target => result(_TypeMapSerde__Config__engineConfig, list(string)) =
    record =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_options => {
          let inner = attr_helpers => {
            let inner = attr_output =>
              Ok(
                {
                  output: attr_output,
                  helpers: attr_helpers,
                  options: attr_options,
                }: _TypeMapSerde__Config__engineConfig,
              );
            switch (Belt.List.getAssoc(items, "output", (==))) {
            | None => Error(["No attribute 'output'"])
            | Some(json) =>
              switch (
                (
                  string =>
                    switch (string) {
                    | Json.String(string) => Ok(string)
                    | _ => Error(["epected a string"])
                    }
                )(
                  json,
                )
              ) {
              | Error(error) => Error(["attribute 'output'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Belt.List.getAssoc(items, "helpers", (==))) {
          | None => inner(None)
          | Some(json) =>
            switch (
              (
                (
                  (transformer, option) =>
                    switch (option) {
                    | Json.Null => Ok(None)
                    | _ =>
                      switch (transformer(option)) {
                      | Error(error) => Error(["optional value", ...error])
                      | Ok(value) => Ok(Some(value))
                      }
                    }
                )(
                  string =>
                  switch (string) {
                  | Json.String(string) => Ok(string)
                  | _ => Error(["epected a string"])
                  }
                )
              )(
                json,
              )
            ) {
            | Error(error) => Error(["attribute 'helpers'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "options", (==))) {
        | None => inner(None)
        | Some(json) =>
          switch (
            (
              (
                (transformer, option) =>
                  switch (option) {
                  | Json.Null => Ok(None)
                  | _ =>
                    switch (transformer(option)) {
                    | Error(error) => Error(["optional value", ...error])
                    | Ok(value) => Ok(Some(value))
                    }
                  }
              )(
                deserialize_TypeMapSerde__Config____engineOptions,
              )
            )(
              json,
            )
          ) {
          | Error(error) => Error(["attribute 'options'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Error(["Expected an object"])
      }
  and deserialize_TypeMapSerde__Config____engineOptions:
    target => result(_TypeMapSerde__Config__engineOptions, list(string)) =
    record =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_deserializeErrorMode => {
          let inner = attr_tailCall =>
            Ok(
              {
                tailCall: attr_tailCall,
                deserializeErrorMode: attr_deserializeErrorMode,
              }: _TypeMapSerde__Config__engineOptions,
            );
          switch (Belt.List.getAssoc(items, "tailCall", (==))) {
          | None => Error(["No attribute 'tailCall'"])
          | Some(json) =>
            switch (
              (
                bool =>
                  switch (bool) {
                  | Json.True => Ok(true)
                  | Json.False => Ok(false)
                  | _ => Error(["Expected a bool"])
                  }
              )(
                json,
              )
            ) {
            | Error(error) => Error(["attribute 'tailCall'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "deserializeErrorMode", (==))) {
        | None => Error(["No attribute 'deserializeErrorMode'"])
        | Some(json) =>
          switch (deserialize_TypeMapSerde__Config____errorMode(json)) {
          | Error(error) =>
            Error(["attribute 'deserializeErrorMode'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Error(["Expected an object"])
      }
  and deserialize_TypeMapSerde__Config____engines:
    target => result(_TypeMapSerde__Config__engines, list(string)) =
    record =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_yojson => {
          let inner = attr_ezjsonm => {
            let inner = attr_bs_json => {
              let inner = attr_rex_json =>
                Ok(
                  {
                    rex_json: attr_rex_json,
                    bs_json: attr_bs_json,
                    ezjsonm: attr_ezjsonm,
                    yojson: attr_yojson,
                  }: _TypeMapSerde__Config__engines,
                );
              switch (Belt.List.getAssoc(items, "rex-json", (==))) {
              | None => inner(None)
              | Some(json) =>
                switch (
                  (
                    (
                      (transformer, option) =>
                        switch (option) {
                        | Json.Null => Ok(None)
                        | _ =>
                          switch (transformer(option)) {
                          | Error(error) =>
                            Error(["optional value", ...error])
                          | Ok(value) => Ok(Some(value))
                          }
                        }
                    )(
                      deserialize_TypeMapSerde__Config____engineConfig,
                    )
                  )(
                    json,
                  )
                ) {
                | Error(error) => Error(["attribute 'rex-json'", ...error])
                | Ok(data) => inner(data)
                }
              };
            };
            switch (Belt.List.getAssoc(items, "Js.Json", (==))) {
            | None => inner(None)
            | Some(json) =>
              switch (
                (
                  (
                    (transformer, option) =>
                      switch (option) {
                      | Json.Null => Ok(None)
                      | _ =>
                        switch (transformer(option)) {
                        | Error(error) => Error(["optional value", ...error])
                        | Ok(value) => Ok(Some(value))
                        }
                      }
                  )(
                    deserialize_TypeMapSerde__Config____engineConfig,
                  )
                )(
                  json,
                )
              ) {
              | Error(error) => Error(["attribute 'Js.Json'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Belt.List.getAssoc(items, "ezjsonm", (==))) {
          | None => inner(None)
          | Some(json) =>
            switch (
              (
                (
                  (transformer, option) =>
                    switch (option) {
                    | Json.Null => Ok(None)
                    | _ =>
                      switch (transformer(option)) {
                      | Error(error) => Error(["optional value", ...error])
                      | Ok(value) => Ok(Some(value))
                      }
                    }
                )(
                  deserialize_TypeMapSerde__Config____engineConfig,
                )
              )(
                json,
              )
            ) {
            | Error(error) => Error(["attribute 'ezjsonm'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "yojson", (==))) {
        | None => inner(None)
        | Some(json) =>
          switch (
            (
              (
                (transformer, option) =>
                  switch (option) {
                  | Json.Null => Ok(None)
                  | _ =>
                    switch (transformer(option)) {
                    | Error(error) => Error(["optional value", ...error])
                    | Ok(value) => Ok(Some(value))
                    }
                  }
              )(
                deserialize_TypeMapSerde__Config____engineConfig,
              )
            )(
              json,
            )
          ) {
          | Error(error) => Error(["attribute 'yojson'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Error(["Expected an object"])
      }
  and deserialize_TypeMapSerde__Config____entry:
    target => result(_TypeMapSerde__Config__entry, list(string)) =
    record =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_minVersion => {
          let inner = attr_history => {
            let inner = attr_publicName => {
              let inner = attr_engines => {
                let inner = attr_type_ => {
                  let inner = attr_file =>
                    Ok(
                      {
                        file: attr_file,
                        type_: attr_type_,
                        engines: attr_engines,
                        publicName: attr_publicName,
                        history: attr_history,
                        minVersion: attr_minVersion,
                      }: _TypeMapSerde__Config__entry,
                    );
                  switch (Belt.List.getAssoc(items, "file", (==))) {
                  | None => Error(["No attribute 'file'"])
                  | Some(json) =>
                    switch (
                      (
                        string =>
                          switch (string) {
                          | Json.String(string) => Ok(string)
                          | _ => Error(["epected a string"])
                          }
                      )(
                        json,
                      )
                    ) {
                    | Error(error) => Error(["attribute 'file'", ...error])
                    | Ok(data) => inner(data)
                    }
                  };
                };
                switch (Belt.List.getAssoc(items, "type", (==))) {
                | None => Error(["No attribute 'type'"])
                | Some(json) =>
                  switch (
                    (
                      string =>
                        switch (string) {
                        | Json.String(string) => Ok(string)
                        | _ => Error(["epected a string"])
                        }
                    )(
                      json,
                    )
                  ) {
                  | Error(error) => Error(["attribute 'type'", ...error])
                  | Ok(data) => inner(data)
                  }
                };
              };
              switch (Belt.List.getAssoc(items, "engines", (==))) {
              | None => inner(None)
              | Some(json) =>
                switch (
                  (
                    (
                      (transformer, option) =>
                        switch (option) {
                        | Json.Null => Ok(None)
                        | _ =>
                          switch (transformer(option)) {
                          | Error(error) =>
                            Error(["optional value", ...error])
                          | Ok(value) => Ok(Some(value))
                          }
                        }
                    )(
                      list =>
                      switch (list) {
                      | Json.Array(items) =>
                        let transformer = deserialize_TypeMapSerde__Config____engine;
                        let rec loop = (collected, items) =>
                          switch (items) {
                          | [] => Ok(Belt.List.reverse(collected))
                          | [one, ...rest] =>
                            switch (transformer(one)) {
                            | Error(error) => Error(["list item", ...error])
                            | Ok(value) => loop([value, ...collected], rest)
                            }
                          };
                        loop([], items);
                      | _ => Error(["expected an array"])
                      }
                    )
                  )(
                    json,
                  )
                ) {
                | Error(error) => Error(["attribute 'engines'", ...error])
                | Ok(data) => inner(data)
                }
              };
            };
            switch (Belt.List.getAssoc(items, "publicName", (==))) {
            | None => inner(None)
            | Some(json) =>
              switch (
                (
                  (
                    (transformer, option) =>
                      switch (option) {
                      | Json.Null => Ok(None)
                      | _ =>
                        switch (transformer(option)) {
                        | Error(error) => Error(["optional value", ...error])
                        | Ok(value) => Ok(Some(value))
                        }
                      }
                  )(
                    string =>
                    switch (string) {
                    | Json.String(string) => Ok(string)
                    | _ => Error(["epected a string"])
                    }
                  )
                )(
                  json,
                )
              ) {
              | Error(error) => Error(["attribute 'publicName'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Belt.List.getAssoc(items, "history", (==))) {
          | None => inner(None)
          | Some(json) =>
            switch (
              (
                (
                  (transformer, option) =>
                    switch (option) {
                    | Json.Null => Ok(None)
                    | _ =>
                      switch (transformer(option)) {
                      | Error(error) => Error(["optional value", ...error])
                      | Ok(value) => Ok(Some(value))
                      }
                    }
                )(
                  bool =>
                  switch (bool) {
                  | Json.True => Ok(true)
                  | Json.False => Ok(false)
                  | _ => Error(["Expected a bool"])
                  }
                )
              )(
                json,
              )
            ) {
            | Error(error) => Error(["attribute 'history'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "minVersion", (==))) {
        | None => inner(None)
        | Some(json) =>
          switch (
            (
              (
                (transformer, option) =>
                  switch (option) {
                  | Json.Null => Ok(None)
                  | _ =>
                    switch (transformer(option)) {
                    | Error(error) => Error(["optional value", ...error])
                    | Ok(value) => Ok(Some(value))
                    }
                  }
              )(
                number =>
                switch (number) {
                | Json.Number(number) => Ok(int_of_float(number))
                | _ => Error(["Expected a float"])
                }
              )
            )(
              json,
            )
          ) {
          | Error(error) => Error(["attribute 'minVersion'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Error(["Expected an object"])
      }
  and deserialize_TypeMapSerde__Config____errorMode:
    target => result(_TypeMapSerde__Config__errorMode, list(string)) =
    constructor =>
      switch (constructor) {
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "Result" == tag =>
        Ok(Result: _TypeMapSerde__Config__errorMode)
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "TrackedExceptions" == tag =>
        Ok(TrackedExceptions: _TypeMapSerde__Config__errorMode)
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "PlainExceptions" == tag =>
        Ok(PlainExceptions: _TypeMapSerde__Config__errorMode)
      | Json.Array([Json.String(tag), ..._]) =>
        Error(["Invalid constructor: " ++ tag])
      | _ => Error(["Expected an array"])
      }
  and deserialize_TypeMapSerde__Config____serializableLockfile:
    target =>
    result(_TypeMapSerde__Config__serializableLockfile, list(string)) =
    value =>
      (
        deserialize_TypeMapSerde__Config__Locked__lockfile(
          deserialize_TypeMap__DigTypes____shortReference,
        )
      )(
        value,
      )
  and deserialize_TypeMapSerde__Config____simpleDeclaration:
    target => result(_TypeMapSerde__Config__simpleDeclaration, list(string)) =
    value =>
      (
        deserialize_SharedTypes__SimpleType__declaration(
          deserialize_TypeMap__DigTypes____typeSource(
            deserialize_TypeMap__DigTypes____shortReference,
          ),
        )
      )(
        value,
      )
  and deserialize_TypeMapSerde__Config____simpleExpr:
    target => result(_TypeMapSerde__Config__simpleExpr, list(string)) =
    value =>
      (
        deserialize_SharedTypes__SimpleType__expr(
          deserialize_TypeMap__DigTypes____typeSource(
            deserialize_TypeMap__DigTypes____shortReference,
          ),
        )
      )(
        value,
      )
  and deserialize_TypeMapSerde__Config____t:
    target => result(_TypeMapSerde__Config__t, list(string)) =
    record =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_custom => {
          let inner = attr_entries => {
            let inner = attr_globalEngines => {
              let inner = attr_engines => {
                let inner = attr_lockedTypes => {
                  let inner = attr_minVersion => {
                    let inner = attr_schemaPropertyName => {
                      let inner = attr_version =>
                        Ok(
                          {
                            version: attr_version,
                            schemaPropertyName: attr_schemaPropertyName,
                            minVersion: attr_minVersion,
                            lockedTypes: attr_lockedTypes,
                            engines: attr_engines,
                            globalEngines: attr_globalEngines,
                            entries: attr_entries,
                            custom: attr_custom,
                          }: _TypeMapSerde__Config__t,
                        );
                      switch (Belt.List.getAssoc(items, "version", (==))) {
                      | None => Error(["No attribute 'version'"])
                      | Some(json) =>
                        switch (
                          (
                            number =>
                              switch (number) {
                              | Json.Number(number) =>
                                Ok(int_of_float(number))
                              | _ => Error(["Expected a float"])
                              }
                          )(
                            json,
                          )
                        ) {
                        | Error(error) =>
                          Error(["attribute 'version'", ...error])
                        | Ok(data) => inner(data)
                        }
                      };
                    };
                    switch (
                      Belt.List.getAssoc(items, "schemaPropertyName", (==))
                    ) {
                    | None => inner(None)
                    | Some(json) =>
                      switch (
                        (
                          (
                            (transformer, option) =>
                              switch (option) {
                              | Json.Null => Ok(None)
                              | _ =>
                                switch (transformer(option)) {
                                | Error(error) =>
                                  Error(["optional value", ...error])
                                | Ok(value) => Ok(Some(value))
                                }
                              }
                          )(
                            string =>
                            switch (string) {
                            | Json.String(string) => Ok(string)
                            | _ => Error(["epected a string"])
                            }
                          )
                        )(
                          json,
                        )
                      ) {
                      | Error(error) =>
                        Error(["attribute 'schemaPropertyName'", ...error])
                      | Ok(data) => inner(data)
                      }
                    };
                  };
                  switch (Belt.List.getAssoc(items, "minVersion", (==))) {
                  | None => inner(None)
                  | Some(json) =>
                    switch (
                      (
                        (
                          (transformer, option) =>
                            switch (option) {
                            | Json.Null => Ok(None)
                            | _ =>
                              switch (transformer(option)) {
                              | Error(error) =>
                                Error(["optional value", ...error])
                              | Ok(value) => Ok(Some(value))
                              }
                            }
                        )(
                          number =>
                          switch (number) {
                          | Json.Number(number) => Ok(int_of_float(number))
                          | _ => Error(["Expected a float"])
                          }
                        )
                      )(
                        json,
                      )
                    ) {
                    | Error(error) =>
                      Error(["attribute 'minVersion'", ...error])
                    | Ok(data) => inner(data)
                    }
                  };
                };
                switch (Belt.List.getAssoc(items, "lockedTypes", (==))) {
                | None => inner(None)
                | Some(json) =>
                  switch (
                    (
                      (
                        (transformer, option) =>
                          switch (option) {
                          | Json.Null => Ok(None)
                          | _ =>
                            switch (transformer(option)) {
                            | Error(error) =>
                              Error(["optional value", ...error])
                            | Ok(value) => Ok(Some(value))
                            }
                          }
                      )(
                        string =>
                        switch (string) {
                        | Json.String(string) => Ok(string)
                        | _ => Error(["epected a string"])
                        }
                      )
                    )(
                      json,
                    )
                  ) {
                  | Error(error) =>
                    Error(["attribute 'lockedTypes'", ...error])
                  | Ok(data) => inner(data)
                  }
                };
              };
              switch (Belt.List.getAssoc(items, "engines", (==))) {
              | None => Error(["No attribute 'engines'"])
              | Some(json) =>
                switch (deserialize_TypeMapSerde__Config____engines(json)) {
                | Error(error) => Error(["attribute 'engines'", ...error])
                | Ok(data) => inner(data)
                }
              };
            };
            switch (Belt.List.getAssoc(items, "globalEngines", (==))) {
            | None => inner(None)
            | Some(json) =>
              switch (
                (
                  (
                    (transformer, option) =>
                      switch (option) {
                      | Json.Null => Ok(None)
                      | _ =>
                        switch (transformer(option)) {
                        | Error(error) => Error(["optional value", ...error])
                        | Ok(value) => Ok(Some(value))
                        }
                      }
                  )(
                    list =>
                    switch (list) {
                    | Json.Array(items) =>
                      let transformer = deserialize_TypeMapSerde__Config____engine;
                      let rec loop = (collected, items) =>
                        switch (items) {
                        | [] => Ok(Belt.List.reverse(collected))
                        | [one, ...rest] =>
                          switch (transformer(one)) {
                          | Error(error) => Error(["list item", ...error])
                          | Ok(value) => loop([value, ...collected], rest)
                          }
                        };
                      loop([], items);
                    | _ => Error(["expected an array"])
                    }
                  )
                )(
                  json,
                )
              ) {
              | Error(error) =>
                Error(["attribute 'globalEngines'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Belt.List.getAssoc(items, "entries", (==))) {
          | None => Error(["No attribute 'entries'"])
          | Some(json) =>
            switch (
              (
                list =>
                  switch (list) {
                  | Json.Array(items) =>
                    let transformer = deserialize_TypeMapSerde__Config____entry;
                    let rec loop = (collected, items) =>
                      switch (items) {
                      | [] => Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Error(error) => Error(["list item", ...error])
                        | Ok(value) => loop([value, ...collected], rest)
                        }
                      };
                    loop([], items);
                  | _ => Error(["expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Error(error) => Error(["attribute 'entries'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "custom", (==))) {
        | None => Error(["No attribute 'custom'"])
        | Some(json) =>
          switch (
            (
              list =>
                switch (list) {
                | Json.Array(items) =>
                  let transformer = deserialize_TypeMapSerde__Config____custom;
                  let rec loop = (collected, items) =>
                    switch (items) {
                    | [] => Ok(Belt.List.reverse(collected))
                    | [one, ...rest] =>
                      switch (transformer(one)) {
                      | Error(error) => Error(["list item", ...error])
                      | Ok(value) => loop([value, ...collected], rest)
                      }
                    };
                  loop([], items);
                | _ => Error(["expected an array"])
                }
            )(
              json,
            )
          ) {
          | Error(error) => Error(["attribute 'custom'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Error(["Expected an object"])
      }
  and deserialize_TypeMapSerde__Config__Locked__lockedConfig:
    type arg0.
      (target => result(arg0, list(string)), target) =>
      result(
        _TypeMapSerde__Config__Locked__lockedConfig(arg0),
        list(string),
      ) =
    (referenceTransformer, record) =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_typeMap => {
          let inner = attr_entries =>
            Ok(
              {entries: attr_entries, typeMap: attr_typeMap}:
                                                               _TypeMapSerde__Config__Locked__lockedConfig(
                                                                 arg0,
                                                               ),
            );
          switch (Belt.List.getAssoc(items, "entries", (==))) {
          | None => Error(["No attribute 'entries'"])
          | Some(json) =>
            switch (
              (
                list =>
                  switch (list) {
                  | Json.Array(items) =>
                    let transformer = deserialize_TypeMapSerde__Config__Locked__lockedEntry;
                    let rec loop = (collected, items) =>
                      switch (items) {
                      | [] => Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Error(error) => Error(["list item", ...error])
                        | Ok(value) => loop([value, ...collected], rest)
                        }
                      };
                    loop([], items);
                  | _ => Error(["expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Error(error) => Error(["attribute 'entries'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "typeMap", (==))) {
        | None => Error(["No attribute 'typeMap'"])
        | Some(json) =>
          switch (
            (deserialize_TypeMap__DigTypes____typeMap(referenceTransformer))(
              json,
            )
          ) {
          | Error(error) => Error(["attribute 'typeMap'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Error(["Expected an object"])
      }

  and deserialize_TypeMapSerde__Config__Locked__lockedEntry:
    target =>
    result(_TypeMapSerde__Config__Locked__lockedEntry, list(string)) =
    record =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_name => {
          let inner = attr_engines => {
            let inner = attr_modulePath => {
              let inner = attr_moduleName =>
                Ok(
                  {
                    moduleName: attr_moduleName,
                    modulePath: attr_modulePath,
                    engines: attr_engines,
                    name: attr_name,
                  }: _TypeMapSerde__Config__Locked__lockedEntry,
                );
              switch (Belt.List.getAssoc(items, "moduleName", (==))) {
              | None => Error(["No attribute 'moduleName'"])
              | Some(json) =>
                switch (
                  (
                    string =>
                      switch (string) {
                      | Json.String(string) => Ok(string)
                      | _ => Error(["epected a string"])
                      }
                  )(
                    json,
                  )
                ) {
                | Error(error) => Error(["attribute 'moduleName'", ...error])
                | Ok(data) => inner(data)
                }
              };
            };
            switch (Belt.List.getAssoc(items, "modulePath", (==))) {
            | None => Error(["No attribute 'modulePath'"])
            | Some(json) =>
              switch (
                (
                  list =>
                    switch (list) {
                    | Json.Array(items) =>
                      let transformer = string =>
                        switch (string) {
                        | Json.String(string) => Ok(string)
                        | _ => Error(["epected a string"])
                        };
                      let rec loop = (collected, items) =>
                        switch (items) {
                        | [] => Ok(Belt.List.reverse(collected))
                        | [one, ...rest] =>
                          switch (transformer(one)) {
                          | Error(error) => Error(["list item", ...error])
                          | Ok(value) => loop([value, ...collected], rest)
                          }
                        };
                      loop([], items);
                    | _ => Error(["expected an array"])
                    }
                )(
                  json,
                )
              ) {
              | Error(error) => Error(["attribute 'modulePath'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Belt.List.getAssoc(items, "engines", (==))) {
          | None => Error(["No attribute 'engines'"])
          | Some(json) =>
            switch (
              (
                list =>
                  switch (list) {
                  | Json.Array(items) =>
                    let transformer = json =>
                      switch (json) {
                      | Json.Array([arg0, arg1]) =>
                        switch (
                          (
                            number =>
                              switch (number) {
                              | Json.Number(number) =>
                                Ok(int_of_float(number))
                              | _ => Error(["Expected a float"])
                              }
                          )(
                            arg1,
                          )
                        ) {
                        | Belt.Result.Ok(arg1) =>
                          switch (
                            deserialize_TypeMapSerde__Config____engine(arg0)
                          ) {
                          | Belt.Result.Ok(arg0) => Ok((arg0, arg1))
                          | Error(error) =>
                            Error(["tuple element 0", ...error])
                          }
                        | Error(error) =>
                          Error(["tuple element 1", ...error])
                        }
                      | _ => Error(["Expected array"])
                      };
                    let rec loop = (collected, items) =>
                      switch (items) {
                      | [] => Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Error(error) => Error(["list item", ...error])
                        | Ok(value) => loop([value, ...collected], rest)
                        }
                      };
                    loop([], items);
                  | _ => Error(["expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Error(error) => Error(["attribute 'engines'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "name", (==))) {
        | None => Error(["No attribute 'name'"])
        | Some(json) =>
          switch (
            (
              string =>
                switch (string) {
                | Json.String(string) => Ok(string)
                | _ => Error(["epected a string"])
                }
            )(
              json,
            )
          ) {
          | Error(error) => Error(["attribute 'name'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Error(["Expected an object"])
      }
  and deserialize_TypeMapSerde__Config__Locked__lockfile:
    type arg0.
      (target => result(arg0, list(string)), target) =>
      result(_TypeMapSerde__Config__Locked__lockfile(arg0), list(string)) =
    (referenceTransformer, record) =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_versions =>
          Ok(
            {versions: attr_versions}:
                                        _TypeMapSerde__Config__Locked__lockfile(
                                          arg0,
                                        ),
          );
        switch (Belt.List.getAssoc(items, "versions", (==))) {
        | None => Error(["No attribute 'versions'"])
        | Some(json) =>
          switch (
            (
              (
                (transformer, array) =>
                  switch (array) {
                  | Json.Array(items) =>
                    let rec loop = (collected, items) =>
                      switch (items) {
                      | [] => Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Error(error) => Error(["array element", ...error])
                        | Ok(value) => loop([value, ...collected], rest)
                        }
                      };
                    switch (loop([], items)) {
                    | Error(error) => Error(error)
                    | Ok(value) => Ok(Belt.List.toArray(value))
                    };
                  | _ => Error(["expected an array"])
                  }
              )(
                deserialize_TypeMapSerde__Config__Locked__lockedConfig(
                  referenceTransformer,
                ),
              )
            )(
              json,
            )
          ) {
          | Error(error) => Error(["attribute 'versions'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Error(["Expected an object"])
      }

  and deserialize_TypeMap__DigTypes____shortReference:
    target => result(_TypeMap__DigTypes__shortReference, list(string)) =
    value =>
      (
        json =>
          switch (json) {
          | Json.Array([arg0, arg1, arg2]) =>
            switch (
              (
                string =>
                  switch (string) {
                  | Json.String(string) => Ok(string)
                  | _ => Error(["epected a string"])
                  }
              )(
                arg2,
              )
            ) {
            | Belt.Result.Ok(arg2) =>
              switch (
                (
                  list =>
                    switch (list) {
                    | Json.Array(items) =>
                      let transformer = string =>
                        switch (string) {
                        | Json.String(string) => Ok(string)
                        | _ => Error(["epected a string"])
                        };
                      let rec loop = (collected, items) =>
                        switch (items) {
                        | [] => Ok(Belt.List.reverse(collected))
                        | [one, ...rest] =>
                          switch (transformer(one)) {
                          | Error(error) => Error(["list item", ...error])
                          | Ok(value) => loop([value, ...collected], rest)
                          }
                        };
                      loop([], items);
                    | _ => Error(["expected an array"])
                    }
                )(
                  arg1,
                )
              ) {
              | Belt.Result.Ok(arg1) =>
                switch (deserialize_Analyze__TopTypes____moduleName(arg0)) {
                | Belt.Result.Ok(arg0) => Ok((arg0, arg1, arg2))
                | Error(error) => Error(["tuple element 0", ...error])
                }
              | Error(error) => Error(["tuple element 1", ...error])
              }
            | Error(error) => Error(["tuple element 2", ...error])
            }
          | _ => Error(["Expected array"])
          }
      )(
        value,
      )
  and deserialize_TypeMap__DigTypes____typeMap:
    type arg0.
      (target => result(arg0, list(string)), target) =>
      result(_TypeMap__DigTypes__typeMap(arg0), list(string)) =
    (referenceTransformer, value) =>
      (
        deserialize_Stdlib__hashtbl____t(
          deserialize_TypeMap__DigTypes____shortReference, json =>
          switch (json) {
          | Json.Array([arg0, arg1]) =>
            switch (
              (
                deserialize_SharedTypes__SimpleType__declaration(
                  deserialize_TypeMap__DigTypes____typeSource(
                    referenceTransformer,
                  ),
                )
              )(
                arg1,
              )
            ) {
            | Belt.Result.Ok(arg1) =>
              switch (deserialize_Parsetree____attributes(arg0)) {
              | Belt.Result.Ok(arg0) => Ok((arg0, arg1))
              | Error(error) => Error(["tuple element 0", ...error])
              }
            | Error(error) => Error(["tuple element 1", ...error])
            }
          | _ => Error(["Expected array"])
          }
        )
      )(
        value,
      )

  and deserialize_TypeMap__DigTypes____typeSource:
    type arg0.
      (target => result(arg0, list(string)), target) =>
      result(_TypeMap__DigTypes__typeSource(arg0), list(string)) =
    (referenceTransformer, constructor) =>
      switch (constructor) {
      | Json.Array([Json.String(tag), arg0]) when "Builtin" == tag =>
        switch (
          (
            string =>
              switch (string) {
              | Json.String(string) => Ok(string)
              | _ => Error(["epected a string"])
              }
          )(
            arg0,
          )
        ) {
        | Belt.Result.Ok(arg0) =>
          Ok(Builtin(arg0): _TypeMap__DigTypes__typeSource(arg0))
        | Error(error) => Error(["constructor argument 0", ...error])
        }
      | Json.Array([Json.String(tag), arg0]) when "Public" == tag =>
        switch (referenceTransformer(arg0)) {
        | Belt.Result.Ok(arg0) =>
          Ok(Public(arg0): _TypeMap__DigTypes__typeSource(arg0))
        | Error(error) => Error(["constructor argument 0", ...error])
        }
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "NotFound" == tag =>
        Ok(NotFound: _TypeMap__DigTypes__typeSource(arg0))
      | Json.Array([Json.String(tag), ..._]) =>
        Error(["Invalid constructor: " ++ tag])
      | _ => Error(["Expected an array"])
      }

  and serialize_Analyze__TopTypes____moduleName:
    _Analyze__TopTypes__moduleName => target =
    value => Json.String(value)
  and serialize_Asttypes____loc:
    'arg0.
    ('arg0 => target, _Asttypes__loc('arg0)) => target
   =
    (aTransformer, record) =>
      Json.Object([
        ("txt", aTransformer(record.txt)),
        ("loc", serialize_Location____t(record.loc)),
      ])
  and serialize_Location____t: _Location__t => target =
    record =>
      Json.Object([
        (
          "loc_start",
          serialize_Stdlib__lexing____position(record.loc_start),
        ),
        ("loc_end", serialize_Stdlib__lexing____position(record.loc_end)),
        ("loc_ghost", record.loc_ghost ? Json.True : Json.False),
      ])
  and serialize_Parsetree____attribute: _Parsetree__attribute => target =
    value => {
      let (arg0, arg1) = value;
      Json.Array([
        serialize_Asttypes____loc(value => Json.String(value), arg0),
        serialize_Parsetree____payload(arg1),
      ]);
    }
  and serialize_Parsetree____attributes: _Parsetree__attributes => target =
    value =>
      Json.Array(Belt.List.map(value, serialize_Parsetree____attribute))
  and serialize_Parsetree____core_type: _Parsetree__core_type => target = TransformHelpers.serialize_Parsetree____core_type
  and serialize_Parsetree____expression: _Parsetree__expression => target = TransformHelpers.serialize_Parsetree____expression
  and serialize_Parsetree____pattern: _Parsetree__pattern => target = TransformHelpers.serialize_Parsetree____pattern
  and serialize_Parsetree____payload: _Parsetree__payload => target =
    constructor =>
      switch (constructor) {
      | PStr(arg0) =>
        Json.Array([
          Json.String("PStr"),
          serialize_Parsetree____structure(arg0),
        ])
      | PSig(arg0) =>
        Json.Array([
          Json.String("PSig"),
          serialize_Parsetree____signature(arg0),
        ])
      | PTyp(arg0) =>
        Json.Array([
          Json.String("PTyp"),
          serialize_Parsetree____core_type(arg0),
        ])
      | [@implicit_arity] PPat(arg0, arg1) =>
        Json.Array([
          Json.String("PPat"),
          serialize_Parsetree____pattern(arg0),
          switch (arg1) {
          | None => Json.Null
          | Some(v) => serialize_Parsetree____expression(v)
          },
        ])
      }
  and serialize_Parsetree____signature: _Parsetree__signature => target = TransformHelpers.serialize_Parsetree____signature
  and serialize_Parsetree____structure: _Parsetree__structure => target = TransformHelpers.serialize_Parsetree____structure
  and serialize_SharedTypes__SimpleType__body:
    'arg0.
    ('arg0 => target, _SharedTypes__SimpleType__body('arg0)) => target
   =
    (sourceTransformer, constructor) =>
      switch (constructor) {
      | Open => Json.Array([Json.String("Open")])
      | Abstract => Json.Array([Json.String("Abstract")])
      | Expr(arg0) =>
        Json.Array([
          Json.String("Expr"),
          serialize_SharedTypes__SimpleType__expr(sourceTransformer, arg0),
        ])
      | Record(arg0) =>
        Json.Array([
          Json.String("Record"),
          Json.Array(
            Belt.List.map(arg0, ((arg0, arg1)) =>
              Json.Array([
                Json.String(arg0),
                serialize_SharedTypes__SimpleType__expr(
                  sourceTransformer,
                  arg1,
                ),
              ])
            ),
          ),
        ])
      | Variant(arg0) =>
        Json.Array([
          Json.String("Variant"),
          Json.Array(
            Belt.List.map(arg0, ((arg0, arg1, arg2)) =>
              Json.Array([
                Json.String(arg0),
                Json.Array(
                  Belt.List.map(
                    arg1,
                    serialize_SharedTypes__SimpleType__expr(
                      sourceTransformer,
                    ),
                  ),
                ),
                switch (arg2) {
                | None => Json.Null
                | Some(v) =>
                  (serialize_SharedTypes__SimpleType__expr(sourceTransformer))(
                    v,
                  )
                },
              ])
            ),
          ),
        ])
      }
  and serialize_SharedTypes__SimpleType__declaration:
    'arg0.
    ('arg0 => target, _SharedTypes__SimpleType__declaration('arg0)) => target
   =
    (sourceTransformer, record) =>
      Json.Object([
        ("name", Json.String(record.name)),
        (
          "variables",
          Json.Array(
            Belt.List.map(
              record.variables,
              serialize_SharedTypes__SimpleType__expr(sourceTransformer),
            ),
          ),
        ),
        (
          "body",
          serialize_SharedTypes__SimpleType__body(
            sourceTransformer,
            record.body,
          ),
        ),
      ])
  and serialize_SharedTypes__SimpleType__expr:
    'arg0.
    ('arg0 => target, _SharedTypes__SimpleType__expr('arg0)) => target
   =
    (sourceTransformer, constructor) =>
      switch (constructor) {
      | Variable(arg0) =>
        Json.Array([Json.String("Variable"), Json.String(arg0)])
      | AnonVariable => Json.Array([Json.String("AnonVariable")])
      | [@implicit_arity] RowVariant(arg0, arg1) =>
        Json.Array([
          Json.String("RowVariant"),
          Json.Array(
            Belt.List.map(arg0, ((arg0, arg1)) =>
              Json.Array([
                Json.String(arg0),
                switch (arg1) {
                | None => Json.Null
                | Some(v) =>
                  (serialize_SharedTypes__SimpleType__expr(sourceTransformer))(
                    v,
                  )
                },
              ])
            ),
          ),
          arg1 ? Json.True : Json.False,
        ])
      | [@implicit_arity] Reference(arg0, arg1) =>
        Json.Array([
          Json.String("Reference"),
          sourceTransformer(arg0),
          Json.Array(
            Belt.List.map(
              arg1,
              serialize_SharedTypes__SimpleType__expr(sourceTransformer),
            ),
          ),
        ])
      | Tuple(arg0) =>
        Json.Array([
          Json.String("Tuple"),
          Json.Array(
            Belt.List.map(
              arg0,
              serialize_SharedTypes__SimpleType__expr(sourceTransformer),
            ),
          ),
        ])
      | [@implicit_arity] Fn(arg0, arg1) =>
        Json.Array([
          Json.String("Fn"),
          Json.Array(
            Belt.List.map(arg0, ((arg0, arg1)) =>
              Json.Array([
                switch (arg0) {
                | None => Json.Null
                | Some(v) => (value => Json.String(value))(v)
                },
                serialize_SharedTypes__SimpleType__expr(
                  sourceTransformer,
                  arg1,
                ),
              ])
            ),
          ),
          serialize_SharedTypes__SimpleType__expr(sourceTransformer, arg1),
        ])
      | Other => Json.Array([Json.String("Other")])
      }
  and serialize_Stdlib__hashtbl____t:
    'arg0 'arg1.
    ('arg0 => target, 'arg1 => target, _Stdlib__hashtbl__t('arg0, 'arg1)) =>
    target
   =
    (aTransformer, bTransformer) =>
      TransformHelpers.serialize_Stdlib__hashtbl____t(
        aTransformer,
        bTransformer,
      )
  and serialize_Stdlib__lexing____position: _Stdlib__lexing__position => target =
    record =>
      Json.Object([
        ("pos_fname", Json.String(record.pos_fname)),
        ("pos_lnum", Json.Number(float_of_int(record.pos_lnum))),
        ("pos_bol", Json.Number(float_of_int(record.pos_bol))),
        ("pos_cnum", Json.Number(float_of_int(record.pos_cnum))),
      ])
  and serialize_TypeMapSerde__Config____custom:
    _TypeMapSerde__Config__custom => target =
    record =>
      Json.Object([
        ("module", Json.String(record.module_)),
        (
          "path",
          Json.Array(
            Belt.List.map(record.path, value => Json.String(value)),
          ),
        ),
        ("name", Json.String(record.name)),
        ...{
             let rest = [];
             switch (
               "args",
               switch (record.args) {
               | None => Json.Null
               | Some(v) => (value => Json.Number(float_of_int(value)))(v)
               },
             ) {
             | (_, Json.Null) => rest
             | x => [x, ...rest]
             };
           },
      ])
  and serialize_TypeMapSerde__Config____engine:
    _TypeMapSerde__Config__engine => target =
    constructor =>
      switch (constructor) {
      | Rex_json => Json.Array([Json.String("rex-json")])
      | Bs_json => Json.Array([Json.String("Js.Json")])
      | Ezjsonm => Json.Array([Json.String("ezjsonm")])
      | Yojson => Json.Array([Json.String("yojson")])
      }
  and serialize_TypeMapSerde__Config____engineConfig:
    _TypeMapSerde__Config__engineConfig => target =
    record =>
      Json.Object([
        ("output", Json.String(record.output)),
        ...{
             let rest = {
               let rest = [];
               switch (
                 "options",
                 switch (record.options) {
                 | None => Json.Null
                 | Some(v) =>
                   serialize_TypeMapSerde__Config____engineOptions(v)
                 },
               ) {
               | (_, Json.Null) => rest
               | x => [x, ...rest]
               };
             };
             switch (
               "helpers",
               switch (record.helpers) {
               | None => Json.Null
               | Some(v) => (value => Json.String(value))(v)
               },
             ) {
             | (_, Json.Null) => rest
             | x => [x, ...rest]
             };
           },
      ])
  and serialize_TypeMapSerde__Config____engineOptions:
    _TypeMapSerde__Config__engineOptions => target =
    record =>
      Json.Object([
        ("tailCall", record.tailCall ? Json.True : Json.False),
        (
          "deserializeErrorMode",
          serialize_TypeMapSerde__Config____errorMode(
            record.deserializeErrorMode,
          ),
        ),
      ])
  and serialize_TypeMapSerde__Config____engines:
    _TypeMapSerde__Config__engines => target =
    record =>
      Json.Object(
        {
          let rest = {
            let rest = {
              let rest = {
                let rest = [];
                switch (
                  "yojson",
                  switch (record.yojson) {
                  | None => Json.Null
                  | Some(v) =>
                    serialize_TypeMapSerde__Config____engineConfig(v)
                  },
                ) {
                | (_, Json.Null) => rest
                | x => [x, ...rest]
                };
              };
              switch (
                "ezjsonm",
                switch (record.ezjsonm) {
                | None => Json.Null
                | Some(v) => serialize_TypeMapSerde__Config____engineConfig(v)
                },
              ) {
              | (_, Json.Null) => rest
              | x => [x, ...rest]
              };
            };
            switch (
              "Js.Json",
              switch (record.bs_json) {
              | None => Json.Null
              | Some(v) => serialize_TypeMapSerde__Config____engineConfig(v)
              },
            ) {
            | (_, Json.Null) => rest
            | x => [x, ...rest]
            };
          };
          switch (
            "rex-json",
            switch (record.rex_json) {
            | None => Json.Null
            | Some(v) => serialize_TypeMapSerde__Config____engineConfig(v)
            },
          ) {
          | (_, Json.Null) => rest
          | x => [x, ...rest]
          };
        },
      )
  and serialize_TypeMapSerde__Config____entry:
    _TypeMapSerde__Config__entry => target =
    record =>
      Json.Object([
        ("file", Json.String(record.file)),
        ("type", Json.String(record.type_)),
        ...{
             let rest = {
               let rest = {
                 let rest = {
                   let rest = [];
                   switch (
                     "minVersion",
                     switch (record.minVersion) {
                     | None => Json.Null
                     | Some(v) =>
                       (value => Json.Number(float_of_int(value)))(v)
                     },
                   ) {
                   | (_, Json.Null) => rest
                   | x => [x, ...rest]
                   };
                 };
                 switch (
                   "history",
                   switch (record.history) {
                   | None => Json.Null
                   | Some(v) => (value => value ? Json.True : Json.False)(v)
                   },
                 ) {
                 | (_, Json.Null) => rest
                 | x => [x, ...rest]
                 };
               };
               switch (
                 "publicName",
                 switch (record.publicName) {
                 | None => Json.Null
                 | Some(v) => (value => Json.String(value))(v)
                 },
               ) {
               | (_, Json.Null) => rest
               | x => [x, ...rest]
               };
             };
             switch (
               "engines",
               switch (record.engines) {
               | None => Json.Null
               | Some(v) =>
                 (
                   value =>
                     Json.Array(
                       Belt.List.map(
                         value,
                         serialize_TypeMapSerde__Config____engine,
                       ),
                     )
                 )(
                   v,
                 )
               },
             ) {
             | (_, Json.Null) => rest
             | x => [x, ...rest]
             };
           },
      ])
  and serialize_TypeMapSerde__Config____errorMode:
    _TypeMapSerde__Config__errorMode => target =
    constructor =>
      switch (constructor) {
      | Result => Json.Array([Json.String("Result")])
      | TrackedExceptions => Json.Array([Json.String("TrackedExceptions")])
      | PlainExceptions => Json.Array([Json.String("PlainExceptions")])
      }
  and serialize_TypeMapSerde__Config____serializableLockfile:
    _TypeMapSerde__Config__serializableLockfile => target =
    value =>
      serialize_TypeMapSerde__Config__Locked__lockfile(
        serialize_TypeMap__DigTypes____shortReference,
        value,
      )
  and serialize_TypeMapSerde__Config____simpleDeclaration:
    _TypeMapSerde__Config__simpleDeclaration => target =
    value =>
      serialize_SharedTypes__SimpleType__declaration(
        serialize_TypeMap__DigTypes____typeSource(
          serialize_TypeMap__DigTypes____shortReference,
        ),
        value,
      )
  and serialize_TypeMapSerde__Config____simpleExpr:
    _TypeMapSerde__Config__simpleExpr => target =
    value =>
      serialize_SharedTypes__SimpleType__expr(
        serialize_TypeMap__DigTypes____typeSource(
          serialize_TypeMap__DigTypes____shortReference,
        ),
        value,
      )
  and serialize_TypeMapSerde__Config____t: _TypeMapSerde__Config__t => target =
    record =>
      Json.Object([
        ("version", Json.Number(float_of_int(record.version))),
        ...{
             let rest = {
               let rest = {
                 let rest = [
                   (
                     "engines",
                     serialize_TypeMapSerde__Config____engines(
                       record.engines,
                     ),
                   ),
                   ...{
                        let rest = [
                          (
                            "entries",
                            Json.Array(
                              Belt.List.map(
                                record.entries,
                                serialize_TypeMapSerde__Config____entry,
                              ),
                            ),
                          ),
                          (
                            "custom",
                            Json.Array(
                              Belt.List.map(
                                record.custom,
                                serialize_TypeMapSerde__Config____custom,
                              ),
                            ),
                          ),
                        ];
                        switch (
                          "globalEngines",
                          switch (record.globalEngines) {
                          | None => Json.Null
                          | Some(v) =>
                            (
                              value =>
                                Json.Array(
                                  Belt.List.map(
                                    value,
                                    serialize_TypeMapSerde__Config____engine,
                                  ),
                                )
                            )(
                              v,
                            )
                          },
                        ) {
                        | (_, Json.Null) => rest
                        | x => [x, ...rest]
                        };
                      },
                 ];
                 switch (
                   "lockedTypes",
                   switch (record.lockedTypes) {
                   | None => Json.Null
                   | Some(v) => (value => Json.String(value))(v)
                   },
                 ) {
                 | (_, Json.Null) => rest
                 | x => [x, ...rest]
                 };
               };
               switch (
                 "minVersion",
                 switch (record.minVersion) {
                 | None => Json.Null
                 | Some(v) => (value => Json.Number(float_of_int(value)))(v)
                 },
               ) {
               | (_, Json.Null) => rest
               | x => [x, ...rest]
               };
             };
             switch (
               "schemaPropertyName",
               switch (record.schemaPropertyName) {
               | None => Json.Null
               | Some(v) => (value => Json.String(value))(v)
               },
             ) {
             | (_, Json.Null) => rest
             | x => [x, ...rest]
             };
           },
      ])
  and serialize_TypeMapSerde__Config__Locked__lockedConfig:
    'arg0.
    ('arg0 => target, _TypeMapSerde__Config__Locked__lockedConfig('arg0)) =>
    target
   =
    (referenceTransformer, record) =>
      Json.Object([
        (
          "entries",
          Json.Array(
            Belt.List.map(
              record.entries,
              serialize_TypeMapSerde__Config__Locked__lockedEntry,
            ),
          ),
        ),
        (
          "typeMap",
          serialize_TypeMap__DigTypes____typeMap(
            referenceTransformer,
            record.typeMap,
          ),
        ),
      ])
  and serialize_TypeMapSerde__Config__Locked__lockedEntry:
    _TypeMapSerde__Config__Locked__lockedEntry => target =
    record =>
      Json.Object([
        ("moduleName", Json.String(record.moduleName)),
        (
          "modulePath",
          Json.Array(
            Belt.List.map(record.modulePath, value => Json.String(value)),
          ),
        ),
        (
          "engines",
          Json.Array(
            Belt.List.map(record.engines, ((arg0, arg1)) =>
              Json.Array([
                serialize_TypeMapSerde__Config____engine(arg0),
                Json.Number(float_of_int(arg1)),
              ])
            ),
          ),
        ),
        ("name", Json.String(record.name)),
      ])
  and serialize_TypeMapSerde__Config__Locked__lockfile:
    'arg0.
    ('arg0 => target, _TypeMapSerde__Config__Locked__lockfile('arg0)) =>
    target
   =
    (referenceTransformer, record) =>
      Json.Object([
        (
          "versions",
          Json.Array(
            Belt.List.fromArray(
              Belt.Array.map(
                record.versions,
                serialize_TypeMapSerde__Config__Locked__lockedConfig(
                  referenceTransformer,
                ),
              ),
            ),
          ),
        ),
      ])
  and serialize_TypeMap__DigTypes____shortReference:
    _TypeMap__DigTypes__shortReference => target =
    value => {
      let (arg0, arg1, arg2) = value;
      Json.Array([
        serialize_Analyze__TopTypes____moduleName(arg0),
        Json.Array(Belt.List.map(arg1, value => Json.String(value))),
        Json.String(arg2),
      ]);
    }
  and serialize_TypeMap__DigTypes____typeMap:
    'arg0.
    ('arg0 => target, _TypeMap__DigTypes__typeMap('arg0)) => target
   =
    (referenceTransformer, value) =>
      serialize_Stdlib__hashtbl____t(
        serialize_TypeMap__DigTypes____shortReference,
        ((arg0, arg1)) =>
          Json.Array([
            serialize_Parsetree____attributes(arg0),
            serialize_SharedTypes__SimpleType__declaration(
              serialize_TypeMap__DigTypes____typeSource(referenceTransformer),
              arg1,
            ),
          ]),
        value,
      )
  and serialize_TypeMap__DigTypes____typeSource:
    'arg0.
    ('arg0 => target, _TypeMap__DigTypes__typeSource('arg0)) => target
   =
    (referenceTransformer, constructor) =>
      switch (constructor) {
      | Builtin(arg0) =>
        Json.Array([Json.String("Builtin"), Json.String(arg0)])
      | Public(arg0) =>
        Json.Array([Json.String("Public"), referenceTransformer(arg0)])
      | NotFound => Json.Array([Json.String("NotFound")])
      };
};
module Current = Version1;
let parseVersion = json =>
  switch (json) {
  | Json.Object(items) =>
    switch ((Belt.List.getAssoc(items))(schemaPropertyName, (==))) {
    | Some(Json.Number(schemaVersion)) =>
      [@implicit_arity] Ok(int_of_float(schemaVersion), json)
    | Some(_) => Error("Invalid schema version - expected number")
    | None => Error("No " ++ schemaPropertyName)
    }
  | Json.Array([Json.Number(version), payload]) =>
    [@implicit_arity] Ok(int_of_float(version), payload)
  | _ => Error("Not wrapped in a version")
  };
let wrapWithVersion = (version, payload) =>
  switch (payload) {
  | Json.Object(items) =>
    Json.Object(
      items @ [(schemaPropertyName, Json.Number(float_of_int(version)))],
    )
  | _ => Json.Array([Json.Number(float_of_int(version)), payload])
  };
let serializeSerializableLockfile = data =>
  wrapWithVersion(
    currentVersion,
    Version1.serialize_TypeMapSerde__Config____serializableLockfile(data),
  )
and deserializeSerializableLockfile = data =>
  switch (parseVersion(data)) {
  | Error(err) => Error([err])
  | [@implicit_arity] Ok(version, data) =>
    switch (version) {
    | 1 =>
      switch (
        Version1.deserialize_TypeMapSerde__Config____serializableLockfile(
          data,
        )
      ) {
      | Error(error) => Error(error)
      | Ok(data) => Ok(data)
      }
    | _ => Error(["Unexpected version " ++ string_of_int(version)])
    }
  };
let serializeT = data =>
  wrapWithVersion(
    currentVersion,
    Version1.serialize_TypeMapSerde__Config____t(data),
  )
and deserializeT = data =>
  switch (parseVersion(data)) {
  | Error(err) => Error([err])
  | [@implicit_arity] Ok(version, data) =>
    switch (version) {
    | 1 =>
      switch (Version1.deserialize_TypeMapSerde__Config____t(data)) {
      | Error(error) => Error(error)
      | Ok(data) => Ok(data)
      }
    | _ => Error(["Unexpected version " ++ string_of_int(version)])
    }
  };
let serializeSimpleDeclaration = data =>
  wrapWithVersion(
    currentVersion,
    Version1.serialize_TypeMapSerde__Config____simpleDeclaration(data),
  )
and deserializeSimpleDeclaration = data =>
  switch (parseVersion(data)) {
  | Error(err) => Error([err])
  | [@implicit_arity] Ok(version, data) =>
    switch (version) {
    | 1 =>
      switch (
        Version1.deserialize_TypeMapSerde__Config____simpleDeclaration(data)
      ) {
      | Error(error) => Error(error)
      | Ok(data) => Ok(data)
      }
    | _ => Error(["Unexpected version " ++ string_of_int(version)])
    }
  };
let serializeSimpleExpr = data =>
  wrapWithVersion(
    currentVersion,
    Version1.serialize_TypeMapSerde__Config____simpleExpr(data),
  )
and deserializeSimpleExpr = data =>
  switch (parseVersion(data)) {
  | Error(err) => Error([err])
  | [@implicit_arity] Ok(version, data) =>
    switch (version) {
    | 1 =>
      switch (Version1.deserialize_TypeMapSerde__Config____simpleExpr(data)) {
      | Error(error) => Error(error)
      | Ok(data) => Ok(data)
      }
    | _ => Error(["Unexpected version " ++ string_of_int(version)])
    }
  };
module Modules = {
  module SerializableLockfile = {
    type t = Types1._TypeMapSerde__Config__serializableLockfile;
    let serialize = serializeSerializableLockfile;
    let deserialize = deserializeSerializableLockfile;
  };
  module T = {
    type t = Types1._TypeMapSerde__Config__t;
    let serialize = serializeT;
    let deserialize = deserializeT;
  };
  module SimpleDeclaration = {
    type t = Types1._TypeMapSerde__Config__simpleDeclaration;
    let serialize = serializeSimpleDeclaration;
    let deserialize = deserializeSimpleDeclaration;
  };
  module SimpleExpr = {
    type t = Types1._TypeMapSerde__Config__simpleExpr;
    let serialize = serializeSimpleExpr;
    let deserialize = deserializeSimpleExpr;
  };
};