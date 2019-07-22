open MysqlOperate;

let getUserInfoValue = () => {
  let mysqlPool = StateDataService.getState() |> StateService.getMysqlPool;

  {
    "userInfo": param =>
      PromiseUtils.await(
        GraphqlOperate.handleSqlForGraphQL(
          mysqlPool,
          OperateUserInfoSql.selectByParamSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
    "addUserInfo": param =>
      PromiseUtils.await(
        GraphqlOperate.handleSqlForGraphQL(
          mysqlPool,
          OperateUserInfoSql.addSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
    "updateUserInfoProfilePicture": param =>
      PromiseUtils.await(
        GraphqlOperate.handleSqlForGraphQL(
          mysqlPool,
          OperateUserInfoSql.updateProfilePictureSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
    "updateUserInfoNickName": param =>
      PromiseUtils.await(
        GraphqlOperate.handleSqlForGraphQL(
          mysqlPool,
          OperateUserInfoSql.updateNickNameSql,
          Some(MySql2.Params.named(param)),
        ),
      ),
  }
  |> Obj.magic;
};