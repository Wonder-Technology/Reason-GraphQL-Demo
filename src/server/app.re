open Express;

let app = App.make();

[@bs.module "body-parser"]
external bodyParserJson: unit => Middleware.t = "json";

[@bs.module] external cors: unit => Middleware.t = "cors";

App.use(app, bodyParserJson());
App.use(app, cors());
App.use(
  app,
  Static.make(Node.Process.cwd() ++ "/public", Static.defaultOptions())
  |> Static.asMiddleware,
);
App.use(
  app,
  Static.make("/mnt", Static.defaultOptions()) |> Static.asMiddleware,
);

RegisterIndexRoute.initIndexRoute(app);
RegisterUserRoute.initUserRoute(app);

App.listen(
  app,
  ~port=8888,
  ~onListen=_ => Js.log("this success connect ==> http://localhost:8888"),
  (),
);