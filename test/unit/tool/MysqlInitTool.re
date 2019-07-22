open ServerConfigParseType;

let createNoDataBaseConnect = ({host, user, password, database, port}) =>
  MySql2.Connection.connect(~host, ~user, ~password, ~port, ());

let _getDropDatabaseSql = () => "drop database if exists graphql_test;";

let _getCreateTestDatabaseSql = () => "CREATE DATABASE graphql_test;";

let _getUseGraphqlTest = () => "use graphql_test;";

let dropDataBase = () =>
  MysqlTool.handleSqlForGraphQL(
    StateDataService.getState()
    |> StateService.getMysqlConfig
    |> createNoDataBaseConnect,
    _getDropDatabaseSql(),
    None,
    (),
  );

let createDataBase = () =>
  MysqlTool.handleSqlForGraphQL(
    StateDataService.getState()
    |> StateService.getMysqlConfig
    |> createNoDataBaseConnect,
    _getCreateTestDatabaseSql(),
    None,
    (),
  );

let useDataBase = () =>
  MysqlTool.handleSqlForGraphQL(
    StateDataService.getState()
    |> StateService.getMysqlConfig
    |> MysqlCommon.createMysqlConnect,
    _getUseGraphqlTest(),
    None,
    (),
  );