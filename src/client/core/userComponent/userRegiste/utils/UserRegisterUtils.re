open UserRegisterType;

let isUserNameInputValueValid = (send, inputValue) =>
  inputValue === "" ?
    {
      send(
        ChangeUserNameInputState({
          logMsg: {j|用户名不能为空|j},
          isValid: false,
        }),
      );
      false;
    } :
    (
      switch ([%re {|/^[A-Za-z][A-Za-z1-9_-]+$/|}] |> Js.Re.test(inputValue)) {
      | false =>
        send(
          ChangeUserNameInputState({
            logMsg: {j|用户名格式不正确, 请以字母开头|j},
            isValid: false,
          }),
        );
        false;

      | true => true
      }
    );

let isPasswordInputValueValid = (send, inputValue) =>
  inputValue === "" ?
    send(
      ChangePasswordInputState({
        logMsg: {j|密码不能为空|j},
        isValid: false,
      }),
    ) :
    inputValue |> Js.String.length >= 6 ?
      send(
        ChangePasswordInputState({
          logMsg: {j|密码符合要求|j},
          isValid: true,
        }),
      ) :
      send(
        ChangePasswordInputState({
          logMsg: {j|密码过短|j},
          isValid: false,
        }),
      );

let isEmailInputValueValid = (send, inputValue) =>
  inputValue === "" ?
    {
      send(
        ChangeEmailInputState({
          logMsg: {j|此邮箱不能为空|j},
          isValid: false,
        }),
      );
      false;
    } :
    (
      switch (
        [%re
          {|/^([A-Za-z0-9_\-\.\u4e00-\u9fa5])+\@([A-Za-z0-9_\-\.])+\.([A-Za-z]{2,8})$/|}
        ]
        |> Js.Re.test(inputValue)
      ) {
      | false =>
        send(
          ChangeEmailInputState({
            logMsg: {j|邮箱格式不正确|j},
            isValid: false,
          }),
        );
        false;

      | true => true
      }
    );

let _createInputStream = domId =>
  WonderBsMost.Most.fromEvent(
    "input",
    DomHelper.getElementById(domId) |> Obj.magic,
    true,
  );
let getLoginUserQuery = (~userName="", ~email="", ()) => {j|
    {
      loginUser(userName:"$userName", email:"$email"){
        user_name
        password
      }
    }
|j};

let getQueryByType = (type_, inputValue) =>
  switch (type_) {
  | UserName => getLoginUserQuery(~userName=inputValue, ())
  | Email => getLoginUserQuery(~email=inputValue, ())
  };

let checkFetchByUserInputStream =
    (
      send,
      (domId, type_),
      (successAction, failAction),
      isInputValueValidFunc,
    ) =>
  _createInputStream(domId)
  |> WonderBsMost.Most.debounce(1000)
  |> WonderBsMost.Most.tap(e => {
       let inputValue = DomType.convertDomToJsObj(e)##target##defaultValue;

       isInputValueValidFunc(inputValue) ?
         Fetch.fetch("/graphql?query=" ++ getQueryByType(type_, inputValue))
         |> Js.Promise.then_(response =>
              response
              |> Fetch.Response.json
              |> Js.Promise.then_(jsonResult =>
                   JsonType.convertToJsObj(jsonResult)##data##loginUser
                   |> Js.Array.length >= 1 ?
                     send(successAction) |> Js.Promise.resolve :
                     send(failAction) |> Js.Promise.resolve
                 )
            )
         |> ignore :
         ();
     })
  |> WonderBsMost.Most.drain
  |> ignore;

let checkUserInputStream = (domId, handleInputValueValidFunc) =>
  _createInputStream(domId)
  |> WonderBsMost.Most.debounce(1000)
  |> WonderBsMost.Most.tap(e => {
       let inputValue = DomType.convertDomToJsObj(e)##target##defaultValue;

       handleInputValueValidFunc(inputValue);
     })
  |> WonderBsMost.Most.drain
  |> ignore;