open WonderBsGraphql;

open WonderBsMost;

let _executeGraphQLByOperate = operate =>
  GraphQL.run(
    AppGraphQL.getSchema(),
    operate,
    ~rootValue=UserInfoValue.getUserInfoValue(),
    (),
  )
  |> Most.fromPromise;

let getUserInfoDataByUserId = userId =>
  UserInfoSchemaOperate.getUserInfoDataByUserId(userId)
  |> _executeGraphQLByOperate;

let updateProfilePictureMutation = (userId, profilePicture) =>
  UserInfoSchemaOperate.updateProfilePicture(userId, profilePicture)
  |> _executeGraphQLByOperate;