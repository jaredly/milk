open Migrate_parsetree.Ast_407;

type shortReference = (string, list(string), string);

type reference = {
  uri: string,
  moduleName: string,
  declared: SharedTypes.declared(SharedTypes.Type.t),
  modulePath: list(string),
  name: string,
  env: Query.queryEnv,
};

let toShortReference = ({moduleName, modulePath, name}) => (
  moduleName,
  modulePath,
  name,
);

let showReference = ({moduleName, modulePath, name}) => {
  String.concat(".", [moduleName] @ modulePath @ [name]);
};

let referenceToLident = ({moduleName, modulePath, name}) => {
  switch (Longident.unflatten([moduleName] @ modulePath @ [name])) {
  | None => assert(false)
  | Some(lident) => lident
  };
};

type typeSource('reference) =
  | Builtin(string)
  | Public('reference)
  | NotFound(string);

let toShortSource = source =>
  switch (source) {
  | Builtin(s) => Builtin(s)
  | NotFound(s) => NotFound(s)
  | Public(r) => Public(toShortReference(r))
  };

type typeMap('reference) =
  Hashtbl.t(
    shortReference,
    (
      Parsetree.attributes,
      SharedTypes.SimpleType.declaration(typeSource('reference)),
    ),
  );
