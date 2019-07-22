let getServerConfig = () => {|
    {
        "mysql_product_config": {
            "host": "127.0.0.1",
            "user": "root",
            "password": "asd",
            "database": "graphql",
            "port": 3306
        },
        "mysql_test_config": {
            "host": "127.0.0.1",
            "user": "root",
            "password": "asd",
            "database": "graphql_test",
            "port": 3306
        }
    }
|};

let getIsDebug = () => true;

let getImageStoreDir = () =>
  SystemConfig.isProd() ?
    "/mnt/image/profile/" : Node.Process.cwd() ++ "/public/image/";

let getImageAccessDir = () =>
  SystemConfig.isProd() ? "/image/profile/" : "/image/";

let getFileChunkStoreDir = () =>
  SystemConfig.isProd() ?
    "/mnt/fileChunk/" : Node.Process.cwd() ++ "/public/fileChunk/";

let getUserRepoDir = () =>
  SystemConfig.isProd() ?
    "/mnt/users/" : Node.Process.cwd() ++ "/public/users/";