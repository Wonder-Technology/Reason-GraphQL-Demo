open WonderBsMost;

open JustgageReasonCookie;

open WonderBsJson;

type state = {
  userName: string,
  password: string,
  logMsg: string,
  isShowRetrievePassword: bool,
  retrieveUserName: string,
};

type action =
  | ChangeUserName(string)
  | ChangePassword(string)
  | ChangeLogMsg(string)
  | ChangeRetrieveUserName(string)
  | ShowRetrievePassword
  | HideRetrievePassword;

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

  let retrievePassword = (userName, send) =>
    Fetch.fetch({j|/sendEmailToRetrievePassword?userName=$userName|j})
    |> WonderBsMost.Most.fromPromise
    |> WonderBsMost.Most.flatMap(response =>
         response
         |> Fetch.Response.json
         |> WonderBsMost.Most.fromPromise
         |> WonderBsMost.Most.map(response => {
              let resultObj = JsonType.convertToJsObj(response);

              resultObj##status === 1 ?
                {
                  let email = resultObj##email;

                  send(
                    ChangeLogMsg(
                      {j|我们已经发送邮件到$email， 请到邮箱进行验证.|j},
                    ),
                  );
                } :
                send(ChangeLogMsg(resultObj##error));
            })
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
  | ChangeRetrieveUserName(value) =>
    ReasonReact.Update({...state, retrieveUserName: value})
  | ShowRetrievePassword =>
    ReasonReact.Update({...state, isShowRetrievePassword: true})
  | HideRetrievePassword =>
    ReasonReact.Update({...state, isShowRetrievePassword: false})
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
    <button onClick={_e => send(ShowRetrievePassword)}>
      {DomHelper.textEl({j|找回密码|j})}
    </button>
    {
      state.isShowRetrievePassword ?
        <div className="">
          <FormItem
            value={state.retrieveUserName}
            label={j|需要找回的用户名|j}
            onChange={value => send(ChangeRetrieveUserName(value))}
          />
          <button
            onClick={
              _e => Method.retrievePassword(state.retrieveUserName, send)
            }>
            {DomHelper.textEl({j|确定|j})}
          </button>
        </div> :
        ReasonReact.null
    }
  </div>;

let make = _children => {
  ...component,
  render,
  initialState: () => {
    userName: "",
    password: "",
    logMsg: "",
    retrieveUserName: "",
    isShowRetrievePassword: false,
  },
  reducer,
};