open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

open WonderBsMost;

open UserLoginDataTool;

open Js.Promise;

let _ =
  describe("test table user_login", () => {
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

      describe("test graphql Query", () =>
        testPromise("test get all login user data", () => {
          let userLoginDataArray = getUserLoginDataArray(date);
          let (resultRef, errorRef) = TestTool.buildTestResultAndErrRef();

          GraphqlTool.runGraphql(
            UserLoginGraphqlTool.getAllLoginUser(),
            UserLoginValue.getUserLoginValue(),
          )
          |> TestTool.handleRunGraphQLFail
          |> TestTool.setResultOrErrorValue(resultRef, errorRef)
          |> then_(() =>
               switch (errorRef^) {
               | None =>
                 expect((resultRef^)##loginUsers)
                 |> toEqual(buildGraphQLAllData(userLoginDataArray))
                 |> resolve
               | Some(error) => fail(error) |> resolve
               }
             );
        })
      );
      describe("test get login user data", () => {
        testPromise("test get login user by userName", () => {
          let (resultRef, errorRef) = TestTool.buildTestResultAndErrRef();
          let userLoginDataArray = getUserLoginDataArray(date);
          let userLoginFirstItem =
            userLoginDataArray |> ArrayUtils.unsafeGetFirst;
          let targetUserName = userLoginFirstItem.userName;

          GraphqlTool.runGraphql(
            UserLoginGraphqlTool.getLoginUserByUserName(targetUserName),
            UserLoginValue.getUserLoginValue(),
          )
          |> TestTool.handleRunGraphQLFail
          |> TestTool.setResultOrErrorValue(resultRef, errorRef)
          |> then_(() =>
               switch (errorRef^) {
               | None =>
                 expect((resultRef^)##loginUser)
                 |> toEqual(
                      buildGraphQLDataByUserName(
                        targetUserName,
                        userLoginDataArray,
                      ),
                    )
                 |> resolve
               | Some(error) => fail(error) |> resolve
               }
             );
        });
        testPromise("test get login user by email", () => {
          let (resultRef, errorRef) = TestTool.buildTestResultAndErrRef();
          let userLoginDataArray = getUserLoginDataArray(date);
          let userLoginFirstItem =
            userLoginDataArray |> ArrayUtils.unsafeGetFirst;
          let targetEmail = userLoginFirstItem.email;

          GraphqlTool.runGraphql(
            UserLoginGraphqlTool.getLoginUserByEmail(targetEmail),
            UserLoginValue.getUserLoginValue(),
          )
          |> TestTool.handleRunGraphQLFail
          |> TestTool.setResultOrErrorValue(resultRef, errorRef)
          |> then_(() =>
               switch (errorRef^) {
               | None =>
                 expect((resultRef^)##loginUser)
                 |> toEqual(
                      buildGraphQLDataByEmail(
                        targetEmail,
                        userLoginDataArray,
                      ),
                    )
                 |> resolve
               | Some(error) => fail(error) |> resolve
               }
             );
        });
      });
      describe("test graphql Mutation", () => {
        testPromise("test add login user", () => {
          let (resultRef, errorRef) = TestTool.buildTestResultAndErrRef();
          let userLoginDataArray = getUserLoginDataArray(date);
          let newUserLoginRecord = {
            id: "5",
            userName: "amy",
            password: "asd1313",
            email: "340606700@qq.com",
            date,
            code: 5461 |> Crypto.getCryptoValueFromInt,
            isActive: 0,
          };

          GraphqlTool.runGraphql(
            UserLoginGraphqlTool.addLoginUser(newUserLoginRecord),
            UserLoginValue.getUserLoginValue(),
          )
          |> TestTool.handleRunGraphQLFail
          |> Most.flatMap(_result =>
               GraphqlTool.runGraphql(
                 UserLoginGraphqlTool.getAllLoginUser(),
                 UserLoginValue.getUserLoginValue(),
               )
               |> TestTool.handleRunGraphQLFail
             )
          |> TestTool.setResultOrErrorValue(resultRef, errorRef)
          |> then_(() =>
               switch (errorRef^) {
               | None =>
                 let newUserLoginData =
                   buildGraphQLResult(newUserLoginRecord);

                 expect((resultRef^)##loginUsers)
                 |> toEqual(
                      buildGraphQLAllData(userLoginDataArray)
                      |> ArrayUtils.push(newUserLoginData),
                    )
                 |> resolve;
               | Some(error) => fail(error) |> resolve
               }
             );
        });

        testPromise("test update login user's is_active", () => {
          let (resultRef, errorRef) = TestTool.buildTestResultAndErrRef();
          let userLoginDataArray = getUserLoginDataArray(date);
          let userLoginFirstItem =
            userLoginDataArray |> ArrayUtils.unsafeGetFirst;
          let targetUserName = userLoginFirstItem.userName;
          let targetIsActive = 1;

          GraphqlTool.runGraphql(
            UserLoginGraphqlTool.updateLoginUserIsActive(
              targetUserName,
              targetIsActive,
            ),
            UserLoginValue.getUserLoginValue(),
          )
          |> TestTool.handleRunGraphQLFail
          |> Most.flatMap(_result =>
               GraphqlTool.runGraphql(
                 UserLoginGraphqlTool.getLoginUserByUserName(targetUserName),
                 UserLoginValue.getUserLoginValue(),
               )
               |> TestTool.handleRunGraphQLFail
             )
          |> TestTool.setResultOrErrorValue(resultRef, errorRef)
          |> then_(() =>
               switch (errorRef^) {
               | None =>
                 let loginUserObj =
                   (resultRef^)##loginUser |> ArrayUtils.unsafeGetFirst;

                 loginUserObj##is_active |> expect == targetIsActive |> resolve;

               | Some(error) => fail(error) |> resolve
               }
             );
        });
        testPromise("test update login user's code", () => {
          let (resultRef, errorRef) = TestTool.buildTestResultAndErrRef();
          let userLoginDataArray = getUserLoginDataArray(date);
          let userLoginFirstItem =
            userLoginDataArray |> ArrayUtils.unsafeGetFirst;
          let targetUserName = userLoginFirstItem.userName;
          let targetCode =
            DomHelper.getRandomNumber() |> Crypto.getCryptoValueFromInt;

          GraphqlTool.runGraphql(
            UserLoginGraphqlTool.updateLoginUserCode(
              targetUserName,
              targetCode,
            ),
            UserLoginValue.getUserLoginValue(),
          )
          |> TestTool.handleRunGraphQLFail
          |> Most.flatMap(_result =>
               GraphqlTool.runGraphql(
                 UserLoginGraphqlTool.getLoginUserByUserName(targetUserName),
                 UserLoginValue.getUserLoginValue(),
               )
               |> TestTool.handleRunGraphQLFail
             )
          |> TestTool.setResultOrErrorValue(resultRef, errorRef)
          |> then_(() =>
               switch (errorRef^) {
               | None =>
                 let loginUserObj =
                   (resultRef^)##loginUser |> ArrayUtils.unsafeGetFirst;

                 loginUserObj##code |> expect == targetCode |> resolve;

               | Some(error) => fail(error) |> resolve
               }
             );
        });
        testPromise("test update login user's password ", () => {
          let (resultRef, errorRef) = TestTool.buildTestResultAndErrRef();
          let userLoginDataArray = getUserLoginDataArray(date);
          let userLoginFirstItem =
            userLoginDataArray |> ArrayUtils.unsafeGetFirst;
          let targetUserName = userLoginFirstItem.userName;
          let targetPassword = "xiaohao111";

          GraphqlTool.runGraphql(
            UserLoginGraphqlTool.updateLoginUserPassword(
              targetUserName,
              targetPassword,
            ),
            UserLoginValue.getUserLoginValue(),
          )
          |> TestTool.handleRunGraphQLFail
          |> Most.flatMap(_result =>
               GraphqlTool.runGraphql(
                 UserLoginGraphqlTool.getLoginUserByUserName(targetUserName),
                 UserLoginValue.getUserLoginValue(),
               )
               |> TestTool.handleRunGraphQLFail
             )
          |> TestTool.setResultOrErrorValue(resultRef, errorRef)
          |> then_(() =>
               switch (errorRef^) {
               | None =>
                 let loginUserObj =
                   (resultRef^)##loginUser |> ArrayUtils.unsafeGetFirst;

                 loginUserObj##password |> expect == targetPassword |> resolve;

               | Some(error) => fail(error) |> resolve
               }
             );
        });
      });
    });
  });