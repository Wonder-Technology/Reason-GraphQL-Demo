'use strict';

var ArrayService$WonderCommonlib = require("wonder-commonlib/lib/js/src/ArrayService.js");
var Crypto$ReasonGraphqlFullstack = require("../../../../../../src/external/Crypto.js");
var ArrayUtils$ReasonGraphqlFullstack = require("../../../../../../src/utils/ArrayUtils.js");
var ValueUtils$ReasonGraphqlFullstack = require("../../../../../../src/utils/ValueUtils.js");

function getUserLoginDataArray(date) {
  var code = Crypto$ReasonGraphqlFullstack.getCryptoValueFromInt(7878);
  return /* array */[
          /* record */[
            /* id */"1",
            /* userName */"mickey1",
            /* password */"asd0001",
            /* email */"340606701@qq.com",
            /* date */date,
            /* code */code,
            /* isActive */0
          ],
          /* record */[
            /* id */"2",
            /* userName */"mickey2",
            /* password */"asd0002",
            /* email */"340606702@qq.com",
            /* date */date,
            /* code */code,
            /* isActive */0
          ],
          /* record */[
            /* id */"3",
            /* userName */"mickey3",
            /* password */"asd0003",
            /* email */"340606703@qq.com",
            /* date */date,
            /* code */code,
            /* isActive */1
          ]
        ];
}

function buildGraphQLResult(userLoginRecord) {
  return {
          id: userLoginRecord[/* id */0],
          user_name: userLoginRecord[/* userName */1],
          password: Crypto$ReasonGraphqlFullstack.getCryptoValue(userLoginRecord[/* password */2]),
          email: userLoginRecord[/* email */3],
          code: userLoginRecord[/* code */5],
          create_date: userLoginRecord[/* date */4],
          is_active: userLoginRecord[/* isActive */6]
        };
}

function buildGraphQLAllData(dataArray) {
  return ArrayService$WonderCommonlib.reduceOneParam((function (resultArray, userLoginItem) {
                return ArrayUtils$ReasonGraphqlFullstack.push(buildGraphQLResult(userLoginItem), resultArray);
              }), /* array */[], dataArray);
}

function buildGraphQLDataByUserName(userName, dataArray) {
  return dataArray.filter((function (userLoginItem) {
                  return ValueUtils$ReasonGraphqlFullstack.isValueEqual(userLoginItem[/* userName */1], userName);
                })).map(buildGraphQLResult);
}

function buildGraphQLDataByEmail(email, dataArray) {
  return dataArray.filter((function (userLoginItem) {
                  return ValueUtils$ReasonGraphqlFullstack.isValueEqual(userLoginItem[/* email */3], email);
                })).map(buildGraphQLResult);
}

exports.getUserLoginDataArray = getUserLoginDataArray;
exports.buildGraphQLResult = buildGraphQLResult;
exports.buildGraphQLAllData = buildGraphQLAllData;
exports.buildGraphQLDataByUserName = buildGraphQLDataByUserName;
exports.buildGraphQLDataByEmail = buildGraphQLDataByEmail;
/* Crypto-ReasonGraphqlFullstack Not a pure module */
