open WonderBsJson;

open ServerConfigParseType;

external convertJsExnToMysqlExn: Js.Exn.t => MySql2.Exn.t = "%identity";

let createMysqlConnect = ({host, user, password, database, port}) =>
  MySql2.Connection.connect(~host, ~user, ~password, ~database, ~port, ());

let createPool = ({host, user, password, database, port}) =>
  MySql2.Pool.make(
    ~connectionLimit=10,
    ~queueLimit=0,
    ~waitForConnections=true,
    ~host,
    ~port,
    ~user,
    ~password,
    ~database,
    (),
  );