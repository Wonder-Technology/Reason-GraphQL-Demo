open StateType;

let getMysqlConfig = state => state.mysqlRecord |> MysqlService.getMysqlConfig;

let setMysqlConfig = (mysqlConfig, state) => {
  ...state,
  mysqlRecord: state.mysqlRecord |> MysqlService.setMysqlConfig(mysqlConfig),
};

let getMysqlPool = state => state.mysqlRecord |> MysqlService.getMysqlPool;

let setMysqlPool = (mysqlPool, state) => {
  ...state,
  mysqlRecord: state.mysqlRecord |> MysqlService.setMysqlPool(mysqlPool),
};