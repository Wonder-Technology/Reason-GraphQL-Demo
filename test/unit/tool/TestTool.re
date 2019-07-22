open WonderBsMost;

external convertReasonObjToJsObj: {.} => Js.t({..}) = "%identity";

let getTestFileChunkStoreDir = () =>
  Node.Process.cwd() ++ "/test/res/fileChunk/";

let getTestImageStoreDir = () => Node.Process.cwd() ++ "/test/res/image/";

let getTestImageAccessDir = () => "/image/";

let buildTestResultAndErrRef = () => (
  ref({} |> convertReasonObjToJsObj),
  ref(None),
);

let getEmptyJsObj = () => {} |> convertReasonObjToJsObj;

let handleRunGraphQLFail = stream =>
  stream
  |> Most.flatMap(response => {
       let errors = response##errors;

       errors |> ValueUtils.isValueValid ?
         errors
         |> ResponseUtils.GraphQLResponse.getErrorMessage
         |> ResponseTool.throwError :
         response##data |> Most.just;
     });

let setResultOrErrorValue = (resultRef, errorRef, stream) =>
  stream
  |> Most.recoverWith(error => {
       errorRef := Some(error |> ResponseTool.convertJsExnToString);

       getEmptyJsObj() |> Most.just;
     })
  |> Most.forEach(response => resultRef := response);