open MysqlOperate;

let getUserLoginValue = () => {
  let mysqlPool = StateDataService.getState() |> StateService.getMysqlPool;

  {
    "loginUsers": () =>
      PromiseUtils.await(
        GraphqlOperate.handleSqlForGraphQL(
          mysqlPool,
          OperateUserLoginSql.selectAllSql,
          None,
        ),
      ),
    "loginUser": param =>
      PromiseUtils.await(
        GraphqlOperate.handleSqlForGraphQL(
          mysqlPool,
          OperateUserLoginSql.selectByParamSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
    "addLoginUser": param =>
      PromiseUtils.await(
        GraphqlOperate.handleSqlForGraphQL(
          mysqlPool,
          OperateUserLoginSql.addSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
    "updateLoginUserIsActive": param =>
      PromiseUtils.await(
        GraphqlOperate.handleSqlForGraphQL(
          mysqlPool,
          OperateUserLoginSql.updateIsActiveSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
    "updateLoginUserPassword": param =>
      PromiseUtils.await(
        GraphqlOperate.handleSqlForGraphQL(
          mysqlPool,
          OperateUserLoginSql.updatePasswordSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
    "updateLoginUserCode": param =>
      PromiseUtils.await(
        GraphqlOperate.handleSqlForGraphQL(
          mysqlPool,
          OperateUserLoginSql.updateCodeSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
  }
  |> Obj.magic;
};