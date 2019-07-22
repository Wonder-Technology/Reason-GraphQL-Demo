open UserLoginDataTool;

let _getCreateUserLoginTableSql = () => {|
  CREATE TABLE IF NOT EXISTS `user_login` (
      id int(11) NOT NULL AUTO_INCREMENT,
      user_name varchar(50) NOT NULL,
      password varchar(128) NOT NULL,
      email varchar(50) NOT NULL,
      create_date datetime NOT NULL,
      code varchar(50) NOT NULL COMMENT '验证码',
      is_active tinyint NOT NULL default 0 COMMENT '是否验证邮箱,0=false, 1=true',
      PRIMARY KEY (id)
  ) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
|};

let _getInsertUserLoginFakeDataSql = dataArray =>
  dataArray
  |> WonderCommonlib.ArrayService.reduceOneParami(
       (.
         result,
         {id, userName, password, email, date, code, isActive},
         index,
       ) => {
         let password = password |> Crypto.getCryptoValue;
         let itemSqlStr = {j| ($id,"$userName", "$password", "$email" , "$date", "$code", $isActive)|j};

         ValueUtils.isValueEqual(dataArray |> Js.Array.length, index + 1) ?
           result ++ itemSqlStr ++ ";" : result ++ itemSqlStr ++ ",";
       },
       "INSERT INTO user_login VALUES",
     );

let _createUserLoginTable = () =>
  MysqlTool.handleSqlForGraphQL(
    StateDataService.getState()
    |> StateService.getMysqlConfig
    |> MysqlCommon.createMysqlConnect,
    _getCreateUserLoginTableSql(),
    None,
    (),
  );

let _insertDataIntoUserLogin = dataArray =>
  MysqlTool.handleSqlForGraphQL(
    StateDataService.getState()
    |> StateService.getMysqlConfig
    |> MysqlCommon.createMysqlConnect,
    _getInsertUserLoginFakeDataSql(dataArray),
    None,
    (),
  );

let initUserLoginTable = dataArray =>
  _createUserLoginTable()
  |> WonderBsMost.Most.fromPromise
  |> WonderBsMost.Most.flatMap(_res =>
       _insertDataIntoUserLogin(dataArray) |> WonderBsMost.Most.fromPromise
     );