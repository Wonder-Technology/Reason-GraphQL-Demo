'use strict';

var Most = require("most");
var Curry = require("bs-platform/lib/js/curry.js");
var Sinon = require("wonder-bs-sinon/lib/js/src/sinon.js");
var Sinon$1 = require("sinon");
var Moment = require("moment");
var Wonder_jest = require("wonder-bs-jest/lib/js/src/wonder_jest.js");
var Crypto$ReasonGraphqlFullstack = require("../../../../src/external/Crypto.js");
var TestTool$ReasonGraphqlFullstack = require("../../tool/TestTool.js");
var DomHelper$ReasonGraphqlFullstack = require("../../../../src/external/DomHelper.js");
var ArrayUtils$ReasonGraphqlFullstack = require("../../../../src/utils/ArrayUtils.js");
var GraphqlTool$ReasonGraphqlFullstack = require("../../tool/GraphqlTool.js");
var TestInitTool$ReasonGraphqlFullstack = require("../../tool/TestInitTool.js");
var UserLoginValue$ReasonGraphqlFullstack = require("../../../../src/server/database/graphQL/user_login/UserLoginValue.js");
var UserLoginDataTool$ReasonGraphqlFullstack = require("./tool/data/UserLoginDataTool.js");
var UserLoginTableTool$ReasonGraphqlFullstack = require("./tool/UserLoginTableTool.js");
var UserLoginGraphqlTool$ReasonGraphqlFullstack = require("./tool/UserLoginGraphqlTool.js");

