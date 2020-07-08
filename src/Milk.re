open Migrate_parsetree.Ast_407;
Printexc.record_backtrace(true);
open Analyze;
module Json = Vendor.Json;
module Locked = TypeMapSerde.Config.Locked;
let loc = Location.none;
open DigUtils;

// let optimiseLater = (timeout, closure) => {
//   let start = Unix.gettimeofday();
//   let result = closure();
//   let time = Unix.gettimeofday() -. start;
//   if (time > timeout) {
//     print_endline("This took too long! " ++ string_of_float(time))
//   };
//   result
// };

open TypeMapSerde.Config;

let loadTypeMap = config => {
  let state = TopTypes.forRootPath(Sys.getcwd());

  let tbl = Hashtbl.create(10);

  config.custom
  ->Belt.List.forEach(({path, name, module_, args}) =>
      Hashtbl.replace(
        tbl,
        (module_, path, name),
        (
          [],
          SharedTypes.SimpleType.{
            name,
            variables: {
              switch (args) {
              | None => []
              | Some(0) => []
              | Some(args) =>
                let rec loop = n =>
                  n <= 0
                    ? []
                    : [
                      SharedTypes.SimpleType.Variable(
                        "arg" ++ string_of_int(args - n),
                      ),
                      ...loop(n - 1),
                    ];
                loop(args);
              };
            },
            body: Abstract,
          },
        ),
      )
    );

  let globalEngines =
    switch (config.globalEngines) {
    | None =>
      switch (config.engines->activeEngines) {
      | [] => failwith("No engines specified")
      | engines => engines
      }
    | Some(engines) => engines
    };

  let lockedEntries =
    config.entries
    ->Belt.List.map(({file, type_, engines}) => {
        print_endline(">> Locking " ++ file);
        let%try_force (moduleName, modulePath, name) =
          TypeMap.GetTypeMap.forInitialType(
            ~tbl,
            ~state,
            Utils.toUri(Filename.concat(Sys.getcwd(), file)),
            type_,
          );
        print_endline(">> Got map " ++ file);
        {
          Locked.moduleName,
          modulePath,
          name,
          engines:
            (
              switch (engines) {
              | None => globalEngines
              | Some(engines) => engines
              // TODO: use the real engine version
              }
            )
            ->Belt.List.map(engine => (engine, 1)),
        };
      });

  print_endline("To simple map now");
  let x = TypeMap.GetTypeMap.toSimpleMap(tbl);
  print_endline("Did it");
  (state, x, lockedEntries);
};

// let isSerializationAttribute = (({Location.txt}, _)) => Util.Utils.startsWith(txt, "rename.");

let makeLockfilePath = configPath => {
  switch (configPath) {
  | `Nested(name) => "types.lock.json"
  | `Top(configPath) =>
    let base = Filename.dirname(configPath);
    let name = Filename.basename(configPath);
    let parts = String.split_on_char('.', name);
    let newName =
      switch (parts) {
      | [single, ..._] => single ++ ".lock.json"
      | [] => "lockfile.json"
      };
    Filename.concat(base, newName);
  };
};

module ToCurrent =
  Migrate_parsetree.Convert(
    Migrate_parsetree.OCaml_407,
    Migrate_parsetree.OCaml_408,
  );
let outputStructure = (~fileName, ~structure) => {
  let structure = ToCurrent.copy_structure(structure);
  if (fileName->Filename.check_suffix(".re")) {
    let reason_structure =
      Reason_toolchain.From_current.copy_structure(structure);
    Reason_toolchain.RE.print_implementation_with_comments(
      Format.str_formatter,
      (reason_structure, []),
    );
  } else {
    Pprintast.structure(Format.str_formatter, structure);
  };

  Files.writeFile(fileName, Format.flush_str_formatter()) |> ignore;
};

let init = dest => {
  let json = TypeMapSerde.configToJson(TypeMapSerde.Config.empty);
  Files.writeFileExn(dest, Json.stringifyPretty(~indent=2, json));
};

