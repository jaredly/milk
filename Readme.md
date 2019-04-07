
# Milk 🥛 : Stress-free serialization & deserialization for Reason/OCaml

🚧 **Stability: settling** 🚧 This is recently released, still settling down API n stuff, but I plan to maintain backwards compatability. Also I'm still working on documentation, so some things might be missing or unclear.

```
Usage: milk [config file] [options]

If no config file is provided, `types.json` will be used if it exists,
otherwise the `milk` section of esy.json or package.json will be used if
it exists.

Options: (rarely used)

- --override : Ignore current lockfile version, overriding conflicts.
               NOTE: This should only be passed if you have not stored any
               data using the currently generated serde, as it may now be
               unparseable.
- --upvert   : Convert a legacy config file (generated with a previous
               version of milk) to the current schema.
```

## Configuration

This goes either in a separate JSON file (e.g. `types.json`), or in a `"milk"` section of your `esy.json` or `package.json`.

#### Example `types.json`:

```
{
  "$schemaVersion": 2,
  "version": 1,
  "engines": {
    "bs.json": {
      "output": "./src/Serde.re"
    }
  },
  "entries": [
    {
      "file": "./src/Types.re",
      "type": "config"
    },
    {
      "file": "./src/Node.re",
      "type": "t",
      "publicName": "node"
    }
  ]
}
```

See the `types.json` in this repo for another example, or [this one over here](https://github.com/notablemind/renm/blob/74034cb0cbd68b31c997548453d45d995c22d2b7/types.json).

#### Full spec:

- `$schemaVersion: int` this is the milk config file schema version. The latest version is `2` (the one documented here).
- `version: int` : this is the version of your types. When you serialize anything, it will have this version attached to it, so that the data can be deserialized in the future & migrated through any subsequent versions. When you make a "breaking change" (see below for details), you'll need to increment this version number, and provide any necessary migrator functions (see below for migration details).
- `lockedTypes: string` : If you have multiple engines defined, then this is required, otherwise it's optional. This file is where all of the types for all of the versions that exist in your lockfile will be generated, for use by deserialization and migration functions.
- `engines: {[key: engine_name]: engineConfig}` : a mapping of `engine_name` to `engineConfig`, where `engine_name` is one of `rex_json`, `bs_json`, `ezjsonm`, and `yojson`.
  - `engineConfig: {output: string, helpers: option(string)}`. Output is the file where the serializer & deserializer functions should be output to, and `helpers` is the name of the module that contains any necessary `TransformHelpers` (see below)
- `entries: list(entry)` : the list of your "entry point" types. These are the types that you want to be able to serialize & deserialize.
    - `file: string` the source file where this type is defined
    - `type: string` the name of the type within the file, including containing submodules. e.g. `someType` if it's at the top level, or `SomeModule.InnerModule.t` if it's nested.
    - `publicName: string` the name that will be used in the externally usable serialization & deserialization functions. e.g. if your type name is `t`, having a function called `deserializeT` won't be super helpful, so you can put `publicName: "animal"` and you'll get `deserializeAnimal`
- `custom: list(custom)`. "Custom" types are types for which you want to be treated as opaque -- milk will not generate ser/de functions for them, and you will provide those in the `helpers` module(s).
  - `module: string` the module name the contains the type you want to override. e.g. `Animals`
  - `path: list(string)` the path within the module, if there's nesting. If the type is `Animals.Dogs.t`, this would be `["Dogs"]`
  - `name: string` the name of the type to override. e.g. `t`
  - `args: int` the number of type arguments that the type has.

# How does it work?

Milk has two phases. 1) generate/update lockfile. 2) generate serialization, migration, and deserialization code for all known types & versions.

## Generate/update lockfile

A lockfile consists of an array of "locked type maps", each corresponding to a "version" of your types.
A "locked type map" is a map from a "module path" (like `MyModule.SubModule.typename`) to a serialization of the type declaration, including any `@attributes`.

Milk first creates a "locked type map" for the current state of your types, starting with your "entry types", and recursively following any type references down to their definitions.
Then, if there's a current lockfile & the version in `types.json` has not been incremented, it checks for incompatible changes & errors out in that case. If the changes are compatible (see below), it overwrites the locked type map, and if the version number has been incremented since the last type Milk was run, it appends the type map to the array.
The whole array is then written out to the lockfile.

## Generate code!

First, the "locked types" are generated. For each version, a `TypesN` module is created that contains the type definition for every type needed to fully define all of the entry types for that version. The final (current) version also aliases those type definitions to the definitions used in the rest of your app. Also, migration functions are auto-generated (if possible), or referenced (if defined as decorators, see below). If a migration function cannot be auto-generated, and has not been provided, Milk errors out with a message indicating the migration function that's missing.

With the "locked types" modules, Milk is able to create type-safe deserializers for all previous versions of your types, after you have made changes to the types used in the rest of your app.

Next, deserialization functions are created (recursively) for all versions in the lockfile.

Then, serialization functions are created for the latest version.

Finally, "entry point" `serializeThing` and `deserializeThing` functions are created, with the deserialize function checking the schema version of the data passed in, and performing any necessary migrations to get it up to the current version of the type.

## Migrations!

When you make a backwards-incompatible change (see below) to a type, you must provide functions to migrate from the previous version to the current version, in the form of `[@` decorators.

For a "whole type" migration, provide a function as a `[@migrate ]` decorator that takes data of the old type and returns data of the new type.

```re
// previous type definition
type person = {name: string, age: int};
// new type, with decorator
[@migrate ({name, age}) => {name, age: float_of_int(age), favoriteColor: None}]
type person = {name: string, age: float, favoriteColor: option(string)};
```

### Records

You can also provide migrator functions on an attribute basis, which is especially helpful if the type is large.
```re
// previous type definition
type person = {name: string, age: int};
// new type, with decorator
[@migrate.age person => float_of_int(person.age)]
[@migrate.favoriteColor (_) => None]
type person = {name: string, age: float, favoriteColor: option(string)};
```

Note that the per-attribute migration function takes the whole previous record as the argument, so that you can provide migrators for newly added attributes as well.

### Variants

If you remove a constructor from a variant, or modify a constuctor, you can provide a per-constructor migrator. The "function" that you're passing in actually gets dissected and turned into a case of a `switch` block, so keep that in mind (which is why I'm deconstructing the individual case in the function argument, which would usually cause problems).

```re
// previous type definition
type animal = Dog(string) | Cat | Mouse;
// new type definition
[@migrate.Dog (Dog(breed)) => Dog(breed, None)]
[@migrate.Mouse (Mouse) => Cat] // yeah this doesn't make sense as a migration to me either
type animal = Dog(string, option(int)) | Cat;
```

## What type changes are "compatible"
(e.g. don't require a version bump)

- *adding* a constructor to a variant type
- *adding* a row to a polymorphic variant type (TODO not yet supported)
- *adding* a new "entry" type
- *adding* an optional attribute for a record (will default to None)
- *removing* an attribute from a record

