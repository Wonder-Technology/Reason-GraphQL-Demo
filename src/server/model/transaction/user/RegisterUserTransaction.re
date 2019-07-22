open WonderBsMost;

open MysqlOperate;

open TransactionType;

open WonderBsJson;
let handleTransaction = (conn, code, (userName, password, email, nickName)) => {
  let generateUserInfoParam = id =>
    Some(
      MySql2.Params.named(
        Json.Encode.object_([
          ("userId", Json.Encode.int(id)),
          ("nickName", Json.Encode.string(nickName)),
          (
            "profilePicture",
            Json.Encode.string("/image/" ++ Image.getDefaultImageName()),
          ),
        ]),
      ),
    );

  let userLoginParam =
    Json.Encode.object_([
      ("userName", Json.Encode.string(userName)),
      ("password", Json.Encode.string(password)),
      ("email", Json.Encode.string(email)),
      ("code", Json.Encode.string(code)),
      (
        "createDate",
        Json.Encode.string(
          MomentRe.momentNow()
          |> MomentRe.Moment.format("YYYY-MM-DD HH:mm:ss"),
        ),
      ),
      ("isActive", Json.Encode.int(0)),
    ]);

  let transactionArray = [|
    {
      sql: OperateUserLoginSql.addSql,
      param: Some(MySql2.Params.named(userLoginParam)),
    },
    {sql: OperateUserInfoSql.addSql, param: None},
  |];

  TransactionMonitor.transactionMonitor(
    conn,
    transactionArray,
    Some(generateUserInfoParam),
  );
};