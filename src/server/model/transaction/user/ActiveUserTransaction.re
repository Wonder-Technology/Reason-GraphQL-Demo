open WonderBsMost;

open MysqlOperate;

open TransactionType;

open WonderBsJson;

let handleTransaction = (conn, userName, code) => {
  let updateCodeParam =
    Json.Encode.object_([
      ("userName", Json.Encode.string(userName)),
      ("code", Json.Encode.string(code)),
    ]);

  let updateIsActiveParam =
    Json.Encode.object_([
      ("userName", Json.Encode.string(userName)),
      ("isActive", Json.Encode.int(1)),
    ]);

  let transactionArray = [|
    {
      sql: OperateUserLoginSql.updateCodeSql,
      param: Some(MySql2.Params.named(updateCodeParam)),
    },
    {
      sql: OperateUserLoginSql.updateIsActiveSql,
      param: Some(MySql2.Params.named(updateIsActiveParam)),
    },
  |];

  TransactionMonitor.transactionMonitor(conn, transactionArray, None);
};