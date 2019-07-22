open WonderBsJson;

open WonderBsMost;

open Express;

open BcErrorType;

let buildResponseDataJson =
    (~status, ~data=Json.Encode.object_([]), ~msg="ok", ()) =>
  Json.Encode.object_([
    ("status", Json.Encode.int(status)),
    ("data", data),
    ("msg", Json.Encode.string(msg)),
  ]);

let handleFail = (response, stream) =>
  stream
  |> Most.recoverWith(error => {
       let (errType, errMsg) = error |> BcErrorType.convertJsExnToBcErr;

       errType |> ValueUtils.isValueValid ?
         buildResponseDataJson(~status=errType, ~msg=errMsg, ())
         |> Response.sendJson(_, response)
         |> Most.just :
         buildResponseDataJson(
           ~status=-1,
           ~msg="500, the server error, please check server",
           (),
         )
         |> Response.sendJson(_, response)
         |> Most.just;
     });

module GraphQLResponse = {
  let isMutationResponseSuccess = responseData =>
    (responseData |> JsonType.parseJsonConvertJsObj)##result === "success";

  let getErrorMessage = [%raw
    errorArray => "
      let error =  errorArray[0].message;

      return error;
  "
  ];
};

module GitHubResponse = {
  let getErrorMessage = [%raw
    errorArray => "
      let error =  errorArray[0].message;

      return error;
  "
  ];
};

module BcResponse = {
  let unsafeGetBcErrorMssage = exn =>
    switch (exn |> convertJsExnToArrayStr |> ArrayUtils.getLast) {
    | None => "execute sql param is undefined"
    | Some(error) => error
    };
};