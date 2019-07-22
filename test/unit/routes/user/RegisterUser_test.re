open UserRouteType.RegisterUserType;

open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

open WonderBsMost;

open UserLoginDataTool;

let _ =
  describe("test route: registerUser", () => {
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
      let code = DomHelper.getRandomNumber() |> Crypto.getCryptoValueFromInt;

      beforeEachPromise(() =>
        getUserLoginDataArray(date)
        |> UserLoginTableTool.initUserLoginTable
        |> Most.flatMap(_res =>
             UserInfoDataTool.getUserInfoData()
             |> UserInfoTableTool.initUserInfoTable
           )
        |> Most.recoverWith(_error =>
             "init userLogin and userInfo table error" |> Most.just
           )
        |> Most.drain
      );

      describe("if param is undefined or null", () =>
        testPromise("should response status and error msg", () => {
          let request = RequestTool.buildFakePostRequest(Js.Undefined.empty);
          let responseObj = sandbox |> ResponseTool.buildFakeResponse;

          RegisterUserHandler.logicContent(
            request |> RequestTool.convertToRequest,
            responseObj |> ResponseTool.convertToResponse,
            code,
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

      describe("if param has no userName or password or email or nickName", () =>
        testPromise("should response status and error msg", () => {
          let request =
            RequestTool.buildFakePostRequest({
              "userName": "mickey",
              "password": "asd123123",
            });
          let responseObj = sandbox |> ResponseTool.buildFakeResponse;

          RegisterUserHandler.logicContent(
            request |> RequestTool.convertToRequest,
            responseObj |> ResponseTool.convertToResponse,
            code,
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

      describe("else, check user login success", () =>
        testPromise("should response status and success msg", () => {
          open WonderBsJson;

          let request =
            RequestTool.buildFakePostRequest({
              "userName": "mickey",
              "password": "asd123000",
              "email": "340606700@qq.com",
              "nickName": "yangHao",
            });
          let responseObj = sandbox |> ResponseTool.buildFakeResponse;

          RegisterUserHandler.logicContent(
            request |> RequestTool.convertToRequest,
            responseObj |> ResponseTool.convertToResponse,
            code,
          )
          |> Most.drain
          |> Js.Promise.then_(_ =>
               responseObj##json
               |> expect
               |> toCalledWith([|
                    ResponseUtils.buildResponseDataJson(
                      ~status=Success |> convertSelfToInt,
                      (),
                    ),
                  |])
               |> Js.Promise.resolve
             );
        })
      );
    });
  });