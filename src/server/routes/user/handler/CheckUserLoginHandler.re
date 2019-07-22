open WonderBsJson;

open Express;

open WonderBsMost;

open UserRouteType.CheckUserLoginType;

let _handleSuccess = (response, stream) =>
  stream
  |> Most.concatMap(userObj =>
       ResponseUtils.buildResponseDataJson(
         ~status=Success |> convertSelfToInt,
         ~data=
           Json.Encode.object_([
             ("userName", Json.Encode.string(userObj##user_name)),
             ("id", Json.Encode.int(userObj##id)),
           ]),
         (),
       )
       |> Response.sendJson(_, response)
       |> Most.just
     );

let _getValidParam = queryData => {
  let userName = queryData##userName;
  let password = queryData##password;

  switch (
    userName |> ValueUtils.isValueValid,
    password |> ValueUtils.isValueValid,
  ) {
  | (true, true) =>
    (userName, password |> Crypto.getCryptoValue) |> Most.just
  | _ =>
    MostHelper.throwErrorWithType((
      ParamError |> convertSelfToInt,
      "the param is error",
    ))
  };
};

let logicContent = (request, response) =>
  Request.bodyJSON(request)
  |> Most.just
  |> Most.flatMap(queryData =>
       switch (queryData) {
       | None =>
         MostHelper.throwErrorWithType((
           InValidParam |> convertSelfToInt,
           "param is invalid",
         ))
       | Some(queryData) => queryData |> JsonType.convertToJsObj |> Most.just
       }
     )
  |> Most.flatMap(_getValidParam)
  |> Most.flatMap(((userName, password)) =>
       OperateUserLoginGraphql.getUserLoginDataByUserName(userName)
       |> Most.flatMap(response =>
            response##errors |> ValueUtils.isValueValid ?
              MostHelper.throwErrorWithType((
                DBSqlError |> convertSelfToInt,
                response##errors
                |> ResponseUtils.GraphQLResponse.getErrorMessage,
              )) :
              response##data |> Most.just
          )
       |> Most.flatMap(userData =>
            switch (userData##loginUser |> ArrayUtils.getFirst) {
            | None =>
              MostHelper.throwErrorWithType((
                UserNameNotExist |> convertSelfToInt,
                "userName is not exist",
              ))

            | Some(user) => user |> Most.just
            }
          )
       |> Most.flatMap(userObj =>
            ValueUtils.isValueEqual(userObj##password, password) ?
              userObj |> Most.just :
              MostHelper.throwErrorWithType((
                PasswordError |> convertSelfToInt,
                "the password error",
              ))
          )
       |> Most.flatMap(userObj =>
            userObj##is_active === 1 ?
              userObj |> Most.just :
              MostHelper.throwErrorWithType((
                UserNotActive |> convertSelfToInt,
                "the user not active",
              ))
          )
     )
  |> _handleSuccess(response)
  |> ResponseUtils.handleFail(response);

let handleLogic = (_, request, response) =>
  logicContent(request, response) |> Most.drain |> Obj.magic;