let _getSchemaQueryHeaderArray = () => [|
  UserLoginSchemaData.getQueryHeader(),
  UserInfoSchemaData.getQueryHeader(),
|];

let _getSchemaQueryItemArray = () => [|
  UserLoginSchemaData.getQueryItem(),
  UserInfoSchemaData.getQueryItem(),
|];

let _getSchemaMutationArray = () => [|
  UserLoginSchemaData.getMutation(),
  UserInfoSchemaData.getMutation(),
|];

let _buildSchemeTypeStr = (type_, content) => {j|
  type $type_{
    $content
  }\n
|j};

let _buildSchemaString = targetSchema =>
  (
    _getSchemaQueryItemArray()
    |> Js.Array.reduce((target, item) => target ++ item, targetSchema)
  )
  ++ (
    _getSchemaQueryHeaderArray()
    |> Js.Array.reduce((target, item) => target ++ item, "")
    |> _buildSchemeTypeStr("Query")
  )
  ++ (
    _getSchemaMutationArray()
    |> Js.Array.reduce((target, item) => target ++ item, "")
    |> _buildSchemeTypeStr("Mutation")
  );

let getSchema = () =>
  WonderBsGraphql.GraphQL.Utilities.buildSchema(_buildSchemaString(""));

let _getRootValueArr = () => [|
  UserLoginValue.getUserLoginValue(),
  UserInfoValue.getUserInfoValue(),
|];

let getRootValue = () =>
  _getRootValueArr()
  |> Js.Array.reduce(
       (targetObj, valueObj) => Js.Obj.assign(targetObj, valueObj),
       {} |> Obj.magic,
     );