'use strict';

var Most = require("most");
var MysqlInitTool$ReasonGraphqlFullstack = require("./MysqlInitTool.js");
var StateInitTool$ReasonGraphqlFullstack = require("./StateInitTool.js");

function initTest(param) {
  return Most.tap((function (_res) {
                return StateInitTool$ReasonGraphqlFullstack.initState(/* () */0);
              }), Most.flatMap((function (_res) {
                    return Most.fromPromise(MysqlInitTool$ReasonGraphqlFullstack.useDataBase(/* () */0));
                  }), Most.flatMap((function (_res) {
                        return Most.fromPromise(MysqlInitTool$ReasonGraphqlFullstack.createDataBase(/* () */0));
                      }), Most.fromPromise(MysqlInitTool$ReasonGraphqlFullstack.dropDataBase(/* () */0)))));
}

function restoreMysql(param) {
  return Most.fromPromise(MysqlInitTool$ReasonGraphqlFullstack.dropDataBase(/* () */0));
}

exports.initTest = initTest;
exports.restoreMysql = restoreMysql;
/* most Not a pure module */
