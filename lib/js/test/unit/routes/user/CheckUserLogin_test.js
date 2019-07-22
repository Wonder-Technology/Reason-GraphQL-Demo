'use strict';

var Most = require("most");
var Curry = require("bs-platform/lib/js/curry.js");
var Sinon = require("wonder-bs-sinon/lib/js/src/sinon.js");
var Sinon$1 = require("sinon");
var Moment = require("moment");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Wonder_jest = require("wonder-bs-jest/lib/js/src/wonder_jest.js");
var Json_encode$WonderBsJson = require("wonder-bs-json/lib/js/src/Json_encode.js");
var ArrayUtils$ReasonGraphqlFullstack = require("../../../../src/utils/ArrayUtils.js");
var RequestTool$ReasonGraphqlFullstack = require("../../tool/RequestTool.js");
var ResponseTool$ReasonGraphqlFullstack = require("../../tool/ResponseTool.js");
var TestInitTool$ReasonGraphqlFullstack = require("../../tool/TestInitTool.js");
var ResponseUtils$ReasonGraphqlFullstack = require("../../../../src/server/routes/utils/ResponseUtils.js");
var UserLoginDataTool$ReasonGraphqlFullstack = require("../../model/userLogin/tool/data/UserLoginDataTool.js");
var UserLoginTableTool$ReasonGraphqlFullstack = require("../../model/userLogin/tool/UserLoginTableTool.js");
var CheckUserLoginHandler$ReasonGraphqlFullstack = require("../../../../src/server/routes/user/handler/CheckUserLoginHandler.js");

