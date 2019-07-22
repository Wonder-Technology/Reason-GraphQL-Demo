open Express;

let initIndexRoute = app => {
  let _graphqlMiddleware =
    WonderBsApolloServerExpress.ApolloServerExpress.createGraphQLExpressMiddleware(
      ~rootValue=AppGraphQL.getRootValue(),
      AppGraphQL.getSchema(),
      (),
    );
  let _graphiqlMiddleware =
    WonderBsApolloServerExpress.ApolloServerExpress.createGraphiQLExpressMiddleware(
      "/graphql",
      (),
    );

  Express.App.useOnPath(app, _graphqlMiddleware, ~path="/graphql");
  Express.App.useOnPath(app, _graphiqlMiddleware, ~path="/graphiql");

  Express.App.get(app, ~path="/") @@
  Middleware.from((_, _, response) =>
    response |> Response.sendFile(Node.Process.cwd() ++ "/index.html", ())
  );

  Express.App.get(app, ~path="/homePage") @@
  Middleware.from((_next, _request, response) =>
    response |> Response.sendFile(Node.Process.cwd() ++ "/index.html", ())
  );

  Express.App.get(app, ~path="/retrievePassword") @@
  Middleware.from((_next, _request, response) =>
    response |> Response.sendFile(Node.Process.cwd() ++ "/index.html", ())
  );

  Express.App.get(app, ~path="/userActive") @@
  Middleware.from((_next, _request, response) =>
    response |> Response.sendFile(Node.Process.cwd() ++ "/index.html", ())
  );
};