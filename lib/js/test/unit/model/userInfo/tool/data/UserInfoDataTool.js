'use strict';

var ValueUtils$ReasonGraphqlFullstack = require("../../../../../../src/utils/ValueUtils.js");

function getUserInfoData(param) {
  return /* array */[
          /* record */[
            /* id */"1",
            /* userId */"1",
            /* nickName */"mickey1",
            /* profilePicture */"/image/logo.png"
          ],
          /* record */[
            /* id */"2",
            /* userId */"2",
            /* nickName */"mickey2",
            /* profilePicture */"/image/logo.png"
          ],
          /* record */[
            /* id */"3",
            /* userId */"3",
            /* nickName */"mickey3",
            /* profilePicture */"/image/logo.png"
          ]
        ];
}

function buildGraphQLResult(userInfoRecord) {
  return {
          id: userInfoRecord[/* id */0],
          user_id: userInfoRecord[/* userId */1],
          nick_name: userInfoRecord[/* nickName */2],
          profile_picture: userInfoRecord[/* profilePicture */3]
        };
}

function buildGraphQLDataByUserId(userId, dataArray) {
  return dataArray.filter((function (userInfoItem) {
                  return ValueUtils$ReasonGraphqlFullstack.isValueEqual(userInfoItem[/* userId */1], userId);
                })).map(buildGraphQLResult);
}

exports.getUserInfoData = getUserInfoData;
exports.buildGraphQLResult = buildGraphQLResult;
exports.buildGraphQLDataByUserId = buildGraphQLDataByUserId;
/* No side effect */
