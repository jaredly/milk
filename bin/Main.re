
open Milk;

let docs = {|
Milk 🥛 : Stress-free serialization & deserialization for Reason/OCaml

Usage: milk [config file] [options]

If no config file is provided, `types.json` will be used if it exists,
otherwise the `milk` section of esy.json or package.json will be used if
it exists.

Options:

- --init     : create a new config file for the current project

(rarely used)

- --override : Ignore current lockfile version, overriding conflicts.
               NOTE: This should only be passed if you have not stored any
               data using the currently generated serde, as it may now be
               unparseable.
- --upvert   : Convert a legacy config file (generated with a previous
               version of milk) to the current schema.

|};

let die = text => {
  print_endline("Error: " ++ text);
  // print_newline();
  print_endline(docs);
  exit(1);
};

let help = () => {
  print_endline(docs);
  exit(1);
};

let rec parse = argv => switch (argv) {
  | [] => (None, [])
  | [arg, ...rest] when (arg != "" && arg.[0] == '-') =>
    let (config, opts) = parse(rest);
    (config, [arg, ...opts])
  | [arg, ...rest] =>
    let (config, opts) = parse(rest);
    if (config == None) {
      (Some(arg), opts)
    } else {
      die("Multiple non-option arguments given. At most one expected (the config file)")
    }
};

let readOrDie = configPath => {
  let text = try (Util.Files.readFileExn(configPath)) {
    | _ => die("Unable to read " ++ configPath)
  };
  try (Json.parse(text)) {
    | _ => die("Invalid JSON in " ++ configPath)
  }
};

let getNested = (json, fname) => {
  switch (json |> Json.get("milk")) {
    | None => die("No 'milk' section found in " ++ fname)
    | Some(json) => json
  }
};

let args = switch (Sys.argv->Belt.List.fromArray) {
  | [_, ...args] => args
  | [] => []
};

switch (parse(args)) {
  | (_, opts) when opts->Belt.List.some(arg => arg == "-h" || arg == "--help") => help();
  | (config, opts) when opts->Belt.List.some(arg => arg == "--init") =>
    Milk.init(switch config {
      | None => "types.json"
      | Some(config) => config
    })
  | (config, opts) =>

if (opts->Belt.List.has("-v", (==))) {

    Util.Log.spamError := true;
    Util.MerlinFile.debug := true;
};
    let (json, configPath) = switch config {
      | None =>
        if (Files.exists("types.json")) {
          (readOrDie("types.json"), `Top("types.json"))
        } else if (Files.exists("esy.json")) {
          (readOrDie("esy.json")->getNested("esy.json"), `Nested("esy.json"))
        } else if (Files.exists("package.json")) {
          (readOrDie("package.json")->getNested("package.json"), `Nested("package.json"))
        } else {
          die("No config file provided")
        };
      | Some(config) => (readOrDie(config), `Top(config))
    };
    let override = opts->Belt.List.has("--override", (==));
    let upvert = opts->Belt.List.has("--upvert", (==));
    main(~override, ~upvert, ~json, configPath)
};