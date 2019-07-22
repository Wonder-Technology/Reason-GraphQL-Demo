open ServerConfigParseType;

let convertDataToRecord = jsonData : serverConfig =>
  WonderBsJson.Json.(
    Decode.(
      jsonData
      |> Js.Json.parseExn
      |> (
        json => {
          mysqlProductConfig:
            json
            |> field("mysql_product_config", json =>
                 {
                   host: json |> field("host", string),
                   user: json |> field("user", string),
                   password: json |> field("password", string),
                   database: json |> field("database", string),
                   port: json |> field("port", int),
                 }
               ),
          mysqlTestConfig:
            json
            |> field("mysql_test_config", json =>
                 {
                   host: json |> field("host", string),
                   user: json |> field("user", string),
                   password: json |> field("password", string),
                   database: json |> field("database", string),
                   port: json |> field("port", int),
                 }
               ),
        }
      )
    )
  );
let getServerConfig = () =>
  ServerConfig.getServerConfig() |> convertDataToRecord;