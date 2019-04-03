[@ocaml.warning "-34"];
module Types1 = {
  type _Types__household = {
    people: list(_Types__person),
    pets: list(_Types__pet),
  }
  and _Types__person = {
    name: string,
    age: int,
    coords: (float, float),
    parents: option((_Types__person, _Types__person)),
  }
  and _Types__pet =
    | Dog
    | Cat;
};
module Types2 = {
  type _Types__household = {
    people: list(_Types__person),
    pets: list(_Types__pet),
  }
  and _Types__person = {
    name: string,
    age: float,
    coords: (float, float),
    parents: option((_Types__person, _Types__person)),
  }
  and _Types__pet = Types.pet = | Dog | Cat | Mouse;
  let rec migrate_Types____household:
    Types1._Types__household => _Types__household =
    _input_data => {
      let _converted_people =
        (Belt.List.map(_input_data.people))(_item =>
          migrate_Types____person(_item)
        );
      let _converted_pets =
        (Belt.List.map(_input_data.pets))(_item =>
          migrate_Types____pet(_item)
        );
      {pets: _converted_pets, people: _converted_people};
    }
  and migrate_Types____person: Types1._Types__person => _Types__person =
    _input_data => {
      let _converted_name = _input_data.name;
      let _converted_age =
        (
          person => float_of_int(person.age * 7):
            Types1._Types__person => float
        )(
          _input_data,
        );
      let _converted_coords = {
        let (arg0, arg1) = _input_data.coords;
        (arg0, arg1);
      };
      let _converted_parents =
        switch (_input_data.parents) {
        | None => None
        | Some(_item) =>
          Some(
            {
              let (arg0, arg1) = _item;
              (
                migrate_Types____person(arg0),
                migrate_Types____person(arg1),
              );
            },
          )
        };
      {
        parents: _converted_parents,
        coords: _converted_coords,
        age: _converted_age,
        name: _converted_name,
      };
    }
  and migrate_Types____pet: Types1._Types__pet => _Types__pet =
    _input_data =>
      switch (_input_data) {
      | Dog => Dog
      | Cat => Cat
      };
};
module Types3 = {
  type _Types__household = {
    people: list(_Types__person),
    pets: list(_Types__pet),
  }
  and _Types__person = {
    name: string,
    age: float,
    coords: (float, float),
  }
  and _Types__pet = Types.pet = | Dog | Cat | Mouse;
  let rec migrate_Types____household:
    Types2._Types__household => _Types__household =
    _input_data => {
      let _converted_people =
        (Belt.List.map(_input_data.people))(_item =>
          migrate_Types____person(_item)
        );
      let _converted_pets =
        (Belt.List.map(_input_data.pets))(_item =>
          migrate_Types____pet(_item)
        );
      {pets: _converted_pets, people: _converted_people};
    }
  and migrate_Types____person: Types2._Types__person => _Types__person =
    _input_data => {
      let _converted_name = _input_data.name;
      let _converted_age = _input_data.age;
      let _converted_coords = {
        let (arg0, arg1) = _input_data.coords;
        (arg0, arg1);
      };
      {coords: _converted_coords, age: _converted_age, name: _converted_name};
    }
  and migrate_Types____pet: Types2._Types__pet => _Types__pet =
    _input_data => _input_data;
};
module Types4 = {
  type _Types__dogBreed =
    | Schnouser
    | Lab
    | Retriever
    | Poodle
  and _Types__household = {
    people: list(_Types__person),
    pets: list(_Types__pet),
  }
  and _Types__person =
    Types3._Types__person = {
      name: string,
      age: float,
      coords: (float, float),
    }
  and _Types__pet =
    | Dog(option(_Types__dogBreed))
    | Cat
    | Mouse;
  let rec migrate_Types____household:
    Types3._Types__household => _Types__household =
    _input_data => {
      let _converted_people =
        (Belt.List.map(_input_data.people))(_item =>
          migrate_Types____person(_item)
        );
      let _converted_pets =
        (Belt.List.map(_input_data.pets))(_item =>
          migrate_Types____pet(_item)
        );
      {pets: _converted_pets, people: _converted_people};
    }
  and migrate_Types____person: Types3._Types__person => _Types__person =
    _input_data => _input_data
  and migrate_Types____pet: Types3._Types__pet => _Types__pet =
    _input_data =>
      switch (_input_data) {
      | Dog => Dog(None)
      | Cat => Cat
      | Mouse => Mouse
      };
};
module Types5 = {
  type _Types__dogBreed =
    | Schnouser(string)
    | Lab
    | Retriever
    | Poodle
  and _Types__household = {
    people: list(_Types__person),
    pets: list(_Types__pet),
    county: _Types__named(int),
  }
  and _Types__named('a) = {
    name: string,
    contents: 'a,
  }
  and _Types__person =
    Types4._Types__person = {
      name: string,
      age: float,
      coords: (float, float),
    }
  and _Types__pet =
    | Dog(option(_Types__dogBreed))
    | Cat
    | Mouse;
  let rec migrate_Types____dogBreed:
    Types4._Types__dogBreed => _Types__dogBreed =
    _input_data =>
      switch (_input_data) {
      | Schnouser => Schnouser("white")
      | Lab => Lab
      | Retriever => Retriever
      | Poodle => Poodle
      }
  and migrate_Types____household: Types4._Types__household => _Types__household =
    _input_data => {
      let _converted_people =
        (Belt.List.map(_input_data.people))(_item =>
          migrate_Types____person(_item)
        );
      let _converted_pets =
        (Belt.List.map(_input_data.pets))(_item =>
          migrate_Types____pet(_item)
        );
      let _converted_county =
        (
          household => {name: "Nowhere", contents: 0}:
            Types4._Types__household => _Types__named(int)
        )(
          _input_data,
        );
      {
        county: _converted_county,
        pets: _converted_pets,
        people: _converted_people,
      };
    }
  and migrate_Types____person: Types4._Types__person => _Types__person =
    _input_data => _input_data
  and migrate_Types____pet: Types4._Types__pet => _Types__pet =
    _input_data =>
      switch (_input_data) {
      | Dog(arg0) =>
        [@implicit_arity]
        Dog(
          switch (arg0) {
          | None => None
          | Some(_item) => Some(migrate_Types____dogBreed(_item))
          },
        )
      | Cat => Cat
      | Mouse => Mouse
      };
};
module Types6 = {
  type _Types__household = {
    people: list(_Types__person),
    pets: list(_Types__pet),
    what: _Types__what(string),
    visitors: list(_Types__person),
    county: _Types__named(int),
  }
  and _Types__named('a) = {
    name: string,
    contents: 'a,
    isClosed: bool,
  }
  and _Types__person =
    Types5._Types__person = {
      name: string,
      age: float,
      coords: (float, float),
    }
  and _Types__pet = Types.pet = | Dog | Cat | Mouse
  and _Types__what('a) =
    | Now('a);
  let rec migrate_Types____household:
    Types5._Types__household => _Types__household =
    _input_data => {
      let _converted_people =
        (Belt.List.map(_input_data.people))(_item =>
          migrate_Types____person(_item)
        );
      let _converted_pets =
        (Belt.List.map(_input_data.pets))(_item =>
          migrate_Types____pet(_item)
        );
      let _converted_what =
        (
          household => Now("4"):
            Types5._Types__household => _Types__what(string)
        )(
          _input_data,
        );
      let _converted_visitors =
        (household => []: Types5._Types__household => list(_Types__person))(
          _input_data,
        );
      let _converted_county =
        migrate_Types____named(arg => arg, _input_data.county);
      {
        county: _converted_county,
        visitors: _converted_visitors,
        what: _converted_what,
        pets: _converted_pets,
        people: _converted_people,
      };
    }
  and migrate_Types____named:
    'a 'a_migrated.
    ('a => 'a_migrated, Types5._Types__named('a)) =>
    _Types__named('a_migrated)
   =
    (type a, type a_migrated) => (
      (contentsMigrator, named) => {
        name: named.name,
        contents: contentsMigrator(named.contents),
        isClosed: false,
      }:
        (a => a_migrated, Types5._Types__named(a)) =>
        _Types__named(a_migrated)
    )
  and migrate_Types____person: Types5._Types__person => _Types__person =
    _input_data => _input_data
  and migrate_Types____pet: Types5._Types__pet => _Types__pet =
    _input_data =>
      switch (_input_data) {
      | Dog(dogBreed) => Dog
      | Cat => Cat
      | Mouse => Mouse
      };
};
module Types7 = {
  type _Types__household =
    Types.household = {
      one: _Types__what(_Types__one),
      two: _Types__what(_Types__two),
      people: list(_Types__person),
      pets: list(_Types__pet),
      what: _Types__what(string),
      visitors: list(_Types__person),
      county: _Types__named(int),
    }
  and _Types__named('a) =
    Types.named('a) = {
      name: string,
      contents: 'a,
      isClosed: bool,
      other: option('a),
    }
  and _Types__one = Types.one = {key: string}
  and _Types__person =
    Types.person = {
      name: string,
      age: float,
      thing: [ | `one | `two(int) | `three(float, string)],
      coords: (float, float),
    }
  and _Types__pet = Types.pet = | Dog | Cat | Mouse
  and _Types__two = Types.two = {key: string}
  and _Types__what('a) = Types.what('a) = | Now('a, int);
  let rec migrate_Types____household:
    Types6._Types__household => _Types__household =
    _input_data => {
      let _converted_one =
        (
          h => Now({key: "one"}, 5):
            Types6._Types__household => _Types__what(_Types__one)
        )(
          _input_data,
        );
      let _converted_two =
        (
          h => Now({key: "two"}, 5):
            Types6._Types__household => _Types__what(_Types__two)
        )(
          _input_data,
        );
      let _converted_people =
        (Belt.List.map(_input_data.people))(_item =>
          migrate_Types____person(_item)
        );
      let _converted_pets =
        (Belt.List.map(_input_data.pets))(_item =>
          migrate_Types____pet(_item)
        );
      let _converted_what =
        migrate_Types____what(arg => arg, _input_data.what);
      let _converted_visitors =
        (Belt.List.map(_input_data.visitors))(_item =>
          migrate_Types____person(_item)
        );
      let _converted_county =
        migrate_Types____named(arg => arg, _input_data.county);
      {
        county: _converted_county,
        visitors: _converted_visitors,
        what: _converted_what,
        pets: _converted_pets,
        people: _converted_people,
        two: _converted_two,
        one: _converted_one,
      };
    }
  and migrate_Types____named:
    'a 'a_migrated.
    ('a => 'a_migrated, Types6._Types__named('a)) =>
    _Types__named('a_migrated)
   =
    (type a, type a_migrated) => (
      (_migrator_a, _input_data) => {
        let _converted_name = _input_data.name;
        let _converted_contents = _migrator_a(_input_data.contents);
        let _converted_isClosed = _input_data.isClosed;
        let _converted_other =
          (_ => None: Types6._Types__named(a) => option(a_migrated))(
            _input_data,
          );
        {
          other: _converted_other,
          isClosed: _converted_isClosed,
          contents: _converted_contents,
          name: _converted_name,
        };
      }:
        (a => a_migrated, Types6._Types__named(a)) =>
        _Types__named(a_migrated)
    )
  and migrate_Types____person: Types6._Types__person => _Types__person =
    _input_data => {
      let _converted_name = _input_data.name;
      let _converted_age = _input_data.age;
      let _converted_thing =
        (
          _ => `one:
            Types6._Types__person =>
            [ | `one | `two(int) | `three(float, string)]
        )(
          _input_data,
        );
      let _converted_coords = {
        let (arg0, arg1) = _input_data.coords;
        (arg0, arg1);
      };
      {
        coords: _converted_coords,
        thing: _converted_thing,
        age: _converted_age,
        name: _converted_name,
      };
    }
  and migrate_Types____pet: Types6._Types__pet => _Types__pet =
    _input_data => _input_data
  and migrate_Types____what:
    'a 'a_migrated.
    ('a => 'a_migrated, Types6._Types__what('a)) => _Types__what('a_migrated)
   =
    (type a, type a_migrated) => (
      (_migrator_a, _input_data) =>
        switch (_input_data) {
        | Now(a) => Now(_migrator_a(a), 5)
        }:
        (a => a_migrated, Types6._Types__what(a)) => _Types__what(a_migrated)
    );
};
let currentVersion = 7;
type target = Js.Json.t;
module Version1 = {
  open Types1;
  let rec deserialize_Types____household:
    target => Belt.Result.t(_Types__household, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_pets => {
          let inner = attr_people =>
            Belt.Result.Ok(
              {people: attr_people, pets: attr_pets}: _Types__household,
            );
          switch (Js.Dict.get(dict, "people")) {
          | None => Belt.Result.Error(["No attribute 'people'"])
          | Some(json) =>
            switch (
              (
                list =>
                  switch (Js.Json.classify(list)) {
                  | JSONArray(items) =>
                    let transformer = deserialize_Types____person;
                    let rec loop = (i, collected, items) =>
                      switch (items) {
                      | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Belt.Result.Error(error) =>
                          Belt.Result.Error([
                            "list element " ++ string_of_int(i),
                            ...error,
                          ])
                        | Belt.Result.Ok(value) =>
                          loop(i + 1, [value, ...collected], rest)
                        }
                      };
                    loop(0, [], Belt.List.fromArray(items));
                  | _ => Belt.Result.Error(["expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'people'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "pets")) {
        | None => Belt.Result.Error(["No attribute 'pets'"])
        | Some(json) =>
          switch (
            (
              list =>
                switch (Js.Json.classify(list)) {
                | JSONArray(items) =>
                  let transformer = deserialize_Types____pet;
                  let rec loop = (i, collected, items) =>
                    switch (items) {
                    | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                    | [one, ...rest] =>
                      switch (transformer(one)) {
                      | Belt.Result.Error(error) =>
                        Belt.Result.Error([
                          "list element " ++ string_of_int(i),
                          ...error,
                        ])
                      | Belt.Result.Ok(value) =>
                        loop(i + 1, [value, ...collected], rest)
                      }
                    };
                  loop(0, [], Belt.List.fromArray(items));
                | _ => Belt.Result.Error(["expected an array"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'pets'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____person:
    target => Belt.Result.t(_Types__person, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_parents => {
          let inner = attr_coords => {
            let inner = attr_age => {
              let inner = attr_name =>
                Belt.Result.Ok(
                  {
                    name: attr_name,
                    age: attr_age,
                    coords: attr_coords,
                    parents: attr_parents,
                  }: _Types__person,
                );
              switch (Js.Dict.get(dict, "name")) {
              | None => Belt.Result.Error(["No attribute 'name'"])
              | Some(json) =>
                switch (
                  (
                    string =>
                      switch (Js.Json.classify(string)) {
                      | JSONString(string) => Belt.Result.Ok(string)
                      | _ => Error(["expected a string"])
                      }
                  )(
                    json,
                  )
                ) {
                | Belt.Result.Error(error) =>
                  Belt.Result.Error(["attribute 'name'", ...error])
                | Ok(data) => inner(data)
                }
              };
            };
            switch (Js.Dict.get(dict, "age")) {
            | None => Belt.Result.Error(["No attribute 'age'"])
            | Some(json) =>
              switch (
                (
                  number =>
                    switch (Js.Json.classify(number)) {
                    | JSONNumber(number) =>
                      Belt.Result.Ok(int_of_float(number))
                    | _ => Error(["Expected a float"])
                    }
                )(
                  json,
                )
              ) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'age'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "coords")) {
          | None => Belt.Result.Error(["No attribute 'coords'"])
          | Some(json) =>
            switch (
              (
                json =>
                  switch (Js.Json.classify(json)) {
                  | JSONArray([|arg0, arg1|]) =>
                    switch (
                      (
                        number =>
                          switch (Js.Json.classify(number)) {
                          | JSONNumber(number) => Belt.Result.Ok(number)
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
                            switch (Js.Json.classify(number)) {
                            | JSONNumber(number) => Belt.Result.Ok(number)
                            | _ => Error(["Expected a float"])
                            }
                        )(
                          arg0,
                        )
                      ) {
                      | Belt.Result.Ok(arg0) => Belt.Result.Ok((arg0, arg1))
                      | Error(error) =>
                        Belt.Result.Error(["tuple element 0", ...error])
                      }
                    | Error(error) =>
                      Belt.Result.Error(["tuple element 1", ...error])
                    }
                  | _ => Belt.Result.Error(["Expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'coords'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "parents")) {
        | None => inner(None)
        | Some(json) =>
          switch (
            (
              (
                (transformer, option) =>
                  switch (Js.Json.classify(option)) {
                  | JSONNull => Belt.Result.Ok(None)
                  | _ =>
                    switch (transformer(option)) {
                    | Belt.Result.Error(error) =>
                      Belt.Result.Error(["optional value", ...error])
                    | Ok(value) => Ok(Some(value))
                    }
                  }
              )(
                json =>
                switch (Js.Json.classify(json)) {
                | JSONArray([|arg0, arg1|]) =>
                  switch (deserialize_Types____person(arg1)) {
                  | Belt.Result.Ok(arg1) =>
                    switch (deserialize_Types____person(arg0)) {
                    | Belt.Result.Ok(arg0) => Belt.Result.Ok((arg0, arg1))
                    | Error(error) =>
                      Belt.Result.Error(["tuple element 0", ...error])
                    }
                  | Error(error) =>
                    Belt.Result.Error(["tuple element 1", ...error])
                  }
                | _ => Belt.Result.Error(["Expected an array"])
                }
              )
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'parents'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____pet:
    target => Belt.Result.t(_Types__pet, list(string)) =
    constructor =>
      switch (Js.Json.classify(constructor)) {
      | JSONArray([|tag|])
          when Js.Json.JSONString("Dog") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Dog: _Types__pet)
      | JSONArray([|tag|])
          when Js.Json.JSONString("Cat") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Cat: _Types__pet)
      | _ => Belt.Result.Error(["Expected an array"])
      };
};
module Version2 = {
  open Types2;
  let rec deserialize_Types____household:
    target => Belt.Result.t(_Types__household, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_pets => {
          let inner = attr_people =>
            Belt.Result.Ok(
              {people: attr_people, pets: attr_pets}: _Types__household,
            );
          switch (Js.Dict.get(dict, "people")) {
          | None => Belt.Result.Error(["No attribute 'people'"])
          | Some(json) =>
            switch (
              (
                list =>
                  switch (Js.Json.classify(list)) {
                  | JSONArray(items) =>
                    let transformer = deserialize_Types____person;
                    let rec loop = (i, collected, items) =>
                      switch (items) {
                      | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Belt.Result.Error(error) =>
                          Belt.Result.Error([
                            "list element " ++ string_of_int(i),
                            ...error,
                          ])
                        | Belt.Result.Ok(value) =>
                          loop(i + 1, [value, ...collected], rest)
                        }
                      };
                    loop(0, [], Belt.List.fromArray(items));
                  | _ => Belt.Result.Error(["expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'people'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "pets")) {
        | None => Belt.Result.Error(["No attribute 'pets'"])
        | Some(json) =>
          switch (
            (
              list =>
                switch (Js.Json.classify(list)) {
                | JSONArray(items) =>
                  let transformer = deserialize_Types____pet;
                  let rec loop = (i, collected, items) =>
                    switch (items) {
                    | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                    | [one, ...rest] =>
                      switch (transformer(one)) {
                      | Belt.Result.Error(error) =>
                        Belt.Result.Error([
                          "list element " ++ string_of_int(i),
                          ...error,
                        ])
                      | Belt.Result.Ok(value) =>
                        loop(i + 1, [value, ...collected], rest)
                      }
                    };
                  loop(0, [], Belt.List.fromArray(items));
                | _ => Belt.Result.Error(["expected an array"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'pets'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____person:
    target => Belt.Result.t(_Types__person, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_parents => {
          let inner = attr_coords => {
            let inner = attr_age => {
              let inner = attr_name =>
                Belt.Result.Ok(
                  {
                    name: attr_name,
                    age: attr_age,
                    coords: attr_coords,
                    parents: attr_parents,
                  }: _Types__person,
                );
              switch (Js.Dict.get(dict, "name")) {
              | None => Belt.Result.Error(["No attribute 'name'"])
              | Some(json) =>
                switch (
                  (
                    string =>
                      switch (Js.Json.classify(string)) {
                      | JSONString(string) => Belt.Result.Ok(string)
                      | _ => Error(["expected a string"])
                      }
                  )(
                    json,
                  )
                ) {
                | Belt.Result.Error(error) =>
                  Belt.Result.Error(["attribute 'name'", ...error])
                | Ok(data) => inner(data)
                }
              };
            };
            switch (Js.Dict.get(dict, "age")) {
            | None => Belt.Result.Error(["No attribute 'age'"])
            | Some(json) =>
              switch (
                (
                  number =>
                    switch (Js.Json.classify(number)) {
                    | JSONNumber(number) => Belt.Result.Ok(number)
                    | _ => Error(["Expected a float"])
                    }
                )(
                  json,
                )
              ) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'age'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "coords")) {
          | None => Belt.Result.Error(["No attribute 'coords'"])
          | Some(json) =>
            switch (
              (
                json =>
                  switch (Js.Json.classify(json)) {
                  | JSONArray([|arg0, arg1|]) =>
                    switch (
                      (
                        number =>
                          switch (Js.Json.classify(number)) {
                          | JSONNumber(number) => Belt.Result.Ok(number)
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
                            switch (Js.Json.classify(number)) {
                            | JSONNumber(number) => Belt.Result.Ok(number)
                            | _ => Error(["Expected a float"])
                            }
                        )(
                          arg0,
                        )
                      ) {
                      | Belt.Result.Ok(arg0) => Belt.Result.Ok((arg0, arg1))
                      | Error(error) =>
                        Belt.Result.Error(["tuple element 0", ...error])
                      }
                    | Error(error) =>
                      Belt.Result.Error(["tuple element 1", ...error])
                    }
                  | _ => Belt.Result.Error(["Expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'coords'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "parents")) {
        | None => inner(None)
        | Some(json) =>
          switch (
            (
              (
                (transformer, option) =>
                  switch (Js.Json.classify(option)) {
                  | JSONNull => Belt.Result.Ok(None)
                  | _ =>
                    switch (transformer(option)) {
                    | Belt.Result.Error(error) =>
                      Belt.Result.Error(["optional value", ...error])
                    | Ok(value) => Ok(Some(value))
                    }
                  }
              )(
                json =>
                switch (Js.Json.classify(json)) {
                | JSONArray([|arg0, arg1|]) =>
                  switch (deserialize_Types____person(arg1)) {
                  | Belt.Result.Ok(arg1) =>
                    switch (deserialize_Types____person(arg0)) {
                    | Belt.Result.Ok(arg0) => Belt.Result.Ok((arg0, arg1))
                    | Error(error) =>
                      Belt.Result.Error(["tuple element 0", ...error])
                    }
                  | Error(error) =>
                    Belt.Result.Error(["tuple element 1", ...error])
                  }
                | _ => Belt.Result.Error(["Expected an array"])
                }
              )
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'parents'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____pet:
    target => Belt.Result.t(_Types__pet, list(string)) =
    constructor =>
      switch (Js.Json.classify(constructor)) {
      | JSONArray([|tag|])
          when Js.Json.JSONString("Dog") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Dog: _Types__pet)
      | JSONArray([|tag|])
          when Js.Json.JSONString("Cat") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Cat: _Types__pet)
      | JSONArray([|tag|])
          when Js.Json.JSONString("Mouse") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Mouse: _Types__pet)
      | _ => Belt.Result.Error(["Expected an array"])
      };
};
module Version3 = {
  open Types3;
  let rec deserialize_Types____household:
    target => Belt.Result.t(_Types__household, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_pets => {
          let inner = attr_people =>
            Belt.Result.Ok(
              {people: attr_people, pets: attr_pets}: _Types__household,
            );
          switch (Js.Dict.get(dict, "people")) {
          | None => Belt.Result.Error(["No attribute 'people'"])
          | Some(json) =>
            switch (
              (
                list =>
                  switch (Js.Json.classify(list)) {
                  | JSONArray(items) =>
                    let transformer = deserialize_Types____person;
                    let rec loop = (i, collected, items) =>
                      switch (items) {
                      | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Belt.Result.Error(error) =>
                          Belt.Result.Error([
                            "list element " ++ string_of_int(i),
                            ...error,
                          ])
                        | Belt.Result.Ok(value) =>
                          loop(i + 1, [value, ...collected], rest)
                        }
                      };
                    loop(0, [], Belt.List.fromArray(items));
                  | _ => Belt.Result.Error(["expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'people'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "pets")) {
        | None => Belt.Result.Error(["No attribute 'pets'"])
        | Some(json) =>
          switch (
            (
              list =>
                switch (Js.Json.classify(list)) {
                | JSONArray(items) =>
                  let transformer = deserialize_Types____pet;
                  let rec loop = (i, collected, items) =>
                    switch (items) {
                    | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                    | [one, ...rest] =>
                      switch (transformer(one)) {
                      | Belt.Result.Error(error) =>
                        Belt.Result.Error([
                          "list element " ++ string_of_int(i),
                          ...error,
                        ])
                      | Belt.Result.Ok(value) =>
                        loop(i + 1, [value, ...collected], rest)
                      }
                    };
                  loop(0, [], Belt.List.fromArray(items));
                | _ => Belt.Result.Error(["expected an array"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'pets'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____person:
    target => Belt.Result.t(_Types__person, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_coords => {
          let inner = attr_age => {
            let inner = attr_name =>
              Belt.Result.Ok(
                {name: attr_name, age: attr_age, coords: attr_coords}: _Types__person,
              );
            switch (Js.Dict.get(dict, "name")) {
            | None => Belt.Result.Error(["No attribute 'name'"])
            | Some(json) =>
              switch (
                (
                  string =>
                    switch (Js.Json.classify(string)) {
                    | JSONString(string) => Belt.Result.Ok(string)
                    | _ => Error(["expected a string"])
                    }
                )(
                  json,
                )
              ) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'name'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "age")) {
          | None => Belt.Result.Error(["No attribute 'age'"])
          | Some(json) =>
            switch (
              (
                number =>
                  switch (Js.Json.classify(number)) {
                  | JSONNumber(number) => Belt.Result.Ok(number)
                  | _ => Error(["Expected a float"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'age'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "coords")) {
        | None => Belt.Result.Error(["No attribute 'coords'"])
        | Some(json) =>
          switch (
            (
              json =>
                switch (Js.Json.classify(json)) {
                | JSONArray([|arg0, arg1|]) =>
                  switch (
                    (
                      number =>
                        switch (Js.Json.classify(number)) {
                        | JSONNumber(number) => Belt.Result.Ok(number)
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
                          switch (Js.Json.classify(number)) {
                          | JSONNumber(number) => Belt.Result.Ok(number)
                          | _ => Error(["Expected a float"])
                          }
                      )(
                        arg0,
                      )
                    ) {
                    | Belt.Result.Ok(arg0) => Belt.Result.Ok((arg0, arg1))
                    | Error(error) =>
                      Belt.Result.Error(["tuple element 0", ...error])
                    }
                  | Error(error) =>
                    Belt.Result.Error(["tuple element 1", ...error])
                  }
                | _ => Belt.Result.Error(["Expected an array"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'coords'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____pet:
    target => Belt.Result.t(_Types__pet, list(string)) = Version2.deserialize_Types____pet;
};
module Version4 = {
  open Types4;
  let rec deserialize_Types____dogBreed:
    target => Belt.Result.t(_Types__dogBreed, list(string)) =
    constructor =>
      switch (Js.Json.classify(constructor)) {
      | JSONArray([|tag|])
          when Js.Json.JSONString("Schnouser") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Schnouser: _Types__dogBreed)
      | JSONArray([|tag|])
          when Js.Json.JSONString("Lab") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Lab: _Types__dogBreed)
      | JSONArray([|tag|])
          when Js.Json.JSONString("Retriever") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Retriever: _Types__dogBreed)
      | JSONArray([|tag|])
          when Js.Json.JSONString("Poodle") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Poodle: _Types__dogBreed)
      | _ => Belt.Result.Error(["Expected an array"])
      }
  and deserialize_Types____household:
    target => Belt.Result.t(_Types__household, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_pets => {
          let inner = attr_people =>
            Belt.Result.Ok(
              {people: attr_people, pets: attr_pets}: _Types__household,
            );
          switch (Js.Dict.get(dict, "people")) {
          | None => Belt.Result.Error(["No attribute 'people'"])
          | Some(json) =>
            switch (
              (
                list =>
                  switch (Js.Json.classify(list)) {
                  | JSONArray(items) =>
                    let transformer = deserialize_Types____person;
                    let rec loop = (i, collected, items) =>
                      switch (items) {
                      | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Belt.Result.Error(error) =>
                          Belt.Result.Error([
                            "list element " ++ string_of_int(i),
                            ...error,
                          ])
                        | Belt.Result.Ok(value) =>
                          loop(i + 1, [value, ...collected], rest)
                        }
                      };
                    loop(0, [], Belt.List.fromArray(items));
                  | _ => Belt.Result.Error(["expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'people'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "pets")) {
        | None => Belt.Result.Error(["No attribute 'pets'"])
        | Some(json) =>
          switch (
            (
              list =>
                switch (Js.Json.classify(list)) {
                | JSONArray(items) =>
                  let transformer = deserialize_Types____pet;
                  let rec loop = (i, collected, items) =>
                    switch (items) {
                    | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                    | [one, ...rest] =>
                      switch (transformer(one)) {
                      | Belt.Result.Error(error) =>
                        Belt.Result.Error([
                          "list element " ++ string_of_int(i),
                          ...error,
                        ])
                      | Belt.Result.Ok(value) =>
                        loop(i + 1, [value, ...collected], rest)
                      }
                    };
                  loop(0, [], Belt.List.fromArray(items));
                | _ => Belt.Result.Error(["expected an array"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'pets'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____person:
    target => Belt.Result.t(_Types__person, list(string)) = Version3.deserialize_Types____person
  and deserialize_Types____pet:
    target => Belt.Result.t(_Types__pet, list(string)) =
    constructor =>
      switch (Js.Json.classify(constructor)) {
      | JSONArray([|tag, arg0|])
          when Js.Json.JSONString("Dog") == Js.Json.classify(tag) =>
        switch (
          (
            (
              (transformer, option) =>
                switch (Js.Json.classify(option)) {
                | JSONNull => Belt.Result.Ok(None)
                | _ =>
                  switch (transformer(option)) {
                  | Belt.Result.Error(error) =>
                    Belt.Result.Error(["optional value", ...error])
                  | Ok(value) => Ok(Some(value))
                  }
                }
            )(
              deserialize_Types____dogBreed,
            )
          )(
            arg0,
          )
        ) {
        | Belt.Result.Ok(arg0) =>
          Belt.Result.Ok([@implicit_arity] Dog(arg0): _Types__pet)
        | Error(error) =>
          Belt.Result.Error(["constructor argument 0", ...error])
        }
      | JSONArray([|tag|])
          when Js.Json.JSONString("Cat") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Cat: _Types__pet)
      | JSONArray([|tag|])
          when Js.Json.JSONString("Mouse") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Mouse: _Types__pet)
      | _ => Belt.Result.Error(["Expected an array"])
      };
};
module Version5 = {
  open Types5;
  let rec deserialize_Types____dogBreed:
    target => Belt.Result.t(_Types__dogBreed, list(string)) =
    constructor =>
      switch (Js.Json.classify(constructor)) {
      | JSONArray([|tag, arg0|])
          when Js.Json.JSONString("Schnouser") == Js.Json.classify(tag) =>
        switch (
          (
            string =>
              switch (Js.Json.classify(string)) {
              | JSONString(string) => Belt.Result.Ok(string)
              | _ => Error(["expected a string"])
              }
          )(
            arg0,
          )
        ) {
        | Belt.Result.Ok(arg0) =>
          Belt.Result.Ok([@implicit_arity] Schnouser(arg0): _Types__dogBreed)
        | Error(error) =>
          Belt.Result.Error(["constructor argument 0", ...error])
        }
      | JSONArray([|tag|])
          when Js.Json.JSONString("Lab") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Lab: _Types__dogBreed)
      | JSONArray([|tag|])
          when Js.Json.JSONString("Retriever") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Retriever: _Types__dogBreed)
      | JSONArray([|tag|])
          when Js.Json.JSONString("Poodle") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Poodle: _Types__dogBreed)
      | _ => Belt.Result.Error(["Expected an array"])
      }
  and deserialize_Types____household:
    target => Belt.Result.t(_Types__household, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_county => {
          let inner = attr_pets => {
            let inner = attr_people =>
              Belt.Result.Ok(
                {people: attr_people, pets: attr_pets, county: attr_county}: _Types__household,
              );
            switch (Js.Dict.get(dict, "people")) {
            | None => Belt.Result.Error(["No attribute 'people'"])
            | Some(json) =>
              switch (
                (
                  list =>
                    switch (Js.Json.classify(list)) {
                    | JSONArray(items) =>
                      let transformer = deserialize_Types____person;
                      let rec loop = (i, collected, items) =>
                        switch (items) {
                        | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                        | [one, ...rest] =>
                          switch (transformer(one)) {
                          | Belt.Result.Error(error) =>
                            Belt.Result.Error([
                              "list element " ++ string_of_int(i),
                              ...error,
                            ])
                          | Belt.Result.Ok(value) =>
                            loop(i + 1, [value, ...collected], rest)
                          }
                        };
                      loop(0, [], Belt.List.fromArray(items));
                    | _ => Belt.Result.Error(["expected an array"])
                    }
                )(
                  json,
                )
              ) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'people'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "pets")) {
          | None => Belt.Result.Error(["No attribute 'pets'"])
          | Some(json) =>
            switch (
              (
                list =>
                  switch (Js.Json.classify(list)) {
                  | JSONArray(items) =>
                    let transformer = deserialize_Types____pet;
                    let rec loop = (i, collected, items) =>
                      switch (items) {
                      | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Belt.Result.Error(error) =>
                          Belt.Result.Error([
                            "list element " ++ string_of_int(i),
                            ...error,
                          ])
                        | Belt.Result.Ok(value) =>
                          loop(i + 1, [value, ...collected], rest)
                        }
                      };
                    loop(0, [], Belt.List.fromArray(items));
                  | _ => Belt.Result.Error(["expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'pets'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "county")) {
        | None => Belt.Result.Error(["No attribute 'county'"])
        | Some(json) =>
          switch (
            (
              deserialize_Types____named(number =>
                switch (Js.Json.classify(number)) {
                | JSONNumber(number) => Belt.Result.Ok(int_of_float(number))
                | _ => Error(["Expected a float"])
                }
              )
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'county'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____named:
    type arg0.
      (target => Belt.Result.t(arg0, list(string)), target) =>
      Belt.Result.t(_Types__named(arg0), list(string)) =
    (aTransformer, record) =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_contents => {
          let inner = attr_name =>
            Belt.Result.Ok(
              {name: attr_name, contents: attr_contents}:
                                                           _Types__named(
                                                             arg0,
                                                           ),
            );
          switch (Js.Dict.get(dict, "name")) {
          | None => Belt.Result.Error(["No attribute 'name'"])
          | Some(json) =>
            switch (
              (
                string =>
                  switch (Js.Json.classify(string)) {
                  | JSONString(string) => Belt.Result.Ok(string)
                  | _ => Error(["expected a string"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'name'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "contents")) {
        | None => Belt.Result.Error(["No attribute 'contents'"])
        | Some(json) =>
          switch (aTransformer(json)) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'contents'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____person:
    target => Belt.Result.t(_Types__person, list(string)) = Version4.deserialize_Types____person
  and deserialize_Types____pet:
    target => Belt.Result.t(_Types__pet, list(string)) =
    constructor =>
      switch (Js.Json.classify(constructor)) {
      | JSONArray([|tag, arg0|])
          when Js.Json.JSONString("Dog") == Js.Json.classify(tag) =>
        switch (
          (
            (
              (transformer, option) =>
                switch (Js.Json.classify(option)) {
                | JSONNull => Belt.Result.Ok(None)
                | _ =>
                  switch (transformer(option)) {
                  | Belt.Result.Error(error) =>
                    Belt.Result.Error(["optional value", ...error])
                  | Ok(value) => Ok(Some(value))
                  }
                }
            )(
              deserialize_Types____dogBreed,
            )
          )(
            arg0,
          )
        ) {
        | Belt.Result.Ok(arg0) =>
          Belt.Result.Ok([@implicit_arity] Dog(arg0): _Types__pet)
        | Error(error) =>
          Belt.Result.Error(["constructor argument 0", ...error])
        }
      | JSONArray([|tag|])
          when Js.Json.JSONString("Cat") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Cat: _Types__pet)
      | JSONArray([|tag|])
          when Js.Json.JSONString("Mouse") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Mouse: _Types__pet)
      | _ => Belt.Result.Error(["Expected an array"])
      };
};
module Version6 = {
  open Types6;
  let rec deserialize_Types____household:
    target => Belt.Result.t(_Types__household, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_county => {
          let inner = attr_visitors => {
            let inner = attr_what => {
              let inner = attr_pets => {
                let inner = attr_people =>
                  Belt.Result.Ok(
                    {
                      people: attr_people,
                      pets: attr_pets,
                      what: attr_what,
                      visitors: attr_visitors,
                      county: attr_county,
                    }: _Types__household,
                  );
                switch (Js.Dict.get(dict, "people")) {
                | None => Belt.Result.Error(["No attribute 'people'"])
                | Some(json) =>
                  switch (
                    (
                      list =>
                        switch (Js.Json.classify(list)) {
                        | JSONArray(items) =>
                          let transformer = deserialize_Types____person;
                          let rec loop = (i, collected, items) =>
                            switch (items) {
                            | [] =>
                              Belt.Result.Ok(Belt.List.reverse(collected))
                            | [one, ...rest] =>
                              switch (transformer(one)) {
                              | Belt.Result.Error(error) =>
                                Belt.Result.Error([
                                  "list element " ++ string_of_int(i),
                                  ...error,
                                ])
                              | Belt.Result.Ok(value) =>
                                loop(i + 1, [value, ...collected], rest)
                              }
                            };
                          loop(0, [], Belt.List.fromArray(items));
                        | _ => Belt.Result.Error(["expected an array"])
                        }
                    )(
                      json,
                    )
                  ) {
                  | Belt.Result.Error(error) =>
                    Belt.Result.Error(["attribute 'people'", ...error])
                  | Ok(data) => inner(data)
                  }
                };
              };
              switch (Js.Dict.get(dict, "pets")) {
              | None => Belt.Result.Error(["No attribute 'pets'"])
              | Some(json) =>
                switch (
                  (
                    list =>
                      switch (Js.Json.classify(list)) {
                      | JSONArray(items) =>
                        let transformer = deserialize_Types____pet;
                        let rec loop = (i, collected, items) =>
                          switch (items) {
                          | [] =>
                            Belt.Result.Ok(Belt.List.reverse(collected))
                          | [one, ...rest] =>
                            switch (transformer(one)) {
                            | Belt.Result.Error(error) =>
                              Belt.Result.Error([
                                "list element " ++ string_of_int(i),
                                ...error,
                              ])
                            | Belt.Result.Ok(value) =>
                              loop(i + 1, [value, ...collected], rest)
                            }
                          };
                        loop(0, [], Belt.List.fromArray(items));
                      | _ => Belt.Result.Error(["expected an array"])
                      }
                  )(
                    json,
                  )
                ) {
                | Belt.Result.Error(error) =>
                  Belt.Result.Error(["attribute 'pets'", ...error])
                | Ok(data) => inner(data)
                }
              };
            };
            switch (Js.Dict.get(dict, "what")) {
            | None => Belt.Result.Error(["No attribute 'what'"])
            | Some(json) =>
              switch (
                (
                  deserialize_Types____what(string =>
                    switch (Js.Json.classify(string)) {
                    | JSONString(string) => Belt.Result.Ok(string)
                    | _ => Error(["expected a string"])
                    }
                  )
                )(
                  json,
                )
              ) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'what'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "visitors")) {
          | None => Belt.Result.Error(["No attribute 'visitors'"])
          | Some(json) =>
            switch (
              (
                list =>
                  switch (Js.Json.classify(list)) {
                  | JSONArray(items) =>
                    let transformer = deserialize_Types____person;
                    let rec loop = (i, collected, items) =>
                      switch (items) {
                      | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Belt.Result.Error(error) =>
                          Belt.Result.Error([
                            "list element " ++ string_of_int(i),
                            ...error,
                          ])
                        | Belt.Result.Ok(value) =>
                          loop(i + 1, [value, ...collected], rest)
                        }
                      };
                    loop(0, [], Belt.List.fromArray(items));
                  | _ => Belt.Result.Error(["expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'visitors'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "county")) {
        | None => Belt.Result.Error(["No attribute 'county'"])
        | Some(json) =>
          switch (
            (
              deserialize_Types____named(number =>
                switch (Js.Json.classify(number)) {
                | JSONNumber(number) => Belt.Result.Ok(int_of_float(number))
                | _ => Error(["Expected a float"])
                }
              )
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'county'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____named:
    type arg0.
      (target => Belt.Result.t(arg0, list(string)), target) =>
      Belt.Result.t(_Types__named(arg0), list(string)) =
    (aTransformer, record) =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_isClosed => {
          let inner = attr_contents => {
            let inner = attr_name =>
              Belt.Result.Ok(
                {
                  name: attr_name,
                  contents: attr_contents,
                  isClosed: attr_isClosed,
                }: _Types__named(arg0),
              );
            switch (Js.Dict.get(dict, "the name")) {
            | None => Belt.Result.Error(["No attribute 'the name'"])
            | Some(json) =>
              switch (
                (
                  string =>
                    switch (Js.Json.classify(string)) {
                    | JSONString(string) => Belt.Result.Ok(string)
                    | _ => Error(["expected a string"])
                    }
                )(
                  json,
                )
              ) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'the name'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "contents")) {
          | None => Belt.Result.Error(["No attribute 'contents'"])
          | Some(json) =>
            switch (aTransformer(json)) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'contents'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "isClosed")) {
        | None => Belt.Result.Error(["No attribute 'isClosed'"])
        | Some(json) =>
          switch (
            (
              bool =>
                switch (Js.Json.classify(bool)) {
                | JSONTrue => Belt.Result.Ok(true)
                | JSONFalse => Belt.Result.Ok(false)
                | _ => Belt.Result.Error(["Expected a bool"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'isClosed'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____person:
    target => Belt.Result.t(_Types__person, list(string)) = Version5.deserialize_Types____person
  and deserialize_Types____pet:
    target => Belt.Result.t(_Types__pet, list(string)) =
    constructor =>
      switch (Js.Json.classify(constructor)) {
      | JSONArray([|tag|])
          when Js.Json.JSONString("a-cat") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Dog: _Types__pet)
      | JSONArray([|tag|])
          when Js.Json.JSONString("Cat") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Cat: _Types__pet)
      | JSONArray([|tag|])
          when Js.Json.JSONString("Mouse") == Js.Json.classify(tag) =>
        Belt.Result.Ok(Mouse: _Types__pet)
      | _ => Belt.Result.Error(["Expected an array"])
      }
  and deserialize_Types____what:
    type arg0.
      (target => Belt.Result.t(arg0, list(string)), target) =>
      Belt.Result.t(_Types__what(arg0), list(string)) =
    (aTransformer, constructor) =>
      switch (Js.Json.classify(constructor)) {
      | JSONArray([|tag, arg0|])
          when Js.Json.JSONString("Now") == Js.Json.classify(tag) =>
        switch (aTransformer(arg0)) {
        | Belt.Result.Ok(arg0) =>
          Belt.Result.Ok([@implicit_arity] Now(arg0): _Types__what(arg0))
        | Error(error) =>
          Belt.Result.Error(["constructor argument 0", ...error])
        }
      | _ => Belt.Result.Error(["Expected an array"])
      };
};
module Version7 = {
  open Types7;
  let rec deserialize_Types____household:
    target => Belt.Result.t(_Types__household, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_county => {
          let inner = attr_visitors => {
            let inner = attr_what => {
              let inner = attr_pets => {
                let inner = attr_people => {
                  let inner = attr_two => {
                    let inner = attr_one =>
                      Belt.Result.Ok(
                        {
                          one: attr_one,
                          two: attr_two,
                          people: attr_people,
                          pets: attr_pets,
                          what: attr_what,
                          visitors: attr_visitors,
                          county: attr_county,
                        }: _Types__household,
                      );
                    switch (Js.Dict.get(dict, "one")) {
                    | None => Belt.Result.Error(["No attribute 'one'"])
                    | Some(json) =>
                      switch (
                        (deserialize_Types____what(deserialize_Types____one))(
                          json,
                        )
                      ) {
                      | Belt.Result.Error(error) =>
                        Belt.Result.Error(["attribute 'one'", ...error])
                      | Ok(data) => inner(data)
                      }
                    };
                  };
                  switch (Js.Dict.get(dict, "two")) {
                  | None => Belt.Result.Error(["No attribute 'two'"])
                  | Some(json) =>
                    switch (
                      (deserialize_Types____what(deserialize_Types____two))(
                        json,
                      )
                    ) {
                    | Belt.Result.Error(error) =>
                      Belt.Result.Error(["attribute 'two'", ...error])
                    | Ok(data) => inner(data)
                    }
                  };
                };
                switch (Js.Dict.get(dict, "people")) {
                | None => Belt.Result.Error(["No attribute 'people'"])
                | Some(json) =>
                  switch (
                    (
                      list =>
                        switch (Js.Json.classify(list)) {
                        | JSONArray(items) =>
                          let transformer = deserialize_Types____person;
                          let rec loop = (i, collected, items) =>
                            switch (items) {
                            | [] =>
                              Belt.Result.Ok(Belt.List.reverse(collected))
                            | [one, ...rest] =>
                              switch (transformer(one)) {
                              | Belt.Result.Error(error) =>
                                Belt.Result.Error([
                                  "list element " ++ string_of_int(i),
                                  ...error,
                                ])
                              | Belt.Result.Ok(value) =>
                                loop(i + 1, [value, ...collected], rest)
                              }
                            };
                          loop(0, [], Belt.List.fromArray(items));
                        | _ => Belt.Result.Error(["expected an array"])
                        }
                    )(
                      json,
                    )
                  ) {
                  | Belt.Result.Error(error) =>
                    Belt.Result.Error(["attribute 'people'", ...error])
                  | Ok(data) => inner(data)
                  }
                };
              };
              switch (Js.Dict.get(dict, "pets")) {
              | None => Belt.Result.Error(["No attribute 'pets'"])
              | Some(json) =>
                switch (
                  (
                    list =>
                      switch (Js.Json.classify(list)) {
                      | JSONArray(items) =>
                        let transformer = deserialize_Types____pet;
                        let rec loop = (i, collected, items) =>
                          switch (items) {
                          | [] =>
                            Belt.Result.Ok(Belt.List.reverse(collected))
                          | [one, ...rest] =>
                            switch (transformer(one)) {
                            | Belt.Result.Error(error) =>
                              Belt.Result.Error([
                                "list element " ++ string_of_int(i),
                                ...error,
                              ])
                            | Belt.Result.Ok(value) =>
                              loop(i + 1, [value, ...collected], rest)
                            }
                          };
                        loop(0, [], Belt.List.fromArray(items));
                      | _ => Belt.Result.Error(["expected an array"])
                      }
                  )(
                    json,
                  )
                ) {
                | Belt.Result.Error(error) =>
                  Belt.Result.Error(["attribute 'pets'", ...error])
                | Ok(data) => inner(data)
                }
              };
            };
            switch (Js.Dict.get(dict, "what")) {
            | None => Belt.Result.Error(["No attribute 'what'"])
            | Some(json) =>
              switch (
                (
                  deserialize_Types____what(string =>
                    switch (Js.Json.classify(string)) {
                    | JSONString(string) => Belt.Result.Ok(string)
                    | _ => Error(["expected a string"])
                    }
                  )
                )(
                  json,
                )
              ) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'what'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "visitors")) {
          | None => Belt.Result.Error(["No attribute 'visitors'"])
          | Some(json) =>
            switch (
              (
                list =>
                  switch (Js.Json.classify(list)) {
                  | JSONArray(items) =>
                    let transformer = deserialize_Types____person;
                    let rec loop = (i, collected, items) =>
                      switch (items) {
                      | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Belt.Result.Error(error) =>
                          Belt.Result.Error([
                            "list element " ++ string_of_int(i),
                            ...error,
                          ])
                        | Belt.Result.Ok(value) =>
                          loop(i + 1, [value, ...collected], rest)
                        }
                      };
                    loop(0, [], Belt.List.fromArray(items));
                  | _ => Belt.Result.Error(["expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'visitors'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "county")) {
        | None => Belt.Result.Error(["No attribute 'county'"])
        | Some(json) =>
          switch (
            (
              deserialize_Types____named(number =>
                switch (Js.Json.classify(number)) {
                | JSONNumber(number) => Belt.Result.Ok(int_of_float(number))
                | _ => Error(["Expected a float"])
                }
              )
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'county'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____named:
    type arg0.
      (target => Belt.Result.t(arg0, list(string)), target) =>
      Belt.Result.t(_Types__named(arg0), list(string)) =
    (aTransformer, record) =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_other => {
          let inner = attr_isClosed => {
            let inner = attr_contents => {
              let inner = attr_name =>
                Belt.Result.Ok(
                  {
                    name: attr_name,
                    contents: attr_contents,
                    isClosed: attr_isClosed,
                    other: attr_other,
                  }: _Types__named(arg0),
                );
              switch (Js.Dict.get(dict, "the name")) {
              | None => Belt.Result.Error(["No attribute 'the name'"])
              | Some(json) =>
                switch (
                  (
                    string =>
                      switch (Js.Json.classify(string)) {
                      | JSONString(string) => Belt.Result.Ok(string)
                      | _ => Error(["expected a string"])
                      }
                  )(
                    json,
                  )
                ) {
                | Belt.Result.Error(error) =>
                  Belt.Result.Error(["attribute 'the name'", ...error])
                | Ok(data) => inner(data)
                }
              };
            };
            switch (Js.Dict.get(dict, "contents")) {
            | None => Belt.Result.Error(["No attribute 'contents'"])
            | Some(json) =>
              switch (aTransformer(json)) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'contents'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "isClosed")) {
          | None => Belt.Result.Error(["No attribute 'isClosed'"])
          | Some(json) =>
            switch (
              (
                bool =>
                  switch (Js.Json.classify(bool)) {
                  | JSONTrue => Belt.Result.Ok(true)
                  | JSONFalse => Belt.Result.Ok(false)
                  | _ => Belt.Result.Error(["Expected a bool"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'isClosed'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "other")) {
        | None => inner(None)
        | Some(json) =>
          switch (
            (
              (
                (transformer, option) =>
                  switch (Js.Json.classify(option)) {
                  | JSONNull => Belt.Result.Ok(None)
                  | _ =>
                    switch (transformer(option)) {
                    | Belt.Result.Error(error) =>
                      Belt.Result.Error(["optional value", ...error])
                    | Ok(value) => Ok(Some(value))
                    }
                  }
              )(
                aTransformer,
              )
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'other'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____one:
    target => Belt.Result.t(_Types__one, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_key => Belt.Result.Ok({key: attr_key}: _Types__one);
        switch (Js.Dict.get(dict, "key")) {
        | None => Belt.Result.Error(["No attribute 'key'"])
        | Some(json) =>
          switch (
            (
              string =>
                switch (Js.Json.classify(string)) {
                | JSONString(string) => Belt.Result.Ok(string)
                | _ => Error(["expected a string"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'key'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____person:
    target => Belt.Result.t(_Types__person, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_coords => {
          let inner = attr_thing => {
            let inner = attr_age => {
              let inner = attr_name =>
                Belt.Result.Ok(
                  {
                    name: attr_name,
                    age: attr_age,
                    thing: attr_thing,
                    coords: attr_coords,
                  }: _Types__person,
                );
              switch (Js.Dict.get(dict, "name")) {
              | None => Belt.Result.Error(["No attribute 'name'"])
              | Some(json) =>
                switch (
                  (
                    string =>
                      switch (Js.Json.classify(string)) {
                      | JSONString(string) => Belt.Result.Ok(string)
                      | _ => Error(["expected a string"])
                      }
                  )(
                    json,
                  )
                ) {
                | Belt.Result.Error(error) =>
                  Belt.Result.Error(["attribute 'name'", ...error])
                | Ok(data) => inner(data)
                }
              };
            };
            switch (Js.Dict.get(dict, "age")) {
            | None => Belt.Result.Error(["No attribute 'age'"])
            | Some(json) =>
              switch (
                (
                  number =>
                    switch (Js.Json.classify(number)) {
                    | JSONNumber(number) => Belt.Result.Ok(number)
                    | _ => Error(["Expected a float"])
                    }
                )(
                  json,
                )
              ) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'age'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "thing")) {
          | None => Belt.Result.Error(["No attribute 'thing'"])
          | Some(json) =>
            switch (
              (
                constructor =>
                  switch (Js.Json.classify(constructor)) {
                  | JSONArray([|tag|])
                      when Js.Json.JSONString("one") == Js.Json.classify(tag) =>
                    Belt.Result.Ok(`one)
                  | JSONArray([|tag, arg0|])
                      when Js.Json.JSONString("two") == Js.Json.classify(tag) =>
                    switch (
                      (
                        number =>
                          switch (Js.Json.classify(number)) {
                          | JSONNumber(number) =>
                            Belt.Result.Ok(int_of_float(number))
                          | _ => Error(["Expected a float"])
                          }
                      )(
                        arg0,
                      )
                    ) {
                    | Belt.Result.Ok(arg) => Belt.Result.Ok(`two(arg))
                    | Error(error) => Belt.Result.Error(error)
                    }
                  | JSONArray([|tag, arg0|])
                      when
                        Js.Json.JSONString("three") == Js.Json.classify(tag) =>
                    switch (
                      (
                        json =>
                          switch (Js.Json.classify(json)) {
                          | JSONArray([|arg0, arg1|]) =>
                            switch (
                              (
                                string =>
                                  switch (Js.Json.classify(string)) {
                                  | JSONString(string) =>
                                    Belt.Result.Ok(string)
                                  | _ => Error(["expected a string"])
                                  }
                              )(
                                arg1,
                              )
                            ) {
                            | Belt.Result.Ok(arg1) =>
                              switch (
                                (
                                  number =>
                                    switch (Js.Json.classify(number)) {
                                    | JSONNumber(number) =>
                                      Belt.Result.Ok(number)
                                    | _ => Error(["Expected a float"])
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
                              Belt.Result.Error(["tuple element 1", ...error])
                            }
                          | _ => Belt.Result.Error(["Expected an array"])
                          }
                      )(
                        arg0,
                      )
                    ) {
                    | Belt.Result.Ok(arg) => Belt.Result.Ok(`three(arg))
                    | Error(error) => Belt.Result.Error(error)
                    }
                  | _ => Belt.Result.Error(["Expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'thing'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "coords")) {
        | None => Belt.Result.Error(["No attribute 'coords'"])
        | Some(json) =>
          switch (
            (
              json =>
                switch (Js.Json.classify(json)) {
                | JSONArray([|arg0, arg1|]) =>
                  switch (
                    (
                      number =>
                        switch (Js.Json.classify(number)) {
                        | JSONNumber(number) => Belt.Result.Ok(number)
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
                          switch (Js.Json.classify(number)) {
                          | JSONNumber(number) => Belt.Result.Ok(number)
                          | _ => Error(["Expected a float"])
                          }
                      )(
                        arg0,
                      )
                    ) {
                    | Belt.Result.Ok(arg0) => Belt.Result.Ok((arg0, arg1))
                    | Error(error) =>
                      Belt.Result.Error(["tuple element 0", ...error])
                    }
                  | Error(error) =>
                    Belt.Result.Error(["tuple element 1", ...error])
                  }
                | _ => Belt.Result.Error(["Expected an array"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'coords'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____pet:
    target => Belt.Result.t(_Types__pet, list(string)) = Version6.deserialize_Types____pet
  and deserialize_Types____two:
    target => Belt.Result.t(_Types__two, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_key => Belt.Result.Ok({key: attr_key}: _Types__two);
        switch (Js.Dict.get(dict, "key")) {
        | None => Belt.Result.Error(["No attribute 'key'"])
        | Some(json) =>
          switch (
            (
              string =>
                switch (Js.Json.classify(string)) {
                | JSONString(string) => Belt.Result.Ok(string)
                | _ => Error(["expected a string"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'key'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____what:
    type arg0.
      (target => Belt.Result.t(arg0, list(string)), target) =>
      Belt.Result.t(_Types__what(arg0), list(string)) =
    (aTransformer, constructor) =>
      switch (Js.Json.classify(constructor)) {
      | JSONArray([|tag, arg0, arg1|])
          when Js.Json.JSONString("Now") == Js.Json.classify(tag) =>
        switch (
          (
            number =>
              switch (Js.Json.classify(number)) {
              | JSONNumber(number) => Belt.Result.Ok(int_of_float(number))
              | _ => Error(["Expected a float"])
              }
          )(
            arg1,
          )
        ) {
        | Belt.Result.Ok(arg1) =>
          switch (aTransformer(arg0)) {
          | Belt.Result.Ok(arg0) =>
            Belt.Result.Ok(
              [@implicit_arity] Now(arg0, arg1): _Types__what(arg0),
            )
          | Error(error) =>
            Belt.Result.Error(["constructor argument 0", ...error])
          }
        | Error(error) =>
          Belt.Result.Error(["constructor argument 1", ...error])
        }
      | _ => Belt.Result.Error(["Expected an array"])
      }
  and serialize_Types____household: _Types__household => target =
    record =>
      Js.Json.object_(
        Js.Dict.fromArray([|
          (
            "one",
            (serialize_Types____what(serialize_Types____one))(record.one),
          ),
          (
            "two",
            (serialize_Types____what(serialize_Types____two))(record.two),
          ),
          (
            "people",
            (
              list =>
                Js.Json.array(
                  Belt.List.toArray(
                    Belt.List.map(list, serialize_Types____person),
                  ),
                )
            )(
              record.people,
            ),
          ),
          (
            "pets",
            (
              list =>
                Js.Json.array(
                  Belt.List.toArray(
                    Belt.List.map(list, serialize_Types____pet),
                  ),
                )
            )(
              record.pets,
            ),
          ),
          ("what", (serialize_Types____what(Js.Json.string))(record.what)),
          (
            "visitors",
            (
              list =>
                Js.Json.array(
                  Belt.List.toArray(
                    Belt.List.map(list, serialize_Types____person),
                  ),
                )
            )(
              record.visitors,
            ),
          ),
          (
            "county",
            (
              serialize_Types____named(int =>
                Js.Json.number(float_of_int(int))
              )
            )(
              record.county,
            ),
          ),
        |]),
      )
  and serialize_Types____named:
    'arg0.
    ('arg0 => target, _Types__named('arg0)) => target
   =
    (aTransformer, record) =>
      Js.Json.object_(
        Js.Dict.fromArray([|
          ("the name", Js.Json.string(record.name)),
          ("contents", aTransformer(record.contents)),
          ("isClosed", Js.Json.boolean(record.isClosed)),
          (
            "other",
            (
              (
                transformer =>
                  fun
                  | Some(inner) => transformer(inner)
                  | None => Js.Json.null
              )(
                aTransformer,
              )
            )(
              record.other,
            ),
          ),
        |]),
      )
  and serialize_Types____one: _Types__one => target =
    record =>
      Js.Json.object_(
        Js.Dict.fromArray([|("key", Js.Json.string(record.key))|]),
      )
  and serialize_Types____person: _Types__person => target =
    record =>
      Js.Json.object_(
        Js.Dict.fromArray([|
          ("name", Js.Json.string(record.name)),
          ("age", Js.Json.number(record.age)),
          (
            "thing",
            (
              constructor =>
                switch (constructor) {
                | `one => Js.Json.array([|Js.Json.string("one")|])
                | `two(arg) =>
                  Js.Json.array([|
                    Js.Json.string("two"),
                    (int => Js.Json.number(float_of_int(int)))(arg),
                  |])
                | `three(arg) =>
                  Js.Json.array([|
                    Js.Json.string("three"),
                    (
                      ((arg0, arg1)) =>
                        Js.Json.array([|
                          Js.Json.number(arg0),
                          Js.Json.string(arg1),
                        |])
                    )(
                      arg,
                    ),
                  |])
                }
            )(
              record.thing,
            ),
          ),
          (
            "coords",
            (
              ((arg0, arg1)) =>
                Js.Json.array([|
                  Js.Json.number(arg0),
                  Js.Json.number(arg1),
                |])
            )(
              record.coords,
            ),
          ),
        |]),
      )
  and serialize_Types____pet: _Types__pet => target =
    constructor =>
      switch (constructor) {
      | Dog => Js.Json.array([|Js.Json.string("a-cat")|])
      | Cat => Js.Json.array([|Js.Json.string("Cat")|])
      | Mouse => Js.Json.array([|Js.Json.string("Mouse")|])
      }
  and serialize_Types____two: _Types__two => target =
    record =>
      Js.Json.object_(
        Js.Dict.fromArray([|("key", Js.Json.string(record.key))|]),
      )
  and serialize_Types____what:
    'arg0.
    ('arg0 => target, _Types__what('arg0)) => target
   =
    (aTransformer, constructor) =>
      switch (constructor) {
      | [@implicit_arity] Now(arg0, arg1) =>
        Js.Json.array([|
          Js.Json.string("Now"),
          aTransformer(arg0),
          (int => Js.Json.number(float_of_int(int)))(arg1),
        |])
      };
};
module Current = Version7;
let parseVersion = json =>
  switch (Js.Json.classify(json)) {
  | JSONObject(dict) =>
    switch (Js.Dict.get(dict, "$schemaVersion")) {
    | Some(schemaVersion) =>
      switch (Js.Json.classify(schemaVersion)) {
      | JSONNumber(version) =>
        [@implicit_arity] Belt.Result.Ok(int_of_float(version), json)
      | _ => Belt.Result.Error("Invalid $schemaVersion")
      }
    | None => Belt.Result.Error("No $schemaVersion present")
    }
  | JSONArray([|version, payload|]) =>
    switch (Js.Json.classify(version)) {
    | JSONNumber(version) =>
      [@implicit_arity] Belt.Result.Ok(int_of_float(version), payload)
    | _ => Belt.Result.Error("Invalid wrapped version")
    }
  | _ => Belt.Result.Error("Must have a schema version")
  };
let wrapWithVersion = (version, payload) =>
  switch (Js.Json.classify(payload)) {
  | JSONObject(dict) =>
    Js.Dict.set(
      dict,
      "$schemaVersion",
      Js.Json.number(float_of_int(version)),
    );
    Js.Json.object_(dict);
  | _ => Js.Json.array([|Js.Json.number(float_of_int(version)), payload|])
  };
let serializeHousehold = data =>
  wrapWithVersion(
    currentVersion,
    Version7.serialize_Types____household(data),
  )
and deserializeHousehold = data =>
  switch (parseVersion(data)) {
  | Belt.Result.Error(err) => Belt.Result.Error([err])
  | [@implicit_arity] Ok(version, data) =>
    switch (version) {
    | 7 =>
      switch (Version7.deserialize_Types____household(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) => Belt.Result.Ok(data)
      }
    | 6 =>
      switch (Version6.deserialize_Types____household(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) =>
        let data = Types7.migrate_Types____household(data);
        Belt.Result.Ok(data);
      }
    | 5 =>
      switch (Version5.deserialize_Types____household(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) =>
        let data = Types6.migrate_Types____household(data);
        let data = Types7.migrate_Types____household(data);
        Belt.Result.Ok(data);
      }
    | 4 =>
      switch (Version4.deserialize_Types____household(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) =>
        let data = Types5.migrate_Types____household(data);
        let data = Types6.migrate_Types____household(data);
        let data = Types7.migrate_Types____household(data);
        Belt.Result.Ok(data);
      }
    | 3 =>
      switch (Version3.deserialize_Types____household(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) =>
        let data = Types4.migrate_Types____household(data);
        let data = Types5.migrate_Types____household(data);
        let data = Types6.migrate_Types____household(data);
        let data = Types7.migrate_Types____household(data);
        Belt.Result.Ok(data);
      }
    | 2 =>
      switch (Version2.deserialize_Types____household(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) =>
        let data = Types3.migrate_Types____household(data);
        let data = Types4.migrate_Types____household(data);
        let data = Types5.migrate_Types____household(data);
        let data = Types6.migrate_Types____household(data);
        let data = Types7.migrate_Types____household(data);
        Belt.Result.Ok(data);
      }
    | 1 =>
      switch (Version1.deserialize_Types____household(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) =>
        let data = Types2.migrate_Types____household(data);
        let data = Types3.migrate_Types____household(data);
        let data = Types4.migrate_Types____household(data);
        let data = Types5.migrate_Types____household(data);
        let data = Types6.migrate_Types____household(data);
        let data = Types7.migrate_Types____household(data);
        Belt.Result.Ok(data);
      }
    | _ =>
      Belt.Result.Error(["Unexpected version " ++ string_of_int(version)])
    }
  };
module Modules = {
  module Household = {
    type t = Types7._Types__household;
    let serialize = serializeHousehold;
    let deserialize = deserializeHousehold;
  };
};
