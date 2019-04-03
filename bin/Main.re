
open Milk;

switch (Sys.argv->Belt.List.fromArray) {
| [_, config] => main(config)
| [_, config, "--override"] => main(~override=true, config)
| [_, config, "--upvert"] => main(~upvert=true, config)
| _ => print_endline({|
Milk 🥛 : Stress-free serialization & deserialization for Reason/OCaml
|})
};