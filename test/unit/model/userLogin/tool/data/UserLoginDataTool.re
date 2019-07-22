type userLoginRecord = {
  id: string,
  userName: string,
  password: string,
  email: string,
  date: string,
  code: string,
  isActive: int,
};

let getUserLoginDataArray = date => {
  let code = 7878 |> Crypto.getCryptoValueFromInt;

  [|
    {
      id: "1",
      userName: "mickey1",
      password: "asd0001",
      email: "340606701@qq.com",
      date,
      code,
      isActive: 0,
    },
    {
      id: "2",
      userName: "mickey2",
      password: "asd0002",
      email: "340606702@qq.com",
      date,
      code,
      isActive: 0,
    },
    {
      id: "3",
      userName: "mickey3",
      password: "asd0003",
      email: "340606703@qq.com",
      date,
      code,
      isActive: 1,
    },
  |];
};

let buildGraphQLResult = userLoginRecord => {
  "id": userLoginRecord.id,
  "user_name": userLoginRecord.userName,
  "password": userLoginRecord.password |> Crypto.getCryptoValue,
  "email": userLoginRecord.email,
  "code": userLoginRecord.code,
  "create_date": userLoginRecord.date,
  "is_active": userLoginRecord.isActive,
};

let buildGraphQLAllData = dataArray =>
  dataArray
  |> WonderCommonlib.ArrayService.reduceOneParam(
       (. resultArray, userLoginItem) =>
         resultArray |> ArrayUtils.push(buildGraphQLResult(userLoginItem)),
       [||],
     );

let buildGraphQLDataByUserName = (userName, dataArray) =>
  dataArray
  |> Js.Array.filter(userLoginItem =>
       ValueUtils.isValueEqual(userLoginItem.userName, userName)
     )
  |> Js.Array.map(userLoginItem => buildGraphQLResult(userLoginItem));

let buildGraphQLDataByEmail = (email, dataArray) =>
  dataArray
  |> Js.Array.filter(userLoginItem =>
       ValueUtils.isValueEqual(userLoginItem.email, email)
     )
  |> Js.Array.map(userLoginItem => buildGraphQLResult(userLoginItem));