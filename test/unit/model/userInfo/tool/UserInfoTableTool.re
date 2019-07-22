open UserInfoDataTool;

let _getCreateUserInfoTableSql = () => {|
  CREATE TABLE IF NOT EXISTS `user_info` (
      id int(11) NOT NULL AUTO_INCREMENT,
      user_id int(11) NOT NULL,
      nick_name varchar(50) NOT NULL,
      profile_picture varchar(64) NOT NULL,
      PRIMARY KEY (id),
      foreign key(user_id) references user_login(id)
  ) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
|};

let _getInsertUserInfoFakeDataSql = dataArray =>
  dataArray
  |> WonderCommonlib.ArrayService.reduceOneParami(
       (. result, {id, userId, nickName, profilePicture}, index) => {
         let itemSqlStr = {j| ($id,$userId,"$nickName", "$profilePicture")|j};

         ValueUtils.isValueEqual(dataArray |> Js.Array.length, index + 1) ?
           result ++ itemSqlStr ++ ";" : result ++ itemSqlStr ++ ",";
       },
       "INSERT INTO user_info VALUES",
     );

let _createUserInfoTable = () =>
  MysqlTool.handleSqlForGraphQL(
    StateDataService.getState()
    |> StateService.getMysqlConfig
    |> MysqlCommon.createMysqlConnect,
    _getCreateUserInfoTableSql(),
    None,
    (),
  );

let _insertDataIntoUserInfo = dataArray =>
  MysqlTool.handleSqlForGraphQL(
    StateDataService.getState()
    |> StateService.getMysqlConfig
    |> MysqlCommon.createMysqlConnect,
    _getInsertUserInfoFakeDataSql(dataArray),
    None,
    (),
  );

let initUserInfoTable = dataArray =>
  _createUserInfoTable()
  |> WonderBsMost.Most.fromPromise
  |> WonderBsMost.Most.flatMap(_res =>
       _insertDataIntoUserInfo(dataArray) |> WonderBsMost.Most.fromPromise
     );