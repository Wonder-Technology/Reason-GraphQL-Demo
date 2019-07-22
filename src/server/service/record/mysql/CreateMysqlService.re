open MysqlType;

open ServerConfigParseType;

let createMysqlRecord = mysqlConfig => {
  mysqlConfig,
  mysqlPool: MysqlCommon.createPool(mysqlConfig),
};