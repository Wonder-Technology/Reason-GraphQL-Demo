open Express;

open WonderBsJson;

open WonderBsMost;

open UserRouteType.RegisterUserType;

let _handleSuccess = (response, stream) =>
  stream
  |> Most.concatMap(((userName, email, nickName)) =>
       ResponseUtils.buildResponseDataJson(
         ~status=Success |> convertSelfToInt,
         (),
       )
       |> Response.sendJson(_, response)
       |> Most.just
     );

let _getValidParam = queryDataObj => {
  let userName = queryDataObj##userName;
  let password = queryDataObj##password;
  let email = queryDataObj##email;
  let nickName = queryDataObj##nickName;

  switch (
    userName |> ValueUtils.isValueValid,
    password |> ValueUtils.isValueValid,
    email |> ValueUtils.isValueValid,
    nickName |> ValueUtils.isValueValid,
  ) {
  | (true, true, true, true) =>
    (userName, password |> Crypto.getCryptoValue, email, nickName)
    |> Most.just
  | _ =>
    MostHelper.throwErrorWithType((
      ParamError |> convertSelfToInt,
      "the param is error",
    ))
  };
};

let logicContent = (request, response, code) => {
  let conn =
    StateDataService.getState()
    |> StateService.getMysqlConfig
    |> MysqlCommon.createMysqlConnect;

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
  |> Most.flatMap(((userName, _password, email, nickName) as paramTuple) =>
       paramTuple
       |> RegisterUserTransaction.handleTransaction(conn, code)
       |> Most.recoverWith(error =>
            MostHelper.throwErrorWithType((
              DBSqlError |> convertSelfToInt,
              error |> ResponseUtils.BcResponse.unsafeGetBcErrorMssage,
            ))
          )
       |> Most.map(_ => (userName, email, nickName))
     )
  |> _handleSuccess(response)
  |> ResponseUtils.handleFail(response)
  |> Most.tap(_ => MySql2.Connection.close(conn));
};

let handlerLogic = (_, request, response) => {
  let code = DomHelper.getRandomNumber() |> Crypto.getCryptoValueFromInt;
  logicContent(request, response, code) |> Most.drain |> Obj.magic;
};