open Parsetree;

type ctx = {
  full: SharedTypes.full,
  state: Analyze.TopTypes.state,
  package: Analyze.TopTypes.package,
};

let mapStr = (structure, strMapper) => {
  let mapper = {
    ...Ast_mapper.default_mapper,
    structure_item: (mapper, str) =>
      switch (strMapper(mapper, str)) {
      | None => Ast_mapper.default_mapper.structure_item(mapper, str)
      | Some(str) => str
      },
  };
  mapper.structure(mapper, structure);
};

let mapExpr = (expr, exprMapper) => {
  let mapper = {
    ...Ast_mapper.default_mapper,
    expr: (mapper, expr) =>
      switch (exprMapper(mapper, expr)) {
      | None => Ast_mapper.default_mapper.expr(mapper, expr)
      | Some(expr) => expr
      },
  };
  mapper.expr(mapper, expr);
};

let strExpr = (structure, exprMapper) => {
  let mapper = {
    ...Ast_mapper.default_mapper,
    expr: (mapper, expr) =>
      switch (exprMapper(mapper, expr)) {
      | None => Ast_mapper.default_mapper.expr(mapper, expr)
      | Some(expr) => expr
      },
  };
  mapper.structure(mapper, structure);
};

let rec collectFnArgs = expr =>
  switch (expr.pexp_desc) {
  | Pexp_fun(label, defaultValue, pattern, body) =>
    let (args, body) = collectFnArgs(body);
    ([(label, defaultValue, pattern), ...args], body);
  | _ => ([], expr)
  };

let rec makeFn = (args, body) =>
  switch (args) {
  | [] => body
  | [(label, defaultValue, pattern), ...rest] =>
    Ast_helper.Exp.fun_(label, defaultValue, pattern, makeFn(rest, body))
  };

let rec mapFn = (mapper, expr) =>
  switch (expr.pexp_desc) {
  | Pexp_fun(label, defaultValue, pattern, body) => {
      ...expr,
      pexp_desc:
        Pexp_fun(
          label,
          switch (defaultValue) {
          | None => None
          | Some(exp) => Some(mapper.Ast_mapper.expr(mapper, exp))
          },
          mapper.pat(mapper, pattern),
          mapFn(mapper, body),
        ),
    }
  | _ => mapper.expr(mapper, expr)
  };

let mapFnExpr = (expr, fnMapper) => {
  expr->mapExpr((mapper, expr) =>
    switch (expr.pexp_desc) {
    | Pexp_fun(_) =>
      let (args, body) = collectFnArgs(expr);
      switch (fnMapper(mapper, args, body)) {
      | Some((args, body)) => Some(makeFn(args, body))
      | None => Some(mapFn(mapper, expr))
      };
    | _ => None
    }
  );
};

let mapConstructor = (expr, ~ident=?, constrMapper) => {
  expr->mapExpr((_mapper, expr) =>
    switch (expr.pexp_desc) {
    | Pexp_construct({txt} as lid, Some({pexp_desc: Pexp_tuple(args)})) =>
      switch (ident) {
      | None => constrMapper(lid, args, expr)
      | Some(ident) when ident == txt => constrMapper(lid, args, expr)
      | _ => None
      }
    | _ => None
    }
  );
};

// type extra = {
//   internalReferences: Hashtbl.t(int, list(Location.t)),
//   externalReferences: Hashtbl.t(string, list((path, tip, Location.t))),
//   mutable locations: list((Location.t, Loc.t)),
//   opens: Hashtbl.t(Location.t, openTracker),
// };

let getExprType = (ctx, expr) => {
  let m = Format.asprintf("%a", Location.print_loc, expr.pexp_loc);

  // ctx.full.extra.locations->Belt.List.forEach(((location, loc)) => {
  //   let t = switch loc {
  //     | Typed(flex, typed) => SharedTypes.Loc.typedToString(typed) ++ " (" ++ flex.toString() ++ ")"
  //     | Constant(_) => "Constant"
  //     | Module(_) => "Module"
  //     | TopLevelModule(string) => "TopLevelModule"
  //     | TypeDefinition(_, _, _) => "TypeDefinition"
  //     | Explanation(_) => "Explanation"
  //     | Open => "Open"
  //     | _ => "Not typed"
  //   };
  //   Format.printf("Type at location: %a, %s@.", Location.print_loc, location, t);
  // });

  let%try_force loc =
    References.locForLocations(~extra=ctx.full.extra, expr.pexp_loc)
    |> RResult.orError(
         "Could not find type for expr at "  ++ m ++ ". Probably the ast & compiled artifacts are out of sync.",
       );
  let env = Query.fileEnv(ctx.full.file);
  let getModule =
    ctx.state->Analyze.State.fileForModule(~package=ctx.package);
  switch (loc) {
  | Typed(typ, _) =>
    SharedTypes.SimpleType.mapSource(
      TypeMap.GetTypeMap.mapSource(~env, ~getModule),
      typ.asSimpleType(),
    )
  | _ => failwith("Location for expression was not Typed. This is a bug.")
  };
};

let getTypeDefinition = (ctx, {TypeMap.DigTypes.declared, env}) => {
  let getModule =
    ctx.state->Analyze.State.fileForModule(~package=ctx.package);
  SharedTypes.SimpleType.declMapSource(
    TypeMap.GetTypeMap.mapSource(~env, ~getModule),
    declared.contents.typ.asSimpleDeclaration(declared.name.txt),
  );
};