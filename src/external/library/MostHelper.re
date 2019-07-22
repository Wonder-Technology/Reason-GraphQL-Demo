open WonderBsMost;

open BcErrorType;

open Most;

let throwErrorWithType = (error: bcError) =>
  throwError(error |> convertBcErrToJsExn) |> Obj.magic;

let callFunc = func => just(func) |> map(func => func());

let ignore = stream => stream |> Most.map(_ => ());

let callStreamFunc = func => just(func) |> flatMap(func => func());