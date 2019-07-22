'use strict';

var MySql2 = require("wonder-bs-mysql2/lib/js/src/MySql2.bs.js");
var MysqlTool$ReasonGraphqlFullstack = require("./MysqlTool.js");
var MysqlCommon$ReasonGraphqlFullstack = require("../../../src/server/model/MysqlCommon.js");
var StateService$ReasonGraphqlFullstack = require("../../../src/server/service/state/StateService.js");
var StateDataService$ReasonGraphqlFullstack = require("../../../src/server/service/state/data/StateDataService.js");

function createNoDataBaseConnect(param) {
  return MySql2.Connection[/* connect */3](param[/* host */0], param[/* port */4], param[/* user */1], param[/* password */2], undefined, /* () */0);
}

function _getDropDatabaseSql(param) {
  return "drop database if exists graphql_test;";
}

function _getCreateTestDatabaseSql(param) {
  return "CREATE DATABASE graphql_test;";
}

function _getUseGraphqlTest(param) {
  return "use graphql_test;";
}

function dropDataBase(param) {
  return MysqlTool$ReasonGraphqlFullstack.handleSqlForGraphQL(createNoDataBaseConnect(StateService$ReasonGraphqlFullstack.getMysqlConfig(StateDataService$ReasonGraphqlFullstack.getState(/* () */0))), "drop database if exists graphql_test;", undefined, /* () */0);
}

function createDataBase(param) {
  return MysqlTool$ReasonGraphqlFullstack.handleSqlForGraphQL(createNoDataBaseConnect(StateService$ReasonGraphqlFullstack.getMysqlConfig(StateDataService$ReasonGraphqlFullstack.getState(/* () */0))), "CREATE DATABASE graphql_test;", undefined, /* () */0);
}

function useDataBase(param) {
  return MysqlTool$ReasonGraphqlFullstack.handleSqlForGraphQL(MysqlCommon$ReasonGraphqlFullstack.createMysqlConnect(StateService$ReasonGraphqlFullstack.getMysqlConfig(StateDataService$ReasonGraphqlFullstack.getState(/* () */0))), "use graphql_test;", undefined, /* () */0);
}

exports.createNoDataBaseConnect = createNoDataBaseConnect;
exports._getDropDatabaseSql = _getDropDatabaseSql;
exports._getCreateTestDatabaseSql = _getCreateTestDatabaseSql;
exports._getUseGraphqlTest = _getUseGraphqlTest;
exports.dropDataBase = dropDataBase;
exports.createDataBase = createDataBase;
exports.useDataBase = useDataBase;
/* MySql2 Not a pure module */
