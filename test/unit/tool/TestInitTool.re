open WonderBsMost;

let initTest = () =>
  MysqlInitTool.dropDataBase()
  |> Most.fromPromise
  |> Most.flatMap(_res => MysqlInitTool.createDataBase() |> Most.fromPromise)
  |> Most.flatMap(_res => MysqlInitTool.useDataBase() |> Most.fromPromise)
  |> Most.tap(_res => StateInitTool.initState());

let restoreMysql = () => MysqlInitTool.dropDataBase() |> Most.fromPromise;