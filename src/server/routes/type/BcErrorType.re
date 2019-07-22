type bcError = (int, string);

external convertBcErrToJsExn: bcError => Js.Exn.t = "%identity";

external convertJsExnToBcErr: Js.Exn.t => bcError = "%identity";

external convertJsExnToArrayStr: Js.Exn.t => array(string) = "%identity";

external convertJsExnToStr: Js.Exn.t => string = "%identity";

external convertStrToJsExn: string => Js.Exn.t = "%identity";

external convertJsExnToJsObj: Js.Exn.t => Js.t({..}) = "%identity";