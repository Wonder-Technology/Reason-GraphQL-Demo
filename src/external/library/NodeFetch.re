open Fetch;

[@bs.module "node-fetch"]
external fetchWithInit:
  (string, Fetch.requestInit) => Js.Promise.t(Fetch.response) =
  "default";

[@bs.module "node-fetch"]
external fetch: string => Js.Promise.t(Fetch.response) = "default";