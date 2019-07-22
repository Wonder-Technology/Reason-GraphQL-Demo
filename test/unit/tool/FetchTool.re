open Sinon;

external convertToResponse: Js.t({..}) => Fetch.response = "%identity";

let buildFakeFetchSucessResponse = () =>
  {"json": () => Js.Promise.resolve("success fetch reponse")}
  |> convertToResponse;

let buildFakeFetchFailResponse = () =>
  {
    "json": () =>
      Js.Promise.resolve({"errors": [{"message": "error fetch response"}]}),
  }
  |> convertToResponse;

let buildFakeFetch = buildFakeFetchResponseFunc => {
  let fetch = _url => buildFakeFetchResponseFunc() |> Js.Promise.resolve;

  fetch;
};

let buildFakeFetchWithInit = buildFakeFetchResponseFunc => {
  let fetch = (_url, _data) =>
    buildFakeFetchResponseFunc() |> Js.Promise.resolve;
  fetch;
};