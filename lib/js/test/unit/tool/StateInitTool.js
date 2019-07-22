'use strict';

var StateDataService$ReasonGraphqlFullstack = require("../../../src/server/service/state/data/StateDataService.js");
var CreateMysqlService$ReasonGraphqlFullstack = require("../../../src/server/service/record/mysql/CreateMysqlService.js");
var CreateStateService$ReasonGraphqlFullstack = require("../../../src/server/service/state/CreateStateService.js");
var ServerConfigParseUtils$ReasonGraphqlFullstack = require("../../../src/server/config/utils/ServerConfigParseUtils.js");

function initState(param) {
  var config = ServerConfigParseUtils$ReasonGraphqlFullstack.getServerConfig(/* () */0);
  StateDataService$ReasonGraphqlFullstack.setState(CreateStateService$ReasonGraphqlFullstack.create(CreateMysqlService$ReasonGraphqlFullstack.createMysqlRecord(config[/* mysqlTestConfig */1])));
  return /* () */0;
}

exports.initState = initState;
/* StateDataService-ReasonGraphqlFullstack Not a pure module */
