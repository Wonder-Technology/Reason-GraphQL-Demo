open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

open WonderBsMost;

open UserInfoDataTool;

open Js.Promise;

let _ =
  describe("test table user_info", () => {
    let sandbox = getSandboxDefaultVal();
    beforeEachPromise(() => {
      sandbox := createSandbox();

      TestInitTool.initTest() |> Most.drain;
    });

    afterEachPromise(() => {
      restoreSandbox(refJsObjToSandbox(sandbox^));

      TestInitTool.restoreMysql() |> Most.drain;
    });

    describe("test init fake database", () => {
      let date =
        MomentRe.momentNow() |> MomentRe.Moment.format("YYYY-MM-DD HH:mm:ss");

      beforeEachPromise(() =>
        UserLoginDataTool.getUserLoginDataArray(date)
        |> UserLoginTableTool.initUserLoginTable
        |> Most.flatMap(_res =>
             getUserInfoData() |> UserInfoTableTool.initUserInfoTable
           )
        |> Most.recoverWith(_error =>
             "init userLogin and userInfo table error" |> Most.just
           )
        |> Most.drain
      );

      describe("test graphql Query", () =>
        describe("test get user info data", () =>
          testPromise("test get info user by userId", () => {
            let (resultRef, errorRef) = TestTool.buildTestResultAndErrRef();
            let userInfoDataArray = getUserInfoData();
            let userInfoFirstItem =
              userInfoDataArray |> ArrayUtils.unsafeGetFirst;
            let targetUserId = userInfoFirstItem.userId;

            GraphqlTool.runGraphql(
              UserInfoGraphqlTool.getUserInfoByUserId(targetUserId),
              UserInfoValue.getUserInfoValue(),
            )
            |> TestTool.handleRunGraphQLFail
            |> TestTool.setResultOrErrorValue(resultRef, errorRef)
            |> then_(() =>
                 switch (errorRef^) {
                 | None =>
                   expect((resultRef^)##userInfo)
                   |> toEqual(
                        buildGraphQLDataByUserId(
                          targetUserId,
                          userInfoDataArray,
                        ),
                      )
                   |> resolve
                 | Some(error) => fail(error) |> resolve
                 }
               );
          })
        )
      );

      describe("test graphql Mutation", () => {
        testPromise(
          "test should add user_login, then get the userId to add user info",
          () => {
          let (resultRef, errorRef) = TestTool.buildTestResultAndErrRef();
          let userInfoDataArray = getUserInfoData();
          let newUserInfoRecordRef =
            ref(userInfoDataArray |> ArrayUtils.unsafeGetFirst);
          let newUserLoginRecord: UserLoginDataTool.userLoginRecord = {
            id: "5",
            userName: "amy",
            password: "asd1313",
            email: "340606700@qq.com",
            date,
            code: 1235 |> Crypto.getCryptoValueFromInt,
            isActive: 0,
          };

          GraphqlTool.runGraphql(
            UserLoginGraphqlTool.addLoginUser(newUserLoginRecord),
            UserLoginValue.getUserLoginValue(),
          )
          |> TestTool.handleRunGraphQLFail
          |> Most.flatMap(_result =>
               GraphqlTool.runGraphql(
                 UserLoginGraphqlTool.getLoginUserByUserName(
                   newUserLoginRecord.userName,
                 ),
                 UserLoginValue.getUserLoginValue(),
               )
               |> TestTool.handleRunGraphQLFail
             )
          |> Most.flatMap(loginUserData => {
               let newUserInfoRecord = {
                 id: "5",
                 userId:
                   loginUserData##loginUser
                   |> ArrayUtils.unsafeGetFirst
                   |> (user => user##id),
                 nickName: "mickey",
                 profilePicture: "/image/mickey.png",
               };
               newUserInfoRecordRef := newUserInfoRecord;

               GraphqlTool.runGraphql(
                 UserInfoGraphqlTool.addUserInfo(newUserInfoRecord),
                 UserInfoValue.getUserInfoValue(),
               )
               |> TestTool.handleRunGraphQLFail;
             })
          |> Most.flatMap(_ =>
               GraphqlTool.runGraphql(
                 UserInfoGraphqlTool.getUserInfoByUserId(
                   newUserInfoRecordRef^.userId,
                 ),
                 UserInfoValue.getUserInfoValue(),
               )
               |> TestTool.handleRunGraphQLFail
             )
          |> TestTool.setResultOrErrorValue(resultRef, errorRef)
          |> then_(() =>
               switch (errorRef^) {
               | None =>
                 expect((resultRef^)##userInfo)
                 |> toEqual([|buildGraphQLResult(newUserInfoRecordRef^)|])
                 |> resolve

               | Some(error) => fail(error) |> resolve
               }
             );
        });

        testPromise("test update user info's nick_name", () => {
          let (resultRef, errorRef) = TestTool.buildTestResultAndErrRef();
          let userInfoDataArray = getUserInfoData();
          let userInfoFirstItem =
            userInfoDataArray |> ArrayUtils.unsafeGetFirst;
          let targetUserId = userInfoFirstItem.userId;
          let targetNickName = "mickey";

          GraphqlTool.runGraphql(
            UserInfoGraphqlTool.updateUserInfoNickName(
              targetUserId,
              targetNickName,
            ),
            UserInfoValue.getUserInfoValue(),
          )
          |> TestTool.handleRunGraphQLFail
          |> Most.flatMap(_result =>
               GraphqlTool.runGraphql(
                 UserInfoGraphqlTool.getUserInfoByUserId(targetUserId),
                 UserInfoValue.getUserInfoValue(),
               )
               |> TestTool.handleRunGraphQLFail
             )
          |> TestTool.setResultOrErrorValue(resultRef, errorRef)
          |> then_(() =>
               switch (errorRef^) {
               | None =>
                 let userInfoObj =
                   (resultRef^)##userInfo |> ArrayUtils.unsafeGetFirst;

                 userInfoObj##nick_name |> expect == targetNickName |> resolve;

               | Some(error) => fail(error) |> resolve
               }
             );
        });
        testPromise("test update user info's profile_picture ", () => {
          let (resultRef, errorRef) = TestTool.buildTestResultAndErrRef();
          let userInfoDataArray = getUserInfoData();
          let userInfoFirstItem =
            userInfoDataArray |> ArrayUtils.unsafeGetFirst;
          let targetUserId = userInfoFirstItem.userId;
          let targetPicture = "/image/mickey.png";

          GraphqlTool.runGraphql(
            UserInfoGraphqlTool.updateUserInfoProfilePicture(
              targetUserId,
              targetPicture,
            ),
            UserInfoValue.getUserInfoValue(),
          )
          |> TestTool.handleRunGraphQLFail
          |> Most.flatMap(_ =>
               GraphqlTool.runGraphql(
                 UserInfoGraphqlTool.getUserInfoByUserId(targetUserId),
                 UserInfoValue.getUserInfoValue(),
               )
               |> TestTool.handleRunGraphQLFail
             )
          |> TestTool.setResultOrErrorValue(resultRef, errorRef)
          |> then_(() =>
               switch (errorRef^) {
               | None =>
                 let userInfoObj =
                   (resultRef^)##userInfo |> ArrayUtils.unsafeGetFirst;

                 userInfoObj##profile_picture
                 |> expect == targetPicture
                 |> resolve;

               | Some(error) => fail(error) |> resolve
               }
             );
        });
      });
    });
  });