'use strict';

var Curry = require("bs-platform/lib/js/curry.js");

function createTransportSetParamFunc(ref1, ref2, ref3, param1, param2, param3, _param4) {
  ref1[0] = param1;
  ref2[0] = param2;
  ref3[0] = param3;
  return {
          sendMail: (function (_option, errorFunc) {
              return Curry._2(errorFunc, null, "");
            })
        };
}

function createTransportFunc(_param1, _param2, _param3, _param4) {
  return {
          sendMail: (function (_option, errorFunc) {
              return Curry._2(errorFunc, null, "");
            })
        };
}

function createTransportSendErrorFunc(_param1, _param2, _param3, _param4) {
  return {
          sendMail: (function (_option, errorFunc) {
              return Curry._2(errorFunc, {
                          code: 4221,
                          response: "connect email error",
                          responseCode: 123,
                          command: "error connection"
                        }, "");
            })
        };
}

exports.createTransportSetParamFunc = createTransportSetParamFunc;
exports.createTransportFunc = createTransportFunc;
exports.createTransportSendErrorFunc = createTransportSendErrorFunc;
/* No side effect */
