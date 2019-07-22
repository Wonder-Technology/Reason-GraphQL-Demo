let createTransportSetParamFunc =
    (ref1, ref2, ref3, param1, param2, param3, _param4) => {
  ref1 := param1;
  ref2 := param2;
  ref3 := param3;

  {"sendMail": (_option, errorFunc) => errorFunc(Js.Null.empty, "")};
};

let createTransportFunc = (_param1, _param2, _param3, _param4) => {
  "sendMail": (_option, errorFunc) => errorFunc(Js.Null.empty, ""),
};

let createTransportSendErrorFunc = (_param1, _param2, _param3, _param4) => {
  "sendMail": (_option, errorFunc) => errorFunc({
      "code":4221,
      "response": "connect email error",
      "responseCode": 123,
      "command": "error connection",
  }, ""),
};