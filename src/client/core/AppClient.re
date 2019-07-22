open WonderBsJson;

module RouterConfig = {
  type route =
    | HomePage
    | Home;

  let routeFromUrl = (url: ReasonReact.Router.url) =>
    switch (url.path) {
    | ["homePage"] => HomePage
    | _ => Home
    };

  let routeToUrl = (route: route) =>
    switch (route) {
    | HomePage => "/homePage"
    | Home => "/"
    };
};

module Router = ReRoute.CreateRouter(RouterConfig);

let component = ReasonReact.statelessComponent("AppClient");

let make = _children => {
  ...component,
  render: _self =>
    <Router.Container>
      ...{
           (~currentRoute) =>
             <div className="">
               <Header />
               {
                 switch (currentRoute) {
                 | RouterConfig.HomePage => <UserHomePage />
                 | RouterConfig.Home => <div className=""> <UserList /> </div>
                 }
               }
             </div>
         }
    </Router.Container>,
};