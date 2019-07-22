open WonderBsJson;

open WonderBsMost;

type state = {
  isShowUserLogin: bool,
  isShowUserRegister: bool,
};

type action =
  | ShowUserLogin
  | ShowUserRegister;

module Method = {};

let component = ReasonReact.reducerComponent("Header");

let reducer = (action, state) =>
  switch (action) {
  | ShowUserLogin =>
    ReasonReact.Update({
      ...state,
      isShowUserLogin: true,
      isShowUserRegister: false,
    })

  | ShowUserRegister =>
    ReasonReact.Update({
      ...state,
      isShowUserLogin: false,
      isShowUserRegister: true,
    })
  };

let render = ({state, send}: ReasonReact.self('a, 'b, 'c)) =>
  <div>
    <h1> {"Header" |> DomHelper.textEl} </h1>
    <div className="">
      <button onClick={_e => send(ShowUserLogin)}>
        {DomHelper.textEl("Login")}
      </button>
      <button onClick={_e => send(ShowUserRegister)}>
        {DomHelper.textEl("Register")}
      </button>
      {state.isShowUserLogin ? <UserLogin /> : ReasonReact.null}
      {state.isShowUserRegister ? <UserRegister /> : ReasonReact.null}
    </div>
  </div>;

let make = _children => {
  ...component,
  initialState: () => {
    isShowUserLogin:
      switch (
        DomHelper.locationSearch(.)##isShowLogin
        |> Js.Undefined.return
        |> Js.Undefined.toOption
      ) {
      | None => false
      | Some(isShowLogin) => isShowLogin
      },
    isShowUserRegister: false,
  },
  reducer,
  render,
};