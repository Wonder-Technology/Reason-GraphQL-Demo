open StateDataType;

open ServerConfigParseType;

let serverConfig = ServerConfigParseUtils.getServerConfig();

let stateData = {
  state:
    CreateStateService.create(
      CreateMysqlService.createMysqlRecord(serverConfig.mysqlProductConfig),
    ),
};