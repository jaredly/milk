let lockfileToJson = Serde.serializeSerializableLockfile;
let lockfileFromJson = Serde.deserializeSerializableLockfile;

let configToJson = Serde.serializeT;
let configFromJson = Serde.deserializeT;

let checkVersion = (~upvert, ~configPath, config, json) => {
  let version = Serde.parseVersion(json);
  switch (version) {
  | Ok((version, _)) when version != Serde.currentVersion =>
    if (upvert) {
      switch configPath {
        | `Nested(otherPath) =>
          try {
            let json = Json.parse(Files.readFileExn(otherPath));
            let json = switch json {
              | Json.Object(items) =>
                let newConfig = configToJson(config);
                let rec loop = items => switch items {
                  | [("milk", _), ...rest] => [("milk", newConfig), ...rest]
                  | [one, ...rest] => [one, ...loop(rest)]
                  | [] => failwith("milk section not found")
                };
                loop(items)
              | _ => failwith("Invalid config")
            };
            Util.Files.writeFileExn(otherPath, Vendor.Json.stringifyPretty(Json.Object(json)));
          } {
            | _ => print_endline("Failed to upvert your nested configuration in " ++ otherPath)
          };
          // print_endline("Unable to upvert nested config just yet")
        | `Top(configPath) =>
          Util.Files.writeFileExn(configPath, Vendor.Json.stringifyPretty(configToJson(config)));
      }
    } else {
      print_endline("Notice: You're using an outdated config schema. To upvert, pass --upvert.");
    }
  | _ => ()
  };
};

let dumpExpr = Serde.serializeSimpleExpr;
let dumpDecl = Serde.serializeSimpleDeclaration;
let parseVersion = Serde.parseVersion;

module Config = Config;