let typesAndDependencies = tbl => {
  let collector = Hashtbl.create(10);

  let rec loop = source =>
    if (!Hashtbl.mem(collector, source)) {
      let (_attributes, decl) = Hashtbl.find(tbl, source);
      collector->Hashtbl.replace(source, `Reference(source));

      let sources =
        SharedTypes.SimpleType.usedSources(decl)
        ->Belt.List.keepMap(source =>
            switch (source) {
            | TypeMap.DigTypes.NotFound(_) => None
            // assert(false)
            | Builtin(_) => None
            | Public(s) => Some(s)
            }
          );
      sources->Belt.List.forEach(loop);

      let contents =
        sources->Belt.List.reduce([`Plain(decl)], (result, source) =>
          switch (collector->Hashtbl.find(source)) {
          | `Reference(what) => [`Reference(what), ...result]
          | `Resolved(items) => items @ result
          }
        );

      collector->Hashtbl.replace(source, `Resolved(contents));
    };

  Hashtbl.iter((key, _value) => loop(key), tbl);

  let collected = Hashtbl.create(10);
  collector
  |> Hashtbl.iter((key, value) =>
       switch (value) {
       | `Resolved(items) => collected->Hashtbl.replace(key, items)
       | _ => assert(false)
       }
     );

  // Printexc.

  let resolve = (source, items) => {
    // print_endline("Resolve " ++ string_of_int(List.length(items)));
    // print_endline(
    //   Printexc.raw_backtrace_to_string(Printexc.get_callstack(100)),
    // );
    let (unresolved, contents) =
      List.fold_left(
        ((unresolved, contents), item) =>
          switch (item) {
          | `Reference(inner) when inner == source => (unresolved, contents)
          | `Reference(inner) => (
              true,
              collected->Hashtbl.find(inner) @ contents,
            )
          | `Plain(x) => (unresolved, [`Plain(x), ...contents])
          },
        (false, []),
        items,
      );
    // print_endline("Resolve1");
    Hashtbl.replace(collected, source, contents);
    // print_endline("< Resolve");
    unresolved;
  };

  let rec loop = i => {
    let unresolved =
      Hashtbl.to_seq(collected)->List.of_seq
      |> List.fold_left(
           (unresolved, (k, v)) => resolve(k, v) || unresolved,
           false,
         );
    // let unresolved =
    //   Hashtbl.fold((k, v, unresolved) => resolve(k, v) || unresolved, collected, false);
    if (unresolved) {
      if (i > 1000) {
        failwith("Failed to resolve in 1000 iterations");
      };
      loop(i + 1);
    };
  };
  loop(0);

  let resolved = Hashtbl.create(10);
  collected
  |> Hashtbl.iter((k, v) =>
       resolved->Hashtbl.replace(
         k,
         v
         ->Belt.List.map(item =>
             switch (item) {
             | `Plain(x) => x
             | `Reference(_inner) => failwith("Unresolved reference")
             }
           )
         ->Belt.List.sort(compare),
       )
     );
  resolved;
};
