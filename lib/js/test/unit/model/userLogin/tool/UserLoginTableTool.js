'use strict';

var Most = require("most");
var ArrayService$WonderCommonlib = require("wonder-commonlib/lib/js/src/ArrayService.js");
var Crypto$ReasonGraphqlFullstack = require("../../../../../src/external/Crypto.js");
var MysqlTool$ReasonGraphqlFullstack = require("../../../tool/MysqlTool.js");
var ValueUtils$ReasonGraphqlFullstack = require("../../../../../src/utils/ValueUtils.js");
var MysqlCommon$ReasonGraphqlFullstack = require("../../../../../src/server/model/MysqlCommon.js");
var StateService$ReasonGraphqlFullstack = require("../../../../../src/server/service/state/StateService.js");
var StateDataService$ReasonGraphqlFullstack = require("../../../../../src/server/service/state/data/StateDataService.js");

function _getCreateUserLoginTableSql(param) {
  return "\n  CREATE TABLE IF NOT EXISTS `user_login` (\n      id int(11) NOT NULL AUTO_INCREMENT,\n      user_name varchar(50) NOT NULL,\n      password varchar(128) NOT NULL,\n      email varchar(50) NOT NULL,\n      create_date datetime NOT NULL,\n      code varchar(50) NOT NULL COMMENT '\xe9\xaa\x8c\xe8\xaf\x81\xe7\xa0\x81',\n      is_active tinyint NOT NULL default 0 COMMENT '\xe6\x98\xaf\xe5\x90\xa6\xe9\xaa\x8c\xe8\xaf\x81\xe9\x82\xae\xe7\xae\xb1,0=false, 1=true',\n      PRIMARY KEY (id)\n  ) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;\n";
}

function _getInsertUserLoginFakeDataSql(dataArray) {
  return ArrayService$WonderCommonlib.reduceOneParami((function (result, param, index) {
                var password = Crypto$ReasonGraphqlFullstack.getCryptoValue(param[/* password */2]);
                var itemSqlStr = " (" + (String(param[/* id */0]) + (",\"" + (String(param[/* userName */1]) + ("\", \"" + (String(password) + ("\", \"" + (String(param[/* email */3]) + ("\" , \"" + (String(param[/* date */4]) + ("\", \"" + (String(param[/* code */5]) + ("\", " + (String(param[/* isActive */6]) + ")")))))))))))));
                var match = ValueUtils$ReasonGraphqlFullstack.isValueEqual(dataArray.length, index + 1 | 0);
                if (match) {
                  return result + (itemSqlStr + ";");
                } else {
                  return result + (itemSqlStr + ",");
                }
              }), "INSERT INTO user_login VALUES", dataArray);
}

function _createUserLoginTable(param) {
  return MysqlTool$ReasonGraphqlFullstack.handleSqlForGraphQL(MysqlCommon$ReasonGraphqlFullstack.createMysqlConnect(StateService$ReasonGraphqlFullstack.getMysqlConfig(StateDataService$ReasonGraphqlFullstack.getState(/* () */0))), "\n  CREATE TABLE IF NOT EXISTS `user_login` (\n      id int(11) NOT NULL AUTO_INCREMENT,\n      user_name varchar(50) NOT NULL,\n      password varchar(128) NOT NULL,\n      email varchar(50) NOT NULL,\n      create_date datetime NOT NULL,\n      code varchar(50) NOT NULL COMMENT '\xe9\xaa\x8c\xe8\xaf\x81\xe7\xa0\x81',\n      is_active tinyint NOT NULL default 0 COMMENT '\xe6\x98\xaf\xe5\x90\xa6\xe9\xaa\x8c\xe8\xaf\x81\xe9\x82\xae\xe7\xae\xb1,0=false, 1=true',\n      PRIMARY KEY (id)\n  ) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;\n", undefined, /* () */0);
}

function _insertDataIntoUserLogin(dataArray) {
  return MysqlTool$ReasonGraphqlFullstack.handleSqlForGraphQL(MysqlCommon$ReasonGraphqlFullstack.createMysqlConnect(StateService$ReasonGraphqlFullstack.getMysqlConfig(StateDataService$ReasonGraphqlFullstack.getState(/* () */0))), _getInsertUserLoginFakeDataSql(dataArray), undefined, /* () */0);
}

function initUserLoginTable(dataArray) {
  return Most.flatMap((function (_res) {
                return Most.fromPromise(_insertDataIntoUserLogin(dataArray));
              }), Most.fromPromise(_createUserLoginTable(/* () */0)));
}

exports._getCreateUserLoginTableSql = _getCreateUserLoginTableSql;
exports._getInsertUserLoginFakeDataSql = _getInsertUserLoginFakeDataSql;
exports._createUserLoginTable = _createUserLoginTable;
exports._insertDataIntoUserLogin = _insertDataIntoUserLogin;
exports.initUserLoginTable = initUserLoginTable;
/* most Not a pure module */