Wonder_jest.describe("test table user_login", (function (param) {
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
                      Wonder_jest.describe("test graphql Query", (function (param) {
                              return Wonder_jest.testPromise("test get all login user data", undefined, (function (param) {
                                            var userLoginDataArray = UserLoginDataTool$ReasonGraphqlFullstack.getUserLoginDataArray(date);
                                            var match = TestTool$ReasonGraphqlFullstack.buildTestResultAndErrRef(/* () */0);
                                            var errorRef = match[1];
                                            var resultRef = match[0];
                                            return TestTool$ReasonGraphqlFullstack.setResultOrErrorValue(resultRef, errorRef, TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserLoginGraphqlTool$ReasonGraphqlFullstack.getAllLoginUser(/* () */0), UserLoginValue$ReasonGraphqlFullstack.getUserLoginValue(/* () */0)))).then((function (param) {
                                                          var match = errorRef[0];
                                                          if (match !== undefined) {
                                                            return Promise.resolve(Wonder_jest.fail(match));
                                                          } else {
                                                            return Promise.resolve(Wonder_jest.Expect[/* toEqual */12](UserLoginDataTool$ReasonGraphqlFullstack.buildGraphQLAllData(userLoginDataArray), Wonder_jest.Expect[/* expect */0](resultRef[0].loginUsers)));
                                                          }
                                                        }));
                                          }));
                            }));
                      Wonder_jest.describe("test get login user data", (function (param) {
                              Wonder_jest.testPromise("test get login user by userName", undefined, (function (param) {
                                      var match = TestTool$ReasonGraphqlFullstack.buildTestResultAndErrRef(/* () */0);
                                      var errorRef = match[1];
                                      var resultRef = match[0];
                                      var userLoginDataArray = UserLoginDataTool$ReasonGraphqlFullstack.getUserLoginDataArray(date);
                                      var userLoginFirstItem = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(userLoginDataArray);
                                      var targetUserName = userLoginFirstItem[/* userName */1];
                                      return TestTool$ReasonGraphqlFullstack.setResultOrErrorValue(resultRef, errorRef, TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserLoginGraphqlTool$ReasonGraphqlFullstack.getLoginUserByUserName(targetUserName), UserLoginValue$ReasonGraphqlFullstack.getUserLoginValue(/* () */0)))).then((function (param) {
                                                    var match = errorRef[0];
                                                    if (match !== undefined) {
                                                      return Promise.resolve(Wonder_jest.fail(match));
                                                    } else {
                                                      return Promise.resolve(Wonder_jest.Expect[/* toEqual */12](UserLoginDataTool$ReasonGraphqlFullstack.buildGraphQLDataByUserName(targetUserName, userLoginDataArray), Wonder_jest.Expect[/* expect */0](resultRef[0].loginUser)));
                                                    }
                                                  }));
                                    }));
                              return Wonder_jest.testPromise("test get login user by email", undefined, (function (param) {
                                            var match = TestTool$ReasonGraphqlFullstack.buildTestResultAndErrRef(/* () */0);
                                            var errorRef = match[1];
                                            var resultRef = match[0];
                                            var userLoginDataArray = UserLoginDataTool$ReasonGraphqlFullstack.getUserLoginDataArray(date);
                                            var userLoginFirstItem = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(userLoginDataArray);
                                            var targetEmail = userLoginFirstItem[/* email */3];
                                            return TestTool$ReasonGraphqlFullstack.setResultOrErrorValue(resultRef, errorRef, TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserLoginGraphqlTool$ReasonGraphqlFullstack.getLoginUserByEmail(targetEmail), UserLoginValue$ReasonGraphqlFullstack.getUserLoginValue(/* () */0)))).then((function (param) {
                                                          var match = errorRef[0];
                                                          if (match !== undefined) {
                                                            return Promise.resolve(Wonder_jest.fail(match));
                                                          } else {
                                                            return Promise.resolve(Wonder_jest.Expect[/* toEqual */12](UserLoginDataTool$ReasonGraphqlFullstack.buildGraphQLDataByEmail(targetEmail, userLoginDataArray), Wonder_jest.Expect[/* expect */0](resultRef[0].loginUser)));
                                                          }
                                                        }));
                                          }));
                            }));
                      return Wonder_jest.describe("test graphql Mutation", (function (param) {
                                    Wonder_jest.testPromise("test add login user", undefined, (function (param) {
                                            var match = TestTool$ReasonGraphqlFullstack.buildTestResultAndErrRef(/* () */0);
                                            var errorRef = match[1];
                                            var resultRef = match[0];
                                            var userLoginDataArray = UserLoginDataTool$ReasonGraphqlFullstack.getUserLoginDataArray(date);
                                            var newUserLoginRecord_005 = /* code */Crypto$ReasonGraphqlFullstack.getCryptoValueFromInt(5461);
                                            var newUserLoginRecord = /* record */[
                                              /* id */"5",
                                              /* userName */"amy",
                                              /* password */"asd1313",
                                              /* email */"340606700@qq.com",
                                              /* date */date,
                                              newUserLoginRecord_005,
                                              /* isActive */0
                                            ];
                                            return TestTool$ReasonGraphqlFullstack.setResultOrErrorValue(resultRef, errorRef, Most.flatMap((function (_result) {
                                                                return TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserLoginGraphqlTool$ReasonGraphqlFullstack.getAllLoginUser(/* () */0), UserLoginValue$ReasonGraphqlFullstack.getUserLoginValue(/* () */0)));
                                                              }), TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserLoginGraphqlTool$ReasonGraphqlFullstack.addLoginUser(newUserLoginRecord), UserLoginValue$ReasonGraphqlFullstack.getUserLoginValue(/* () */0))))).then((function (param) {
                                                          var match = errorRef[0];
                                                          if (match !== undefined) {
                                                            return Promise.resolve(Wonder_jest.fail(match));
                                                          } else {
                                                            var newUserLoginData = UserLoginDataTool$ReasonGraphqlFullstack.buildGraphQLResult(newUserLoginRecord);
                                                            return Promise.resolve(Wonder_jest.Expect[/* toEqual */12](ArrayUtils$ReasonGraphqlFullstack.push(newUserLoginData, UserLoginDataTool$ReasonGraphqlFullstack.buildGraphQLAllData(userLoginDataArray)), Wonder_jest.Expect[/* expect */0](resultRef[0].loginUsers)));
                                                          }
                                                        }));
                                          }));
                                    Wonder_jest.testPromise("test update login user's is_active", undefined, (function (param) {
                                            var match = TestTool$ReasonGraphqlFullstack.buildTestResultAndErrRef(/* () */0);
                                            var errorRef = match[1];
                                            var resultRef = match[0];
                                            var userLoginDataArray = UserLoginDataTool$ReasonGraphqlFullstack.getUserLoginDataArray(date);
                                            var userLoginFirstItem = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(userLoginDataArray);
                                            var targetUserName = userLoginFirstItem[/* userName */1];
                                            return TestTool$ReasonGraphqlFullstack.setResultOrErrorValue(resultRef, errorRef, Most.flatMap((function (_result) {
                                                                return TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserLoginGraphqlTool$ReasonGraphqlFullstack.getLoginUserByUserName(targetUserName), UserLoginValue$ReasonGraphqlFullstack.getUserLoginValue(/* () */0)));
                                                              }), TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserLoginGraphqlTool$ReasonGraphqlFullstack.updateLoginUserIsActive(targetUserName, 1), UserLoginValue$ReasonGraphqlFullstack.getUserLoginValue(/* () */0))))).then((function (param) {
                                                          var match = errorRef[0];
                                                          if (match !== undefined) {
                                                            return Promise.resolve(Wonder_jest.fail(match));
                                                          } else {
                                                            var loginUserObj = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(resultRef[0].loginUser);
                                                            return Promise.resolve(Curry._2(Wonder_jest.Expect[/* Operators */25][/* = */5], Wonder_jest.Expect[/* expect */0](loginUserObj.is_active), 1));
                                                          }
                                                        }));
                                          }));
                                    Wonder_jest.testPromise("test update login user's code", undefined, (function (param) {
                                            var match = TestTool$ReasonGraphqlFullstack.buildTestResultAndErrRef(/* () */0);
                                            var errorRef = match[1];
                                            var resultRef = match[0];
                                            var userLoginDataArray = UserLoginDataTool$ReasonGraphqlFullstack.getUserLoginDataArray(date);
                                            var userLoginFirstItem = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(userLoginDataArray);
                                            var targetUserName = userLoginFirstItem[/* userName */1];
                                            var targetCode = Crypto$ReasonGraphqlFullstack.getCryptoValueFromInt(DomHelper$ReasonGraphqlFullstack.getRandomNumber(/* () */0));
                                            return TestTool$ReasonGraphqlFullstack.setResultOrErrorValue(resultRef, errorRef, Most.flatMap((function (_result) {
                                                                return TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserLoginGraphqlTool$ReasonGraphqlFullstack.getLoginUserByUserName(targetUserName), UserLoginValue$ReasonGraphqlFullstack.getUserLoginValue(/* () */0)));
                                                              }), TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserLoginGraphqlTool$ReasonGraphqlFullstack.updateLoginUserCode(targetUserName, targetCode), UserLoginValue$ReasonGraphqlFullstack.getUserLoginValue(/* () */0))))).then((function (param) {
                                                          var match = errorRef[0];
                                                          if (match !== undefined) {
                                                            return Promise.resolve(Wonder_jest.fail(match));
                                                          } else {
                                                            var loginUserObj = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(resultRef[0].loginUser);
                                                            return Promise.resolve(Curry._2(Wonder_jest.Expect[/* Operators */25][/* = */5], Wonder_jest.Expect[/* expect */0](loginUserObj.code), targetCode));
                                                          }
                                                        }));
                                          }));
                                    return Wonder_jest.testPromise("test update login user's password ", undefined, (function (param) {
                                                  var match = TestTool$ReasonGraphqlFullstack.buildTestResultAndErrRef(/* () */0);
                                                  var errorRef = match[1];
                                                  var resultRef = match[0];
                                                  var userLoginDataArray = UserLoginDataTool$ReasonGraphqlFullstack.getUserLoginDataArray(date);
                                                  var userLoginFirstItem = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(userLoginDataArray);
                                                  var targetUserName = userLoginFirstItem[/* userName */1];
                                                  var targetPassword = "xiaohao111";
                                                  return TestTool$ReasonGraphqlFullstack.setResultOrErrorValue(resultRef, errorRef, Most.flatMap((function (_result) {
                                                                      return TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserLoginGraphqlTool$ReasonGraphqlFullstack.getLoginUserByUserName(targetUserName), UserLoginValue$ReasonGraphqlFullstack.getUserLoginValue(/* () */0)));
                                                                    }), TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserLoginGraphqlTool$ReasonGraphqlFullstack.updateLoginUserPassword(targetUserName, targetPassword), UserLoginValue$ReasonGraphqlFullstack.getUserLoginValue(/* () */0))))).then((function (param) {
                                                                var match = errorRef[0];
                                                                if (match !== undefined) {
                                                                  return Promise.resolve(Wonder_jest.fail(match));
                                                                } else {
                                                                  var loginUserObj = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(resultRef[0].loginUser);
                                                                  return Promise.resolve(Curry._2(Wonder_jest.Expect[/* Operators */25][/* = */5], Wonder_jest.Expect[/* expect */0](loginUserObj.password), targetPassword));
                                                                }
                                                              }));
                                                }));
                                  }));
                    }));
      }));

/*  Not a pure module */
