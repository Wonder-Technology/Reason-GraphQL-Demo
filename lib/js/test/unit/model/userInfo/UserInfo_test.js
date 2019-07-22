'use strict';

var Most = require("most");
var Curry = require("bs-platform/lib/js/curry.js");
var Sinon = require("wonder-bs-sinon/lib/js/src/sinon.js");
var Sinon$1 = require("sinon");
var Moment = require("moment");
var Wonder_jest = require("wonder-bs-jest/lib/js/src/wonder_jest.js");
var Crypto$ReasonGraphqlFullstack = require("../../../../src/external/Crypto.js");
var TestTool$ReasonGraphqlFullstack = require("../../tool/TestTool.js");
var ArrayUtils$ReasonGraphqlFullstack = require("../../../../src/utils/ArrayUtils.js");
var GraphqlTool$ReasonGraphqlFullstack = require("../../tool/GraphqlTool.js");
var TestInitTool$ReasonGraphqlFullstack = require("../../tool/TestInitTool.js");
var UserInfoValue$ReasonGraphqlFullstack = require("../../../../src/server/database/graphQL/user_info/UserInfoValue.js");
var UserLoginValue$ReasonGraphqlFullstack = require("../../../../src/server/database/graphQL/user_login/UserLoginValue.js");
var UserInfoDataTool$ReasonGraphqlFullstack = require("./tool/data/UserInfoDataTool.js");
var UserInfoTableTool$ReasonGraphqlFullstack = require("./tool/UserInfoTableTool.js");
var UserLoginDataTool$ReasonGraphqlFullstack = require("../userLogin/tool/data/UserLoginDataTool.js");
var UserLoginTableTool$ReasonGraphqlFullstack = require("../userLogin/tool/UserLoginTableTool.js");
var UserInfoGraphqlTool$ReasonGraphqlFullstack = require("./tool/UserInfoGraphqlTool.js");
var UserLoginGraphqlTool$ReasonGraphqlFullstack = require("../userLogin/tool/UserLoginGraphqlTool.js");