let main = (~upvert=false, ~override=false, ~json, configPath) => {
  // let json = Json.parse(Util.Files.readFileExn(configPath));
  let%try_force config =
    switch (TypeMapSerde.configFromJson(json)) {
    | Error(m) => Error(String.concat("::", m))
    | Ok(v) => Ok(v)
    };
  TypeMapSerde.checkVersion(~upvert, ~configPath, config, json);

  let (state, currentTypeMap, lockedEntries) = loadTypeMap(config);
  print_endline("loaded");

  let engines =
    TypeMapSerde.Config.engineConfigs(config.engines)
    ->Belt.List.map(((engine, config)) =>
        (
          switch (engine) {
          | Bs_json => ((module Serde.BsJson): (module Serde.Engine.T))
          | Rex_json => ((module Serde.Json): (module Serde.Engine.T))
          | Ezjsonm => ((module Serde.Ezjsonm): (module Serde.Engine.T))
          | Yojson => ((module Serde.Yojson): (module Serde.Engine.T))
          },
          config,
        )
      );

  let lockFilePath = makeLockfilePath(configPath);
  print_endline("a");

  let lockfile =
    Lockfile.parseLockfile(
      ~override,
      config,
      lockedEntries,
      currentTypeMap,
      lockFilePath,
    );
  print_endline("b");

  let lockedDeep =
    Belt.Array.concat(
      [|Hashtbl.create(0)|],
      lockfile.versions
      ->Belt.Array.mapWithIndex((_index, config) => {
          print_endline("c1");

          Lockdown.typesAndDependencies(config.typeMap);
        }),
    );

  print_endline("c");
  let typeModules = {
    let rec loop = version =>
      version > config.version
        ? []
        : {
          [
            TypesFile.makeModule(
              ~currentVersion=config.version,
              ~lockedDeep,
              ~lockfile,
              version,
              lockfile->Locked.getVersion(version).typeMap,
            ),
            ...loop(version + 1),
          ];
        };
    loop(1);
  };

  print_endline("d");
  let makeEngineModules = (engine, helpers) => {
    let rec loop = version =>
      version > config.version
        ? []
        : {
          [
            SerdeFile.makeFullModule(
              ~helpers,
              ~engine,
              ~currentVersion=config.version,
              ~lockedDeep,
              ~lockfile,
              version,
              lockfile->Locked.getVersion(version),
            ),
            ...loop(version + 1),
          ];
        };
    module Engine = (val engine: Serde.Engine.T);
    Parsetree.(
      [%str
        type target = [%t Engine.target];
        let schemaPropertyName =
          switch%e (config.schemaPropertyName) {
          | None =>
            %expr
            "$schemaVersion"
          | Some(name) => Ast_helper.Exp.constant(Pconst_string(name, None))
          }
      ]
      @ Engine.preamble
      @ loop(1)
      @ [%str
        module Current = [%m
          Ast_helper.Mod.ident(
            Location.mknoloc(
              Longident.Lident(versionModuleName(config.version)),
            ),
          )
        ];
        let parseVersion = [%e Engine.deserializeTransformer.parseVersion];
        let wrapWithVersion = [%e Engine.serializeTransformer.wrapWithVersion]
      ]
    );
  };

  print_endline("e");
  let typeModuleStructures =
    typeModules
    @ Parsetree.[
        [%stri
          let currentVersion = [%e
            Ast_helper.Exp.constant(
              Parsetree.Pconst_integer(string_of_int(config.version), None),
            )
          ]
        ],
      ];
  let warning = Parsetree.[[%stri [@ocaml.warning "-34-39"]]];

  print_endline("f");
  switch (engines, config.lockedTypes) {
  | ([(engine, {output, helpers})], None) =>
    let body =
      warning @ typeModuleStructures @ makeEngineModules(engine, helpers);

    let converters = SerdeFile.makeConverters(~config, ~state);
    let structure =
      body @ converters @ SerdeFile.makeSubModules(~config, ~state);

    outputStructure(~fileName=output, ~structure);
  | (_multiple, None) =>
    failwith(
      "When you specify multiple engines, you must provide an `lockedTypes` file",
    )
  | (multiple, Some(lockedTypes)) =>
    outputStructure(
      ~fileName=lockedTypes,
      ~structure=warning @ typeModuleStructures,
    );
    let lockedTypesModule =
      Filename.basename(lockedTypes)
      ->Stdlib.Filename.remove_extension
      ->String.capitalize_ascii;
    multiple->Belt.List.forEach(((engine, {output, helpers})) => {
      let body =
        warning
        @ [
          Ast_helper.Str.open_(
            Ast_helper.Opn.mk(
              Location.mknoloc(Longident.Lident(lockedTypesModule)),
            ),
          ),
        ]
        @ makeEngineModules(engine, helpers);
      let converters = SerdeFile.makeConverters(~config, ~state);
      let structure =
        body @ converters @ SerdeFile.makeSubModules(~config, ~state);
      outputStructure(~fileName=output, ~structure);
    });
  };

  print_endline("g");
  let lockfileJson = TypeMapSerde.lockfileToJson(lockfile);
  Files.writeFileExn(
    lockFilePath,
    Json.stringifyPretty(~indent=2, lockfileJson),
  );
};
