open WonderBsGraphql;

open WonderBsJson;

open Express;

open WonderBsMost;

open NodeFetch;

let initUserRoute = app => {
  Express.App.post(app, ~path="/registerUser") @@
  Middleware.from(RegisterUserHandler.handlerLogic);

  Express.App.post(app, ~path="/checkUserLogin") @@
  Middleware.from(CheckUserLoginHandler.handleLogic);
};