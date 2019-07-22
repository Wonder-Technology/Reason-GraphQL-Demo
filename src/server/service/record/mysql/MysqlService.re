open MysqlType;

let getMysqlConfig = mysqlRecord => mysqlRecord.mysqlConfig;

let setMysqlConfig = (mysqlConfig, mysqlRecord) => {
  ...mysqlRecord,
  mysqlConfig,
};

let getMysqlPool = mysqlRecord => mysqlRecord.mysqlPool;

let setMysqlPool = (mysqlPool, mysqlRecord) => {...mysqlRecord, mysqlPool};