Wonder_jest.describe("test table user_info", (function (param) {
        var sandbox = Sinon.getSandboxDefaultVal(/* () */0);
        Wonder_jest.beforeEachPromise(undefined, (function (param) {
                sandbox[0] = Sinon$1.sandbox.create();
                return Most.drain(TestInitTool$ReasonGraphqlFullstack.initTest(/* () */0));
              }));
        Wonder_jest.afterEachPromise(undefined, (function (param) {
                Curry._1(Sinon.restoreSandbox, sandbox[0]);
                return Most.drain(TestInitTool$ReasonGraphqlFullstack.restoreMysql(/* () */0));
              }));
        return Wonder_jest.describe("test init fake database", (function (param) {
                      var date = Moment().format("YYYY-MM-DD HH:mm:ss");
                      Wonder_jest.beforeEachPromise(undefined, (function (param) {
                              return Most.drain(Most.recoverWith((function (_error) {
                                                return Most.just("init userLogin and userInfo table error");
                                              }), Most.flatMap((function (_res) {
                                                    return UserInfoTableTool$ReasonGraphqlFullstack.initUserInfoTable(UserInfoDataTool$ReasonGraphqlFullstack.getUserInfoData(/* () */0));
                                                  }), UserLoginTableTool$ReasonGraphqlFullstack.initUserLoginTable(UserLoginDataTool$ReasonGraphqlFullstack.getUserLoginDataArray(date)))));
                            }));
                      Wonder_jest.describe("test graphql Query", (function (param) {
                              return Wonder_jest.describe("test get user info data", (function (param) {
                                            return Wonder_jest.testPromise("test get info user by userId", undefined, (function (param) {
                                                          var match = TestTool$ReasonGraphqlFullstack.buildTestResultAndErrRef(/* () */0);
                                                          var errorRef = match[1];
                                                          var resultRef = match[0];
                                                          var userInfoDataArray = UserInfoDataTool$ReasonGraphqlFullstack.getUserInfoData(/* () */0);
                                                          var userInfoFirstItem = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(userInfoDataArray);
                                                          var targetUserId = userInfoFirstItem[/* userId */1];
                                                          return TestTool$ReasonGraphqlFullstack.setResultOrErrorValue(resultRef, errorRef, TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserInfoGraphqlTool$ReasonGraphqlFullstack.getUserInfoByUserId(targetUserId), UserInfoValue$ReasonGraphqlFullstack.getUserInfoValue(/* () */0)))).then((function (param) {
                                                                        var match = errorRef[0];
                                                                        if (match !== undefined) {
                                                                          return Promise.resolve(Wonder_jest.fail(match));
                                                                        } else {
                                                                          return Promise.resolve(Wonder_jest.Expect[/* toEqual */12](UserInfoDataTool$ReasonGraphqlFullstack.buildGraphQLDataByUserId(targetUserId, userInfoDataArray), Wonder_jest.Expect[/* expect */0](resultRef[0].userInfo)));
                                                                        }
                                                                      }));
                                                        }));
                                          }));
                            }));
                      return Wonder_jest.describe("test graphql Mutation", (function (param) {
                                    Wonder_jest.testPromise("test should add user_login, then get the userId to add user info", undefined, (function (param) {
                                            var match = TestTool$ReasonGraphqlFullstack.buildTestResultAndErrRef(/* () */0);
                                            var errorRef = match[1];
                                            var resultRef = match[0];
                                            var userInfoDataArray = UserInfoDataTool$ReasonGraphqlFullstack.getUserInfoData(/* () */0);
                                            var newUserInfoRecordRef = /* record */[/* contents */ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(userInfoDataArray)];
                                            var newUserLoginRecord_005 = /* code */Crypto$ReasonGraphqlFullstack.getCryptoValueFromInt(1235);
                                            var newUserLoginRecord = /* record */[
                                              /* id */"5",
                                              /* userName */"amy",
                                              /* password */"asd1313",
                                              /* email */"340606700@qq.com",
                                              /* date */date,
                                              newUserLoginRecord_005,
                                              /* isActive */0
                                            ];
                                            return TestTool$ReasonGraphqlFullstack.setResultOrErrorValue(resultRef, errorRef, Most.flatMap((function (param) {
                                                                return TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserInfoGraphqlTool$ReasonGraphqlFullstack.getUserInfoByUserId(newUserInfoRecordRef[0][/* userId */1]), UserInfoValue$ReasonGraphqlFullstack.getUserInfoValue(/* () */0)));
                                                              }), Most.flatMap((function (loginUserData) {
                                                                    var newUserInfoRecord_001 = /* userId */ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(loginUserData.loginUser).id;
                                                                    var newUserInfoRecord = /* record */[
                                                                      /* id */"5",
                                                                      newUserInfoRecord_001,
                                                                      /* nickName */"mickey",
                                                                      /* profilePicture */"/image/mickey.png"
                                                                    ];
                                                                    newUserInfoRecordRef[0] = newUserInfoRecord;
                                                                    return TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserInfoGraphqlTool$ReasonGraphqlFullstack.addUserInfo(newUserInfoRecord), UserInfoValue$ReasonGraphqlFullstack.getUserInfoValue(/* () */0)));
                                                                  }), Most.flatMap((function (_result) {
                                                                        return TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserLoginGraphqlTool$ReasonGraphqlFullstack.getLoginUserByUserName("amy"), UserLoginValue$ReasonGraphqlFullstack.getUserLoginValue(/* () */0)));
                                                                      }), TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserLoginGraphqlTool$ReasonGraphqlFullstack.addLoginUser(newUserLoginRecord), UserLoginValue$ReasonGraphqlFullstack.getUserLoginValue(/* () */0))))))).then((function (param) {
                                                          var match = errorRef[0];
                                                          if (match !== undefined) {
                                                            return Promise.resolve(Wonder_jest.fail(match));
                                                          } else {
                                                            return Promise.resolve(Wonder_jest.Expect[/* toEqual */12](/* array */[UserInfoDataTool$ReasonGraphqlFullstack.buildGraphQLResult(newUserInfoRecordRef[0])], Wonder_jest.Expect[/* expect */0](resultRef[0].userInfo)));
                                                          }
                                                        }));
                                          }));
                                    Wonder_jest.testPromise("test update user info's nick_name", undefined, (function (param) {
                                            var match = TestTool$ReasonGraphqlFullstack.buildTestResultAndErrRef(/* () */0);
                                            var errorRef = match[1];
                                            var resultRef = match[0];
                                            var userInfoDataArray = UserInfoDataTool$ReasonGraphqlFullstack.getUserInfoData(/* () */0);
                                            var userInfoFirstItem = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(userInfoDataArray);
                                            var targetUserId = userInfoFirstItem[/* userId */1];
                                            var targetNickName = "mickey";
                                            return TestTool$ReasonGraphqlFullstack.setResultOrErrorValue(resultRef, errorRef, Most.flatMap((function (_result) {
                                                                return TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserInfoGraphqlTool$ReasonGraphqlFullstack.getUserInfoByUserId(targetUserId), UserInfoValue$ReasonGraphqlFullstack.getUserInfoValue(/* () */0)));
                                                              }), TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserInfoGraphqlTool$ReasonGraphqlFullstack.updateUserInfoNickName(targetUserId, targetNickName), UserInfoValue$ReasonGraphqlFullstack.getUserInfoValue(/* () */0))))).then((function (param) {
                                                          var match = errorRef[0];
                                                          if (match !== undefined) {
                                                            return Promise.resolve(Wonder_jest.fail(match));
                                                          } else {
                                                            var userInfoObj = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(resultRef[0].userInfo);
                                                            return Promise.resolve(Curry._2(Wonder_jest.Expect[/* Operators */25][/* = */5], Wonder_jest.Expect[/* expect */0](userInfoObj.nick_name), targetNickName));
                                                          }
                                                        }));
                                          }));
                                    return Wonder_jest.testPromise("test update user info's profile_picture ", undefined, (function (param) {
                                                  var match = TestTool$ReasonGraphqlFullstack.buildTestResultAndErrRef(/* () */0);
                                                  var errorRef = match[1];
                                                  var resultRef = match[0];
                                                  var userInfoDataArray = UserInfoDataTool$ReasonGraphqlFullstack.getUserInfoData(/* () */0);
                                                  var userInfoFirstItem = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(userInfoDataArray);
                                                  var targetUserId = userInfoFirstItem[/* userId */1];
                                                  var targetPicture = "/image/mickey.png";
                                                  return TestTool$ReasonGraphqlFullstack.setResultOrErrorValue(resultRef, errorRef, Most.flatMap((function (param) {
                                                                      return TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserInfoGraphqlTool$ReasonGraphqlFullstack.getUserInfoByUserId(targetUserId), UserInfoValue$ReasonGraphqlFullstack.getUserInfoValue(/* () */0)));
                                                                    }), TestTool$ReasonGraphqlFullstack.handleRunGraphQLFail(GraphqlTool$ReasonGraphqlFullstack.runGraphql(UserInfoGraphqlTool$ReasonGraphqlFullstack.updateUserInfoProfilePicture(targetUserId, targetPicture), UserInfoValue$ReasonGraphqlFullstack.getUserInfoValue(/* () */0))))).then((function (param) {
                                                                var match = errorRef[0];
                                                                if (match !== undefined) {
                                                                  return Promise.resolve(Wonder_jest.fail(match));
                                                                } else {
                                                                  var userInfoObj = ArrayUtils$ReasonGraphqlFullstack.unsafeGetFirst(resultRef[0].userInfo);
                                                                  return Promise.resolve(Curry._2(Wonder_jest.Expect[/* Operators */25][/* = */5], Wonder_jest.Expect[/* expect */0](userInfoObj.profile_picture), targetPicture));
                                                                }
                                                              }));
                                                }));
                                  }));
                    }));
      }));

/*  Not a pure module */
