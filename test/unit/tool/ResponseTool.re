open Sinon;

external convertToResponse: Js.t({..}) => Express.Response.t = "%identity";

let buildFakeResponse = sandbox => {
  let response = {
    "json": createEmptyStubWithJsObjSandbox(sandbox),
    "sendFile": createEmptyStubWithJsObjSandbox(sandbox),
    "send": createEmptyStubWithJsObjSandbox(sandbox),
    "sendStatus": createEmptyStubWithJsObjSandbox(sandbox),
    "status": createEmptyStubWithJsObjSandbox(sandbox),
    "redirect": createEmptyStubWithJsObjSandbox(sandbox),
    "set": createEmptyStubWithJsObjSandbox(sandbox),
    "links": createEmptyStubWithJsObjSandbox(sandbox),
  };

  response;
};

external convertJsExnToString: Js.Exn.t => string = "%identity";

external convertStrToJsExn: string => Js.Exn.t = "%identity";

let throwError = (error: string) =>
  WonderBsMost.Most.throwError(error |> convertStrToJsExn) |> Obj.magic;