external convertSelectToJsObj: MySql2.Select.t => Js.t({..}) = "%identity";

external convertMutationToJsObj: MySql2.Mutation.t => Js.t({..}) =
  "%identity";