open ServerConfigParseType;

let initState = () => {
  let config = ServerConfigParseUtils.getServerConfig();

  CreateStateService.create(
    CreateMysqlService.createMysqlRecord(config.mysqlTestConfig),
  )
  |> StateDataService.setState
  |> ignore;
};