'use strict';

var Most = require("most");
var Curry = require("bs-platform/lib/js/curry.js");
var Sinon = require("wonder-bs-sinon/lib/js/src/sinon.js");
var Sinon$1 = require("sinon");
var Moment = require("moment");
var Wonder_jest = require("wonder-bs-jest/lib/js/src/wonder_jest.js");
var Crypto$ReasonGraphqlFullstack = require("../../../../src/external/Crypto.js");
var DomHelper$ReasonGraphqlFullstack = require("../../../../src/external/DomHelper.js");
var RequestTool$ReasonGraphqlFullstack = require("../../tool/RequestTool.js");
var ResponseTool$ReasonGraphqlFullstack = require("../../tool/ResponseTool.js");
var TestInitTool$ReasonGraphqlFullstack = require("../../tool/TestInitTool.js");
var ResponseUtils$ReasonGraphqlFullstack = require("../../../../src/server/routes/utils/ResponseUtils.js");
var UserInfoDataTool$ReasonGraphqlFullstack = require("../../model/userInfo/tool/data/UserInfoDataTool.js");
var UserInfoTableTool$ReasonGraphqlFullstack = require("../../model/userInfo/tool/UserInfoTableTool.js");
var UserLoginDataTool$ReasonGraphqlFullstack = require("../../model/userLogin/tool/data/UserLoginDataTool.js");
var UserLoginTableTool$ReasonGraphqlFullstack = require("../../model/userLogin/tool/UserLoginTableTool.js");
var RegisterUserHandler$ReasonGraphqlFullstack = require("../../../../src/server/routes/user/handler/RegisterUserHandler.js");

Wonder_jest.describe("test route: registerUser", (function (param) {
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
                      var code = Crypto$ReasonGraphqlFullstack.getCryptoValueFromInt(DomHelper$ReasonGraphqlFullstack.getRandomNumber(/* () */0));
                      Wonder_jest.beforeEachPromise(undefined, (function (param) {
                              return Most.drain(Most.recoverWith((function (_error) {
                                                return Most.just("init userLogin and userInfo table error");
                                              }), Most.flatMap((function (_res) {
                                                    return UserInfoTableTool$ReasonGraphqlFullstack.initUserInfoTable(UserInfoDataTool$ReasonGraphqlFullstack.getUserInfoData(/* () */0));
                                                  }), UserLoginTableTool$ReasonGraphqlFullstack.initUserLoginTable(UserLoginDataTool$ReasonGraphqlFullstack.getUserLoginDataArray(date)))));
                            }));
                      Wonder_jest.describe("if param is undefined or null", (function (param) {
                              return Wonder_jest.testPromise("should response status and error msg", undefined, (function (param) {
                                            var request = RequestTool$ReasonGraphqlFullstack.buildFakePostRequest(undefined);
                                            var responseObj = ResponseTool$ReasonGraphqlFullstack.buildFakeResponse(sandbox);
                                            return Most.drain(RegisterUserHandler$ReasonGraphqlFullstack.logicContent(request, responseObj, code)).then((function (param) {
                                                          return Promise.resolve(Sinon.toCalledWith(/* array */[ResponseUtils$ReasonGraphqlFullstack.buildResponseDataJson(/* InValidParam */3, undefined, "param is invalid", /* () */0)], Wonder_jest.Expect[/* expect */0](responseObj.json)));
                                                        }));
                                          }));
                            }));
                      Wonder_jest.describe("if param has no userName or password or email or nickName", (function (param) {
                              return Wonder_jest.testPromise("should response status and error msg", undefined, (function (param) {
                                            var request = RequestTool$ReasonGraphqlFullstack.buildFakePostRequest({
                                                  userName: "mickey",
                                                  password: "asd123123"
                                                });
                                            var responseObj = ResponseTool$ReasonGraphqlFullstack.buildFakeResponse(sandbox);
                                            return Most.drain(RegisterUserHandler$ReasonGraphqlFullstack.logicContent(request, responseObj, code)).then((function (param) {
                                                          return Promise.resolve(Sinon.toCalledWith(/* array */[ResponseUtils$ReasonGraphqlFullstack.buildResponseDataJson(/* ParamError */1, undefined, "the param is error", /* () */0)], Wonder_jest.Expect[/* expect */0](responseObj.json)));
                                                        }));
                                          }));
                            }));
                      return Wonder_jest.describe("else, check user login success", (function (param) {
                                    return Wonder_jest.testPromise("should response status and success msg", undefined, (function (param) {
                                                  var request = RequestTool$ReasonGraphqlFullstack.buildFakePostRequest({
                                                        userName: "mickey",
                                                        password: "asd123000",
                                                        email: "340606700@qq.com",
                                                        nickName: "yangHao"
                                                      });
                                                  var responseObj = ResponseTool$ReasonGraphqlFullstack.buildFakeResponse(sandbox);
                                                  return Most.drain(RegisterUserHandler$ReasonGraphqlFullstack.logicContent(request, responseObj, code)).then((function (param) {
                                                                return Promise.resolve(Sinon.toCalledWith(/* array */[ResponseUtils$ReasonGraphqlFullstack.buildResponseDataJson(/* Success */0, undefined, undefined, /* () */0)], Wonder_jest.Expect[/* expect */0](responseObj.json)));
                                                              }));
                                                }));
                                  }));
                    }));
      }));

/*  Not a pure module */