Wonder_jest.describe("test route: checkUserLogin", (function (param) {
        var sandbox = Sinon.getSandboxDefaultVal(/* () */0);
        Wonder_jest.beforeEachPromise(undefined, (function (param) {
                sandbox[0] = Sinon$1.sandbox.create();
                return Most.drain(TestInitTool$ReasonGraphqlFullstack.initTest(/* () */0));
              }));
        Wonder_jest.afterEachPromise(undefined, (function (param) {
                Curry._1(Sinon.restoreSandbox, sandbox[0]);
                return Most.drain(TestInitTool$ReasonGraphqlFullstack.restoreMysql(/* () */0));
              }));
        return Wonder_jest.describe("init fake database and table", (function (param) {
                      var date = Moment().format("YYYY-MM-DD HH:mm:ss");
                      Wonder_jest.beforeEachPromise(undefined, (function (param) {
                              return Most.drain(Most.recoverWith((function (_error) {
                                                return Most.just("init userLogin table error");
                                              }), UserLoginTableTool$ReasonGraphqlFullstack.initUserLoginTable(UserLoginDataTool$ReasonGraphqlFullstack.getUserLoginDataArray(date))));
                            }));
                      Wonder_jest.describe("if param is undefined or null", (function (param) {
                              return Wonder_jest.testPromise("should response status and error msg", undefined, (function (param) {
                                            var request = RequestTool$ReasonGraphqlFullstack.buildFakePostRequest(null);
                                            var responseObj = ResponseTool$ReasonGraphqlFullstack.buildFakeResponse(sandbox);
                                            return Most.drain(CheckUserLoginHandler$ReasonGraphqlFullstack.logicContent(request, responseObj)).then((function (param) {
                                                          return Promise.resolve(Sinon.toCalledWith(/* array */[ResponseUtils$ReasonGraphqlFullstack.buildResponseDataJson(/* InValidParam */2, undefined, "param is invalid", /* () */0)], Wonder_jest.Expect[/* expect */0](responseObj.json)));
                                                        }));
                                          }));
                            }));
                      Wonder_jest.describe("if param has no userName or password", (function (param) {
                              return Wonder_jest.testPromise("should response status and error msg", undefined, (function (param) {
                                            var request = RequestTool$ReasonGraphqlFullstack.buildFakePostRequest({
                                                  userName: "mickey"
                                                });
                                            var responseObj = ResponseTool$ReasonGraphqlFullstack.buildFakeResponse(sandbox);
                                            return Most.drain(CheckUserLoginHandler$ReasonGraphqlFullstack.logicContent(request, responseObj)).then((function (param) {
                                                          return Promise.resolve(Sinon.toCalledWith(/* array */[ResponseUtils$ReasonGraphqlFullstack.buildResponseDataJson(/* ParamError */1, undefined, "the param is error", /* () */0)], Wonder_jest.Expect[/* expect */0](responseObj.json)));
                                                        }));
                                          }));
                            }));
                      Wonder_jest.describe("if param userName not exist in table", (function (param) {
                              return Wonder_jest.testPromise("should response status and error msg", undefined, (function (param) {
                                            var request = RequestTool$ReasonGraphqlFullstack.buildFakePostRequest({
                                                  userName: "mickey",
                                                  password: "asd1313"
                                                });
                                            var responseObj = ResponseTool$ReasonGraphqlFullstack.buildFakeResponse(sandbox);
                                            return Most.drain(CheckUserLoginHandler$ReasonGraphqlFullstack.logicContent(request, responseObj)).then((function (param) {
                                                          return Promise.resolve(Sinon.toCalledWith(/* array */[ResponseUtils$ReasonGraphqlFullstack.buildResponseDataJson(/* UserNameNotExist */6, undefined, "userName is not exist", /* () */0)], Wonder_jest.Expect[/* expect */0](responseObj.json)));
                                                        }));
                                          }));
                            }));
                      Wonder_jest.describe("if param password not matching in table", (function (param) {
                              return Wonder_jest.testPromise("should response status and error msg", undefined, (function (param) {
                                            var userLoginDataArray = UserLoginDataTool$ReasonGraphqlFullstack.getUserLoginDataArray(date);
                                            var userLoginFirstItem = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(userLoginDataArray);
                                            var request = RequestTool$ReasonGraphqlFullstack.buildFakePostRequest({
                                                  userName: userLoginFirstItem[/* userName */1],
                                                  password: "asd1111"
                                                });
                                            var responseObj = ResponseTool$ReasonGraphqlFullstack.buildFakeResponse(sandbox);
                                            return Most.drain(CheckUserLoginHandler$ReasonGraphqlFullstack.logicContent(request, responseObj)).then((function (param) {
                                                          return Promise.resolve(Sinon.toCalledWith(/* array */[ResponseUtils$ReasonGraphqlFullstack.buildResponseDataJson(/* PasswordError */5, undefined, "the password error", /* () */0)], Wonder_jest.Expect[/* expect */0](responseObj.json)));
                                                        }));
                                          }));
                            }));
                      Wonder_jest.describe("if target user is not active", (function (param) {
                              return Wonder_jest.testPromise("should response status and error msg", undefined, (function (param) {
                                            var userLoginDataArray = UserLoginDataTool$ReasonGraphqlFullstack.getUserLoginDataArray(date);
                                            var userLoginFirstItem = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(userLoginDataArray);
                                            var request = RequestTool$ReasonGraphqlFullstack.buildFakePostRequest({
                                                  userName: userLoginFirstItem[/* userName */1],
                                                  password: userLoginFirstItem[/* password */2]
                                                });
                                            var responseObj = ResponseTool$ReasonGraphqlFullstack.buildFakeResponse(sandbox);
                                            return Most.drain(CheckUserLoginHandler$ReasonGraphqlFullstack.logicContent(request, responseObj)).then((function (param) {
                                                          return Promise.resolve(Sinon.toCalledWith(/* array */[ResponseUtils$ReasonGraphqlFullstack.buildResponseDataJson(/* UserNotActive */4, undefined, "the user not active", /* () */0)], Wonder_jest.Expect[/* expect */0](responseObj.json)));
                                                        }));
                                          }));
                            }));
                      return Wonder_jest.describe("else, check user login success", (function (param) {
                                    return Wonder_jest.testPromise("should response status and success msg", undefined, (function (param) {
                                                  var userLoginDataArray = UserLoginDataTool$ReasonGraphqlFullstack.getUserLoginDataArray(date);
                                                  var userLoginLastItem = ArrayUtils$ReasonGraphqlFullstack.unsafeGetLast(userLoginDataArray);
                                                  var request = RequestTool$ReasonGraphqlFullstack.buildFakePostRequest({
                                                        userName: userLoginLastItem[/* userName */1],
                                                        password: userLoginLastItem[/* password */2]
                                                      });
                                                  var responseObj = ResponseTool$ReasonGraphqlFullstack.buildFakeResponse(sandbox);
                                                  return Most.drain(CheckUserLoginHandler$ReasonGraphqlFullstack.logicContent(request, responseObj)).then((function (param) {
                                                                return Promise.resolve(Sinon.toCalledWith(/* array */[ResponseUtils$ReasonGraphqlFullstack.buildResponseDataJson(/* Success */0, Caml_option.some(Json_encode$WonderBsJson.object_(/* :: */[
                                                                                              /* tuple */[
                                                                                                "userName",
                                                                                                userLoginLastItem[/* userName */1]
                                                                                              ],
                                                                                              /* :: */[
                                                                                                /* tuple */[
                                                                                                  "id",
                                                                                                  userLoginLastItem[/* id */0]
                                                                                                ],
                                                                                                /* [] */0
                                                                                              ]
                                                                                            ])), undefined, /* () */0)], Wonder_jest.Expect[/* expect */0](responseObj.json)));
                                                              }));
                                                }));
                                  }));
                    }));
      }));

/*  Not a pure module */
