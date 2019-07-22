open WonderBsGraphql;

open WonderBsMost;

let _executeGraphQLByOperate = operate =>
  GraphQL.run(
    AppGraphQL.getSchema(),
    operate,
    ~rootValue=UserLoginValue.getUserLoginValue(),
    (),
  )
  |> Most.fromPromise;

let getUserLoginDataByUserName = userName =>
  UserLoginSchemaOperate.getUserLoginDataByUserName(userName)
  |> _executeGraphQLByOperate;

let updateIsActiveMutation = (userName, isActive) =>
  UserLoginSchemaOperate.updateIsActiveMutation(userName, isActive)
  |> _executeGraphQLByOperate;

let updateCodeMutation = (userName, code) =>
  UserLoginSchemaOperate.updateCodeMutation(userName, code)
  |> _executeGraphQLByOperate;