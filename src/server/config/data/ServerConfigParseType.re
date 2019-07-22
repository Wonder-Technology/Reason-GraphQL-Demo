type mysqlConfig = {
  host: string,
  user: string,
  password: string,
  database: string,
  port: int,
};

type serverConfig = {
  mysqlProductConfig: mysqlConfig,
  mysqlTestConfig: mysqlConfig,
};