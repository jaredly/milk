[@ocaml.warning "-34"];
open KitchenTypes;
type target = Json.t;
module Version1 = {
  open Types1;
  let rec deserialize_AllTypes__All__normalRecord:
    target => Belt.Result.t(_AllTypes__All__normalRecord, list(string)) =
    record =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_f => {
          let inner = attr_e => {
            let inner = attr_d => {
              let inner = attr_c => {
                let inner = attr_b => {
                  let inner = attr_a =>
                    Belt.Result.Ok(
                      {
                        a: attr_a,
                        b: attr_b,
                        c: attr_c,
                        d: attr_d,
                        e: attr_e,
                        f: attr_f,
                      }: _AllTypes__All__normalRecord,
                    );
                  switch (Belt.List.getAssoc(items, "a", (==))) {
                  | None => Belt.Result.Error(["No attribute 'a'"])
                  | Some(json) =>
                    switch (
                      (
                        number =>
                          switch (number) {
                          | Json.Number(number) =>
                            Belt.Result.Ok(int_of_float(number))
                          | _ => Error(["Expected a float"])
                          }
                      )(
                        json,
                      )
                    ) {
                    | Belt.Result.Error(error) =>
                      Belt.Result.Error(["attribute 'a'", ...error])
                    | Belt.Result.Ok(data) => inner(data)
                    }
                  };
                };
                switch (Belt.List.getAssoc(items, "b", (==))) {
                | None => Belt.Result.Error(["No attribute 'b'"])
                | Some(json) =>
                  switch (
                    (
                      string =>
                        switch (string) {
                        | Json.String(string) => Belt.Result.Ok(string)
                        | _ => Error(["epected a string"])
                        }
                    )(
                      json,
                    )
                  ) {
                  | Belt.Result.Error(error) =>
                    Belt.Result.Error(["attribute 'b'", ...error])
                  | Belt.Result.Ok(data) => inner(data)
                  }
                };
              };
              switch (Belt.List.getAssoc(items, "c", (==))) {
              | None => Belt.Result.Error(["No attribute 'c'"])
              | Some(json) =>
                switch (
                  (
                    json =>
                      switch (json) {
                      | Json.Array([arg0, arg1]) =>
                        switch (
                          (
                            json =>
                              switch (json) {
                              | Json.Array([arg0, arg1]) =>
                                switch (
                                  (
                                    number =>
                                      switch (number) {
                                      | Json.Number(number) =>
                                        Belt.Result.Ok(number)
                                      | _ => Error(["Expected a float"])
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
                                        | Json.String(string) =>
                                          Belt.Result.Ok(string)
                                        | _ => Error(["epected a string"])
                                        }
                                    )(
                                      arg0,
                                    )
                                  ) {
                                  | Belt.Result.Ok(arg0) =>
                                    Belt.Result.Ok((arg0, arg1))
                                  | Error(error) =>
                                    Belt.Result.Error([
                                      "tuple element 0",
                                      ...error,
                                    ])
                                  }
                                | Error(error) =>
                                  Belt.Result.Error([
                                    "tuple element 1",
                                    ...error,
                                  ])
                                }
                              | _ => Belt.Result.Error(["Expected array"])
                              }
                          )(
                            arg1,
                          )
                        ) {
                        | Belt.Result.Ok(arg1) =>
                          switch (
                            (
                              number =>
                                switch (number) {
                                | Json.Number(number) =>
                                  Belt.Result.Ok(int_of_float(number))
                                | _ => Error(["Expected a float"])
                                }
                            )(
                              arg0,
                            )
                          ) {
                          | Belt.Result.Ok(arg0) =>
                            Belt.Result.Ok((arg0, arg1))
                          | Error(error) =>
                            Belt.Result.Error(["tuple element 0", ...error])
                          }
                        | Error(error) =>
                          Belt.Result.Error(["tuple element 1", ...error])
                        }
                      | _ => Belt.Result.Error(["Expected array"])
                      }
                  )(
                    json,
                  )
                ) {
                | Belt.Result.Error(error) =>
                  Belt.Result.Error(["attribute 'c'", ...error])
                | Belt.Result.Ok(data) => inner(data)
                }
              };
            };
            switch (Belt.List.getAssoc(items, "d", (==))) {
            | None => Belt.Result.Error(["No attribute 'd'"])
            | Some(json) =>
              switch (
                (
                  (
                    (transformer, array) =>
                      switch (array) {
                      | Json.Array(items) =>
                        let rec loop = (collected, items) =>
                          switch (items) {
                          | [] =>
                            Belt.Result.Ok(Belt.List.reverse(collected))
                          | [one, ...rest] =>
                            switch (transformer(one)) {
                            | Belt.Result.Error(error) =>
                              Belt.Result.Error(["array element", ...error])
                            | Belt.Result.Ok(value) =>
                              loop([value, ...collected], rest)
                            }
                          };
                        switch (loop([], items)) {
                        | Belt.Result.Error(error) =>
                          Belt.Result.Error(error)
                        | Belt.Result.Ok(value) =>
                          Belt.Result.Ok(Belt.List.toArray(value))
                        };
                      | _ => Belt.Result.Error(["expected an array"])
                      }
                  )(
                    number =>
                    switch (number) {
                    | Json.Number(number) =>
                      Belt.Result.Ok(int_of_float(number))
                    | _ => Error(["Expected a float"])
                    }
                  )
                )(
                  json,
                )
              ) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'd'", ...error])
              | Belt.Result.Ok(data) => inner(data)
              }
            };
          };
          switch (Belt.List.getAssoc(items, "e", (==))) {
          | None => Belt.Result.Error(["No attribute 'e'"])
          | Some(json) =>
            switch (
              (
                list =>
                  switch (list) {
                  | Json.Array(items) =>
                    let transformer = number =>
                      switch (number) {
                      | Json.Number(number) => Belt.Result.Ok(number)
                      | _ => Error(["Expected a float"])
                      };
                    let rec loop = (collected, items) =>
                      switch (items) {
                      | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Belt.Result.Error(error) =>
                          Belt.Result.Error(["list item", ...error])
                        | Belt.Result.Ok(value) =>
                          loop([value, ...collected], rest)
                        }
                      };
                    loop([], items);
                  | _ => Belt.Result.Error(["expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'e'", ...error])
            | Belt.Result.Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "f", (==))) {
        | None => inner(None)
        | Some(json) =>
          switch (
            (
              (
                (transformer, option) =>
                  switch (option) {
                  | Json.Null => Belt.Result.Ok(None)
                  | _ =>
                    switch (transformer(option)) {
                    | Belt.Result.Error(error) =>
                      Belt.Result.Error(["optional value", ...error])
                    | Belt.Result.Ok(value) => Belt.Result.Ok(Some(value))
                    }
                  }
              )(
                number =>
                switch (number) {
                | Json.Number(number) =>
                  Belt.Result.Ok(int_of_float(number))
                | _ => Error(["Expected a float"])
                }
              )
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'f'", ...error])
          | Belt.Result.Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_AllTypes__All__normalVariant:
    target => Belt.Result.t(_AllTypes__All__normalVariant, list(string)) =
    constructor =>
      switch (constructor) {
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "A" == tag =>
        Belt.Result.Ok(A: _AllTypes__All__normalVariant)
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "B" == tag =>
        Belt.Result.Ok(B: _AllTypes__All__normalVariant)
      | Json.Array([Json.String(tag), arg0]) when "C" == tag =>
        switch (
          (
            number =>
              switch (number) {
              | Json.Number(number) => Belt.Result.Ok(int_of_float(number))
              | _ => Error(["Expected a float"])
              }
          )(
            arg0,
          )
        ) {
        | Belt.Result.Ok(arg0) =>
          Belt.Result.Ok(
            [@implicit_arity] C(arg0): _AllTypes__All__normalVariant,
          )
        | Error(error) =>
          Belt.Result.Error(["constructor argument 0", ...error])
        }
      | Json.Array([Json.String(tag), arg0]) when "D" == tag =>
        switch (deserialize_AllTypes__All__normalRecord(arg0)) {
        | Belt.Result.Ok(arg0) =>
          Belt.Result.Ok(
            [@implicit_arity] D(arg0): _AllTypes__All__normalVariant,
          )
        | Error(error) =>
          Belt.Result.Error(["constructor argument 0", ...error])
        }
      | Json.Array([Json.String(tag), ..._]) =>
        Belt.Result.Error(["Invalid constructor: " ++ tag])
      | _ => Belt.Result.Error(["Expected an array"])
      }
  and deserialize_AllTypes__All__parameterizedRecord:
    'arg0 'arg1.
    (
      target => Belt.Result.t('arg0, list(string)),
      target => Belt.Result.t('arg1, list(string)),
      target
    ) =>
    Belt.Result.t(
      _AllTypes__All__parameterizedRecord('arg0, 'arg1),
      list(string),
    )
   =
    (type arg1, type arg0) => (
      (aTransformer, bTransformer, record) =>
        switch (record) {
        | Json.Object(items) =>
          let inner = attr_d => {
            let inner = attr_c => {
              let inner = attr_b => {
                let inner = attr_a =>
                  Belt.Result.Ok(
                    {a: attr_a, b: attr_b, c: attr_c, d: attr_d}:
                                                                   _AllTypes__All__parameterizedRecord(
                                                                    arg0,
                                                                    arg1,
                                                                   ),
                  );
                switch (Belt.List.getAssoc(items, "a", (==))) {
                | None => Belt.Result.Error(["No attribute 'a'"])
                | Some(json) =>
                  switch (aTransformer(json)) {
                  | Belt.Result.Error(error) =>
                    Belt.Result.Error(["attribute 'a'", ...error])
                  | Belt.Result.Ok(data) => inner(data)
                  }
                };
              };
              switch (Belt.List.getAssoc(items, "b", (==))) {
              | None => Belt.Result.Error(["No attribute 'b'"])
              | Some(json) =>
                switch (bTransformer(json)) {
                | Belt.Result.Error(error) =>
                  Belt.Result.Error(["attribute 'b'", ...error])
                | Belt.Result.Ok(data) => inner(data)
                }
              };
            };
            switch (Belt.List.getAssoc(items, "c", (==))) {
            | None => Belt.Result.Error(["No attribute 'c'"])
            | Some(json) =>
              switch (
                (
                  json =>
                    switch (json) {
                    | Json.Array([arg0, arg1]) =>
                      switch (
                        (
                          number =>
                            switch (number) {
                            | Json.Number(number) => Belt.Result.Ok(number)
                            | _ => Error(["Expected a float"])
                            }
                        )(
                          arg1,
                        )
                      ) {
                      | Belt.Result.Ok(arg1) =>
                        switch (
                          (
                            number =>
                              switch (number) {
                              | Json.Number(number) =>
                                Belt.Result.Ok(int_of_float(number))
                              | _ => Error(["Expected a float"])
                              }
                          )(
                            arg0,
                          )
                        ) {
                        | Belt.Result.Ok(arg0) =>
                          Belt.Result.Ok((arg0, arg1))
                        | Error(error) =>
                          Belt.Result.Error(["tuple element 0", ...error])
                        }
                      | Error(error) =>
                        Belt.Result.Error(["tuple element 1", ...error])
                      }
                    | _ => Belt.Result.Error(["Expected array"])
                    }
                )(
                  json,
                )
              ) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'c'", ...error])
              | Belt.Result.Ok(data) => inner(data)
              }
            };
          };
          switch (Belt.List.getAssoc(items, "d", (==))) {
          | None => Belt.Result.Error(["No attribute 'd'"])
          | Some(json) =>
            switch (deserialize_AllTypes__All__recursive(json)) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'd'", ...error])
            | Belt.Result.Ok(data) => inner(data)
            }
          };
        | _ => Belt.Result.Error(["Expected an object"])
        }:
        (
          target => Belt.Result.t(arg0, list(string)),
          target => Belt.Result.t(arg1, list(string)),
          target
        ) =>
        Belt.Result.t(
          _AllTypes__All__parameterizedRecord(arg0, arg1),
          list(string),
        )
    )
  and deserialize_AllTypes__All__parameterizedVariant:
    'arg0 'arg1.
    (
      target => Belt.Result.t('arg0, list(string)),
      target => Belt.Result.t('arg1, list(string)),
      target
    ) =>
    Belt.Result.t(
      _AllTypes__All__parameterizedVariant('arg0, 'arg1),
      list(string),
    )
   =
    (type arg1, type arg0) => (
      (aTransformer, bTransformer, constructor) =>
        switch (constructor) {
        | Json.Array([Json.String(tag)])
        | Json.String(tag) when "PA" == tag =>
          Belt.Result.Ok(
            PA: _AllTypes__All__parameterizedVariant(arg0, arg1),
          )
        | Json.Array([Json.String(tag), arg0]) when "PB" == tag =>
          switch (aTransformer(arg0)) {
          | Belt.Result.Ok(arg0) =>
            Belt.Result.Ok(
              [@implicit_arity] PB(arg0):
                                           _AllTypes__All__parameterizedVariant(
                                             arg0,
                                             arg1,
                                           ),
            )
          | Error(error) =>
            Belt.Result.Error(["constructor argument 0", ...error])
          }
        | Json.Array([Json.String(tag), arg0, arg1]) when "PC" == tag =>
          switch (bTransformer(arg1)) {
          | Belt.Result.Ok(arg1) =>
            switch (aTransformer(arg0)) {
            | Belt.Result.Ok(arg0) =>
              Belt.Result.Ok(
                [@implicit_arity] PC(arg0, arg1):
                                                   _AllTypes__All__parameterizedVariant(
                                                     arg0,
                                                     arg1,
                                                   ),
              )
            | Error(error) =>
              Belt.Result.Error(["constructor argument 0", ...error])
            }
          | Error(error) =>
            Belt.Result.Error(["constructor argument 1", ...error])
          }
        | Json.Array([Json.String(tag), arg0]) when "PD" == tag =>
          switch (
            (
              deserialize_AllTypes__All__parameterizedRecord(
                aTransformer,
                bTransformer,
              )
            )(
              arg0,
            )
          ) {
          | Belt.Result.Ok(arg0) =>
            Belt.Result.Ok(
              [@implicit_arity] PD(arg0):
                                           _AllTypes__All__parameterizedVariant(
                                             arg0,
                                             arg1,
                                           ),
            )
          | Error(error) =>
            Belt.Result.Error(["constructor argument 0", ...error])
          }
        | Json.Array([Json.String(tag), arg0]) when "PE" == tag =>
          switch (deserialize_AllTypes__All__normalVariant(arg0)) {
          | Belt.Result.Ok(arg0) =>
            Belt.Result.Ok(
              [@implicit_arity] PE(arg0):
                                           _AllTypes__All__parameterizedVariant(
                                             arg0,
                                             arg1,
                                           ),
            )
          | Error(error) =>
            Belt.Result.Error(["constructor argument 0", ...error])
          }
        | Json.Array([Json.String(tag), arg0]) when "PF" == tag =>
          switch (deserialize_AllTypes__All__normalRecord(arg0)) {
          | Belt.Result.Ok(arg0) =>
            Belt.Result.Ok(
              [@implicit_arity] PF(arg0):
                                           _AllTypes__All__parameterizedVariant(
                                             arg0,
                                             arg1,
                                           ),
            )
          | Error(error) =>
            Belt.Result.Error(["constructor argument 0", ...error])
          }
        | Json.Array([Json.String(tag), ..._]) =>
          Belt.Result.Error(["Invalid constructor: " ++ tag])
        | _ => Belt.Result.Error(["Expected an array"])
        }:
        (
          target => Belt.Result.t(arg0, list(string)),
          target => Belt.Result.t(arg1, list(string)),
          target
        ) =>
        Belt.Result.t(
          _AllTypes__All__parameterizedVariant(arg0, arg1),
          list(string),
        )
    )
  and deserialize_AllTypes__All__recursive:
    target => Belt.Result.t(_AllTypes__All__recursive, list(string)) =
    constructor =>
      switch (constructor) {
      | Json.Array([Json.String(tag)])
      | Json.String(tag) when "A" == tag =>
        Belt.Result.Ok(A: _AllTypes__All__recursive)
      | Json.Array([Json.String(tag), arg0]) when "B" == tag =>
        switch (deserialize_AllTypes__All__recursive(arg0)) {
        | Belt.Result.Ok(arg0) =>
          Belt.Result.Ok(
            [@implicit_arity] B(arg0): _AllTypes__All__recursive,
          )
        | Error(error) =>
          Belt.Result.Error(["constructor argument 0", ...error])
        }
      | Json.Array([Json.String(tag), ..._]) =>
        Belt.Result.Error(["Invalid constructor: " ++ tag])
      | _ => Belt.Result.Error(["Expected an array"])
      }
  and deserialize_AllTypes__All__rename:
    target => Belt.Result.t(_AllTypes__All__rename, list(string)) =
    value => deserialize_AllTypes__All__top(value)
  and deserialize_AllTypes__All__top:
    target => Belt.Result.t(_AllTypes__All__top, list(string)) =
    record =>
      switch (record) {
      | Json.Object(items) =>
        let inner = attr_title => {
          let inner = attr_contents =>
            Belt.Result.Ok(
              {contents: attr_contents, title: attr_title}: _AllTypes__All__top,
            );
          switch (Belt.List.getAssoc(items, "contents", (==))) {
          | None => Belt.Result.Error(["No attribute 'contents'"])
          | Some(json) =>
            switch (
              (
                deserialize_AllTypes__All__parameterizedVariant(
                  number =>
                    switch (number) {
                    | Json.Number(number) =>
                      Belt.Result.Ok(int_of_float(number))
                    | _ => Error(["Expected a float"])
                    },
                  (
                    (transformer, array) =>
                      switch (array) {
                      | Json.Array(items) =>
                        let rec loop = (collected, items) =>
                          switch (items) {
                          | [] =>
                            Belt.Result.Ok(Belt.List.reverse(collected))
                          | [one, ...rest] =>
                            switch (transformer(one)) {
                            | Belt.Result.Error(error) =>
                              Belt.Result.Error(["array element", ...error])
                            | Belt.Result.Ok(value) =>
                              loop([value, ...collected], rest)
                            }
                          };
                        switch (loop([], items)) {
                        | Belt.Result.Error(error) =>
                          Belt.Result.Error(error)
                        | Belt.Result.Ok(value) =>
                          Belt.Result.Ok(Belt.List.toArray(value))
                        };
                      | _ => Belt.Result.Error(["expected an array"])
                      }
                  )(
                    number =>
                    switch (number) {
                    | Json.Number(number) => Belt.Result.Ok(number)
                    | _ => Error(["Expected a float"])
                    }
                  ),
                )
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'contents'", ...error])
            | Belt.Result.Ok(data) => inner(data)
            }
          };
        };
        switch (Belt.List.getAssoc(items, "title", (==))) {
        | None => Belt.Result.Error(["No attribute 'title'"])
        | Some(json) =>
          switch (
            (
              string =>
                switch (string) {
                | Json.String(string) => Belt.Result.Ok(string)
                | _ => Error(["epected a string"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'title'", ...error])
          | Belt.Result.Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and serialize_AllTypes__All__normalRecord:
    _AllTypes__All__normalRecord => target =
    record =>
      Json.Object([
        ("a", Json.Number(float_of_int(record.a))),
        ("b", Json.String(record.b)),
        (
          "c",
          {
            let (arg0, arg1) = record.c;
            Json.Array([
              Json.Number(float_of_int(arg0)),
              {
                let (arg0, arg1) = arg1;
                Json.Array([Json.String(arg0), Json.Number(arg1)]);
              },
            ]);
          },
        ),
        (
          "d",
          Json.Array(
            Belt.List.fromArray(
              Belt.Array.map(record.d, value =>
                Json.Number(float_of_int(value))
              ),
            ),
          ),
        ),
        (
          "e",
          Json.Array(Belt.List.map(record.e, value => Json.Number(value))),
        ),
        (
          "f",
          switch (record.f) {
          | None => Json.Null
          | Some(v) => (value => Json.Number(float_of_int(value)))(v)
          },
        ),
      ])
  and serialize_AllTypes__All__normalVariant:
    _AllTypes__All__normalVariant => target =
    constructor =>
      switch (constructor) {
      | A => Json.Array([Json.String("A")])
      | B => Json.Array([Json.String("B")])
      | C(arg0) =>
        Json.Array([Json.String("C"), Json.Number(float_of_int(arg0))])
      | D(arg0) =>
        Json.Array([
          Json.String("D"),
          serialize_AllTypes__All__normalRecord(arg0),
        ])
      }
  and serialize_AllTypes__All__parameterizedRecord:
    'arg0 'arg1.
    (
      'arg0 => target,
      'arg1 => target,
      _AllTypes__All__parameterizedRecord('arg0, 'arg1)
    ) =>
    target
   =
    (aTransformer, bTransformer, record) =>
      Json.Object([
        ("a", aTransformer(record.a)),
        ("b", bTransformer(record.b)),
        (
          "c",
          {
            let (arg0, arg1) = record.c;
            Json.Array([
              Json.Number(float_of_int(arg0)),
              Json.Number(arg1),
            ]);
          },
        ),
        ("d", serialize_AllTypes__All__recursive(record.d)),
      ])
  and serialize_AllTypes__All__parameterizedVariant:
    'arg0 'arg1.
    (
      'arg0 => target,
      'arg1 => target,
      _AllTypes__All__parameterizedVariant('arg0, 'arg1)
    ) =>
    target
   =
    (aTransformer, bTransformer, constructor) =>
      switch (constructor) {
      | PA => Json.Array([Json.String("PA")])
      | PB(arg0) => Json.Array([Json.String("PB"), aTransformer(arg0)])
      | [@implicit_arity] PC(arg0, arg1) =>
        Json.Array([
          Json.String("PC"),
          aTransformer(arg0),
          bTransformer(arg1),
        ])
      | PD(arg0) =>
        Json.Array([
          Json.String("PD"),
          serialize_AllTypes__All__parameterizedRecord(
            aTransformer,
            bTransformer,
            arg0,
          ),
        ])
      | PE(arg0) =>
        Json.Array([
          Json.String("PE"),
          serialize_AllTypes__All__normalVariant(arg0),
        ])
      | PF(arg0) =>
        Json.Array([
          Json.String("PF"),
          serialize_AllTypes__All__normalRecord(arg0),
        ])
      }
  and serialize_AllTypes__All__recursive: _AllTypes__All__recursive => target =
    constructor =>
      switch (constructor) {
      | A => Json.Array([Json.String("A")])
      | B(arg0) =>
        Json.Array([
          Json.String("B"),
          serialize_AllTypes__All__recursive(arg0),
        ])
      }
  and serialize_AllTypes__All__rename: _AllTypes__All__rename => target =
    value => serialize_AllTypes__All__top(value)
  and serialize_AllTypes__All__top: _AllTypes__All__top => target =
    record =>
      Json.Object([
        (
          "contents",
          serialize_AllTypes__All__parameterizedVariant(
            value => Json.Number(float_of_int(value)),
            value =>
              Json.Array(
                Belt.List.fromArray(
                  Belt.Array.map(value, value => Json.Number(value)),
                ),
              ),
            record.contents,
          ),
        ),
        ("title", Json.String(record.title)),
      ]);
};
module Current = Version1;
let parseVersion = json =>
  switch (json) {
  | Json.Object(items) =>
    switch ((Belt.List.getAssoc(items))("$schemaVersion", (==))) {
    | Some(Json.Number(schemaVersion)) =>
      [@implicit_arity] Belt.Result.Ok(int_of_float(schemaVersion), json)
    | Some(_) => Belt.Result.Error("Invalid schema version - expected number")
    | None => Belt.Result.Error("No $schemaVersion")
    }
  | Json.Array([Json.Number(version), payload]) =>
    [@implicit_arity] Belt.Result.Ok(int_of_float(version), payload)
  | _ => Belt.Result.Error("Not wrapped in a version")
  };
let wrapWithVersion = (version, payload) =>
  switch (payload) {
  | Json.Object(items) =>
    Json.Object([
      ("$schemaVersion", Json.Number(float_of_int(version))),
      ...items,
    ])
  | _ => Json.Array([Json.Number(float_of_int(version)), payload])
  };
let serializeKitchenSink = data =>
  wrapWithVersion(
    currentVersion,
    Version1.serialize_AllTypes__All__rename(data),
  )
and deserializeKitchenSink = data =>
  switch (parseVersion(data)) {
  | Belt.Result.Error(err) => Belt.Result.Error([err])
  | [@implicit_arity] Ok(version, data) =>
    switch (version) {
    | 1 =>
      switch (Version1.deserialize_AllTypes__All__rename(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) => Belt.Result.Ok(data)
      }
    | _ =>
      Belt.Result.Error(["Unexpected version " ++ string_of_int(version)])
    }
  };
module Modules = {
  module KitchenSink = {
    type t = Types1._AllTypes__All__rename;
    let serialize = serializeKitchenSink;
    let deserialize = deserializeKitchenSink;
  };
};
