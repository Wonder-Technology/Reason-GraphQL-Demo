open UserRegisterType;

open WonderBsMost;

open WonderBsJson;

module Method = {
  let isValueHasInValid = state =>
    [|state.userName, state.password, state.email|]
    |> Js.Array.filter(item => item === "")
    |> Js.Array.length >= 1
    || !state.userNameInputState.isValid
    || !state.passwordInputState.isValid
    || !state.emailInputState.isValid;

  let handleAddUser = (state, send) =>
    Fetch.fetchWithInit(
      "/registerUser",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=
          Fetch.BodyInit.make(
            Js.Json.stringify(
              Json.Encode.object_([
                ("userName", Json.Encode.string(state.userName)),
                ("nickName", Json.Encode.string(state.nickName)),
                ("password", Json.Encode.string(state.password)),
                ("email", Json.Encode.string(state.email)),
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
         |> Most.fromPromise
         |> Most.flatMap(result => {
              let resultObj = JsonType.convertToJsObj(result);

              resultObj##status === 0 ?
                send(
                  ChangeRegisterState({
                    logMsg: {j|注册成功|j},
                    isSubmit: true,
                  }),
                )
                |> Most.just :
                send(
                  ChangeRegisterState({
                    logMsg: {j|注册会员失败|j},
                    isSubmit: true,
                  }),
                )
                |> Most.just;
            })
       )
    |> Most.drain
    |> ignore;
};

let component = ReasonReact.reducerComponent("AddLoginUser");

let reducer = (action, state) =>
  switch (action) {
  | ChangeUserName(value) => ReasonReact.Update({...state, userName: value})
  | ChangeNickName(value) => ReasonReact.Update({...state, nickName: value})
  | ChangePassword(value) => ReasonReact.Update({...state, password: value})
  | ChangeEmail(value) => ReasonReact.Update({...state, email: value})
  | ChangeUserNameInputState(value) =>
    ReasonReact.Update({...state, userNameInputState: value})
  | ChangeEmailInputState(value) =>
    ReasonReact.Update({...state, emailInputState: value})
  | ChangePasswordInputState(value) =>
    ReasonReact.Update({...state, passwordInputState: value})
  | ChangeRegisterState(value) =>
    ReasonReact.Update({...state, registerState: value})
  };

let render = ({state, send}: ReasonReact.self('a, 'b, 'c)) =>
  <div>
    <h1> {DomHelper.textEl("Add Person")} </h1>
    <FormItem
      value={state.userName}
      logMsg={state.userNameInputState.logMsg}
      label={j|用户名|j}
      onChange={value => send(ChangeUserName(value))}
      inputId="userNameInput"
    />
    <FormItem
      value={state.nickName}
      logMsg={j||j}
      label={j|昵称|j}
      onChange={value => send(ChangeNickName(value))}
    />
    <FormItem
      value={state.email}
      logMsg={state.emailInputState.logMsg}
      label={j|邮箱|j}
      onChange={value => send(ChangeEmail(value))}
      inputId="emailInput"
    />
    <FormItem
      value={state.password}
      logMsg={state.passwordInputState.logMsg}
      label={j|密码|j}
      onChange={value => send(ChangePassword(value))}
      inputId="passwordInput"
      inputType="password"
    />
    <button
      disabled={
        state.registerState.isSubmit ? true : Method.isValueHasInValid(state)
      }
      onClick={_ => Method.handleAddUser(state, send)}>
      {{j|创建新账号|j} |> DomHelper.textEl}
    </button>
    <div className=""> {DomHelper.textEl(state.registerState.logMsg)} </div>
  </div>;

let make = _children => {
  ...component,
  initialState: () => {
    userName: "",
    nickName: "",
    password: "",
    email: "",
    userNameInputState: {
      logMsg: {j|必填，字母开头，没有空格|j},
      isValid: false,
    },
    emailInputState: {
      logMsg: {j|必填|j},
      isValid: false,
    },
    passwordInputState: {
      logMsg: {j|必填, 密码不能少于6位|j},
      isValid: false,
    },
    registerState: {
      logMsg: "",
      isSubmit: false,
    },
  },
  reducer,
  didMount: ({send}: ReasonReact.self('a, 'b, 'c)) => {
    UserRegisterUtils.checkFetchByUserInputStream(
      send,
      ("userNameInput", UserName),
      (
        ChangeUserNameInputState({
          logMsg: {j|用户名已经被注册|j},
          isValid: false,
        }),
        ChangeUserNameInputState({logMsg: {j|可以使用|j}, isValid: true}),
      ),
      UserRegisterUtils.isUserNameInputValueValid(send),
    );

    UserRegisterUtils.checkFetchByUserInputStream(
      send,
      ("emailInput", Email),
      (
        ChangeEmailInputState({
          logMsg: {j|此邮箱已经被注册|j},
          isValid: false,
        }),
        ChangeEmailInputState({logMsg: {j|可以使用|j}, isValid: true}),
      ),
      UserRegisterUtils.isEmailInputValueValid(send),
    );

    UserRegisterUtils.checkUserInputStream(
      "passwordInput",
      UserRegisterUtils.isPasswordInputValueValid(send),
    );
  },
  render,
};