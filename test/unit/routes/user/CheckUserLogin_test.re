open UserRouteType.CheckUserLoginType;

open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

open WonderBsMost;

open UserLoginDataTool;

let _ =
  describe("test route: checkUserLogin", () => {
    let sandbox = getSandboxDefaultVal();

    beforeEachPromise(() => {
      sandbox := createSandbox();

      TestInitTool.initTest() |> Most.drain;
    });
    afterEachPromise(() => {
      restoreSandbox(refJsObjToSandbox(sandbox^));

      TestInitTool.restoreMysql() |> Most.drain;
    });

    describe("init fake database and table", () => {
      let date =
        MomentRe.momentNow() |> MomentRe.Moment.format("YYYY-MM-DD HH:mm:ss");

      beforeEachPromise(() =>
        getUserLoginDataArray(date)
        |> UserLoginTableTool.initUserLoginTable
        |> Most.recoverWith(_error =>
             "init userLogin table error" |> Most.just
           )
        |> Most.drain
      );

      describe("if param is undefined or null", () =>
        testPromise("should response status and error msg", () => {
          let request = RequestTool.buildFakePostRequest(Js.Null.empty);
          let responseObj = sandbox |> ResponseTool.buildFakeResponse;

          CheckUserLoginHandler.logicContent(
            request |> RequestTool.convertToRequest,
            responseObj |> ResponseTool.convertToResponse,
          )
          |> Most.drain
          |> Js.Promise.then_(_ =>
               responseObj##json
               |> expect
               |> toCalledWith([|
                    ResponseUtils.buildResponseDataJson(
                      ~status=InValidParam |> convertSelfToInt,
                      ~msg="param is invalid",
                      (),
                    ),
                  |])
               |> Js.Promise.resolve
             );
        })
      );

      describe("if param has no userName or password", () =>
        testPromise("should response status and error msg", () => {
          let request =
            RequestTool.buildFakePostRequest({"userName": "mickey"});
          let responseObj = sandbox |> ResponseTool.buildFakeResponse;

          CheckUserLoginHandler.logicContent(
            request |> RequestTool.convertToRequest,
            responseObj |> ResponseTool.convertToResponse,
          )
          |> Most.drain
          |> Js.Promise.then_(_ =>
               responseObj##json
               |> expect
               |> toCalledWith([|
                    ResponseUtils.buildResponseDataJson(
                      ~status=ParamError |> convertSelfToInt,
                      ~msg="the param is error",
                      (),
                    ),
                  |])
               |> Js.Promise.resolve
             );
        })
      );

      describe("if param userName not exist in table", () =>
        testPromise("should response status and error msg", () => {
          let request =
            RequestTool.buildFakePostRequest({
              "userName": "mickey",
              "password": "asd1313",
            });
          let responseObj = sandbox |> ResponseTool.buildFakeResponse;

          CheckUserLoginHandler.logicContent(
            request |> RequestTool.convertToRequest,
            responseObj |> ResponseTool.convertToResponse,
          )
          |> Most.drain
          |> Js.Promise.then_(_ =>
               responseObj##json
               |> expect
               |> toCalledWith([|
                    ResponseUtils.buildResponseDataJson(
                      ~status=UserNameNotExist |> convertSelfToInt,
                      ~msg="userName is not exist",
                      (),
                    ),
                  |])
               |> Js.Promise.resolve
             );
        })
      );

      describe("if param password not matching in table", () =>
        testPromise("should response status and error msg", () => {
          let userLoginDataArray = getUserLoginDataArray(date);
          let userLoginFirstItem =
            userLoginDataArray |> ArrayUtils.unsafeGetFirst;

          let request =
            RequestTool.buildFakePostRequest({
              "userName": userLoginFirstItem.userName,
              "password": "asd1111",
            });
          let responseObj = sandbox |> ResponseTool.buildFakeResponse;

          CheckUserLoginHandler.logicContent(
            request |> RequestTool.convertToRequest,
            responseObj |> ResponseTool.convertToResponse,
          )
          |> Most.drain
          |> Js.Promise.then_(_ =>
               responseObj##json
               |> expect
               |> toCalledWith([|
                    ResponseUtils.buildResponseDataJson(
                      ~status=PasswordError |> convertSelfToInt,
                      ~msg="the password error",
                      (),
                    ),
                  |])
               |> Js.Promise.resolve
             );
        })
      );

      describe("if target user is not active", () =>
        testPromise("should response status and error msg", () => {
          let userLoginDataArray = getUserLoginDataArray(date);
          let userLoginFirstItem =
            userLoginDataArray |> ArrayUtils.unsafeGetFirst;

          let request =
            RequestTool.buildFakePostRequest({
              "userName": userLoginFirstItem.userName,
              "password": userLoginFirstItem.password,
            });
          let responseObj = sandbox |> ResponseTool.buildFakeResponse;

          CheckUserLoginHandler.logicContent(
            request |> RequestTool.convertToRequest,
            responseObj |> ResponseTool.convertToResponse,
          )
          |> Most.drain
          |> Js.Promise.then_(_ =>
               responseObj##json
               |> expect
               |> toCalledWith([|
                    ResponseUtils.buildResponseDataJson(
                      ~status=UserNotActive |> convertSelfToInt,
                      ~msg="the user not active",
                      (),
                    ),
                  |])
               |> Js.Promise.resolve
             );
        })
      );

      describe("else, check user login success", () =>
        testPromise("should response status and success msg", () => {
          open WonderBsJson;

          let userLoginDataArray = getUserLoginDataArray(date);
          let userLoginLastItem =
            userLoginDataArray |> ArrayUtils.unsafeGetLast;

          let request =
            RequestTool.buildFakePostRequest({
              "userName": userLoginLastItem.userName,
              "password": userLoginLastItem.password,
            });
          let responseObj = sandbox |> ResponseTool.buildFakeResponse;

          CheckUserLoginHandler.logicContent(
            request |> RequestTool.convertToRequest,
            responseObj |> ResponseTool.convertToResponse,
          )
          |> Most.drain
          |> Js.Promise.then_(_ =>
               responseObj##json
               |> expect
               |> toCalledWith([|
                    ResponseUtils.buildResponseDataJson(
                      ~status=Success |> convertSelfToInt,
                      ~data=
                        Json.Encode.object_([
                          (
                            "userName",
                            Json.Encode.string(userLoginLastItem.userName),
                          ),
                          ("id", Json.Encode.string(userLoginLastItem.id)),
                        ]),
                      (),
                    ),
                  |])
               |> Js.Promise.resolve
             );
        })
      );
    });
  });