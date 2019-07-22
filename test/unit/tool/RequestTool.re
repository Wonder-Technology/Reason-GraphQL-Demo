external convertToRequest: Js.t({..}) => Express.Request.t = "%identity";

let buildFakeGetRequest = query => {
  let response = {"query": query};

  response;
};

let buildFakePostRequest = bodyJson => {
  let response = {"body": bodyJson};

  response;
};