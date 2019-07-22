open WonderBsGraphql;

open WonderBsMost;

let getSchema = AppGraphQL.getSchema;

let runGraphql = (source, rootValue) =>
  GraphQL.run(getSchema(), source, ~rootValue, ())
  |> Most.fromPromise;
