open WonderBsMost;

open JustgageReasonCookie;

open WonderBsJson;

type state = {
  userName: string,
  password: string,
  logMsg: string,
};

type action =
  | ChangeUserName(string)
  | ChangePassword(string)
  | ChangeLogMsg(string);

module Method = {
  let submit = (userName, password, send) =>
    Fetch.fetchWithInit(
      "/checkUserLogin",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=
          Fetch.BodyInit.make(
            Js.Json.stringify(
              Json.Encode.object_([
                ("userName", Json.Encode.string(userName)),
                ("password", Json.Encode.string(password)),
              ]),
            ),
          ),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> Most.fromPromise
    |> Most.flatMap(response =>
         response
         |> Fetch.Response.json
         |> Js.Promise.then_(response => {
              let resultObj = JsonType.convertToJsObj(response);
              Js.log(resultObj);

              resultObj##status === 0 ?
                {
                  let responseData = resultObj##data;

                  Cookie.setJson(
                    "userData",
                    Json.Encode.object_([
                      ("userId", Json.Encode.int(responseData##id)),
                      (
                        "userName",
                        Json.Encode.string(responseData##userName),
                      ),
                    ]),
                  );

                  DomHelper.locationHref("/homePage");
                } :
                send(ChangeLogMsg(resultObj##error));

              Js.Promise.resolve("");
            })
         |> Most.fromPromise
       )
    |> Most.drain
    |> ignore;
};

let component = ReasonReact.reducerComponent("UserLogin");

let reducer = (action, state) =>
  switch (action) {
  | ChangeUserName(value) => ReasonReact.Update({...state, userName: value})
  | ChangePassword(value) => ReasonReact.Update({...state, password: value})
  | ChangeLogMsg(value) => ReasonReact.Update({...state, logMsg: value})
  };

let render = ({state, send}: ReasonReact.self('a, 'b, 'c)) =>
  <div>
    <h1> {"user login" |> DomHelper.textEl} </h1>
    <FormItem
      value={state.userName}
      label={j|用户名|j}
      onChange={value => send(ChangeUserName(value))}
    />
    <FormItem
      value={state.password}
      label={j|密码|j}
      onChange={value => send(ChangePassword(value))}
      inputType="password"
    />
    <button
      disabled={state.userName === "" || state.password === ""}
      onClick={_ => Method.submit(state.userName, state.password, send)}>
      {"login" |> ReasonReact.string}
    </button>
    <div className=""> {DomHelper.textEl(state.logMsg)} </div>
  </div>;

let make = _children => {
  ...component,
  render,
  initialState: () => {userName: "", password: "", logMsg: ""},
  reducer,
};