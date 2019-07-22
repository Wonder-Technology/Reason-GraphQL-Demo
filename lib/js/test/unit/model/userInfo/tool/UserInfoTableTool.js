'use strict';

var Most = require("most");
var ArrayService$WonderCommonlib = require("wonder-commonlib/lib/js/src/ArrayService.js");
var MysqlTool$ReasonGraphqlFullstack = require("../../../tool/MysqlTool.js");
var ValueUtils$ReasonGraphqlFullstack = require("../../../../../src/utils/ValueUtils.js");
var MysqlCommon$ReasonGraphqlFullstack = require("../../../../../src/server/model/MysqlCommon.js");
var StateService$ReasonGraphqlFullstack = require("../../../../../src/server/service/state/StateService.js");
var StateDataService$ReasonGraphqlFullstack = require("../../../../../src/server/service/state/data/StateDataService.js");

function _getCreateUserInfoTableSql(param) {
  return "\n  CREATE TABLE IF NOT EXISTS `user_info` (\n      id int(11) NOT NULL AUTO_INCREMENT,\n      user_id int(11) NOT NULL,\n      nick_name varchar(50) NOT NULL,\n      profile_picture varchar(64) NOT NULL,\n      PRIMARY KEY (id),\n      foreign key(user_id) references user_login(id)\n  ) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;\n";
}

function _getInsertUserInfoFakeDataSql(dataArray) {
  return ArrayService$WonderCommonlib.reduceOneParami((function (result, param, index) {
                var itemSqlStr = " (" + (String(param[/* id */0]) + ("," + (String(param[/* userId */1]) + (",\"" + (String(param[/* nickName */2]) + ("\", \"" + (String(param[/* profilePicture */3]) + "\")")))))));
                var match = ValueUtils$ReasonGraphqlFullstack.isValueEqual(dataArray.length, index + 1 | 0);
                if (match) {
                  return result + (itemSqlStr + ";");
                } else {
                  return result + (itemSqlStr + ",");
                }
              }), "INSERT INTO user_info VALUES", dataArray);
}

function _createUserInfoTable(param) {
  return MysqlTool$ReasonGraphqlFullstack.handleSqlForGraphQL(MysqlCommon$ReasonGraphqlFullstack.createMysqlConnect(StateService$ReasonGraphqlFullstack.getMysqlConfig(StateDataService$ReasonGraphqlFullstack.getState(/* () */0))), "\n  CREATE TABLE IF NOT EXISTS `user_info` (\n      id int(11) NOT NULL AUTO_INCREMENT,\n      user_id int(11) NOT NULL,\n      nick_name varchar(50) NOT NULL,\n      profile_picture varchar(64) NOT NULL,\n      PRIMARY KEY (id),\n      foreign key(user_id) references user_login(id)\n  ) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;\n", undefined, /* () */0);
}

function _insertDataIntoUserInfo(dataArray) {
  return MysqlTool$ReasonGraphqlFullstack.handleSqlForGraphQL(MysqlCommon$ReasonGraphqlFullstack.createMysqlConnect(StateService$ReasonGraphqlFullstack.getMysqlConfig(StateDataService$ReasonGraphqlFullstack.getState(/* () */0))), _getInsertUserInfoFakeDataSql(dataArray), undefined, /* () */0);
}

function initUserInfoTable(dataArray) {
  return Most.flatMap((function (_res) {
                return Most.fromPromise(_insertDataIntoUserInfo(dataArray));
              }), Most.fromPromise(_createUserInfoTable(/* () */0)));
}

exports._getCreateUserInfoTableSql = _getCreateUserInfoTableSql;
exports._getInsertUserInfoFakeDataSql = _getInsertUserInfoFakeDataSql;
exports._createUserInfoTable = _createUserInfoTable;
exports._insertDataIntoUserInfo = _insertDataIntoUserInfo;
exports.initUserInfoTable = initUserInfoTable;
/* most Not a pure module */
