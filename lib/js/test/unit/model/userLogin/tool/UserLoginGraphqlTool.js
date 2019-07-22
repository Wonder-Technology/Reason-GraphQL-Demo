'use strict';

var Crypto$ReasonGraphqlFullstack = require("../../../../../src/external/Crypto.js");
var UserLoginSchemaOperate$ReasonGraphqlFullstack = require("../../../../../src/server/database/graphQL/user_login/UserLoginSchemaOperate.js");

function updateLoginUserPassword(userName, password) {
  return "\n    mutation{\n        updateLoginUserPassword(userName:\"" + (String(userName) + ("\", password:\"" + (String(password) + "\")\n    }\n")));
}

function addLoginUser(param) {
  var password = Crypto$ReasonGraphqlFullstack.getCryptoValue(param[/* password */2]);
  return "\n    mutation{\n        addLoginUser(userName:\"" + (String(param[/* userName */1]) + ("\",password:\"" + (String(password) + ("\",email:\"" + (String(param[/* email */3]) + ("\",createDate:\"" + (String(param[/* date */4]) + ("\",isActive:" + (String(param[/* isActive */6]) + (",code:\"" + (String(param[/* code */5]) + "\")\n    }\n")))))))))));
}

function getAllLoginUser(param) {
  return "\n    {\n        loginUsers{\n            id\n            user_name\n            password\n            email\n            code\n            create_date\n            is_active\n        }\n    }\n";
}

function getLoginUserByEmail(email) {
  return "\n    {\n        loginUser(email:\"" + (String(email) + "\"){\n            id\n            user_name\n            password\n            email\n            code\n            create_date\n            is_active\n        }\n    }\n");
}

var updateLoginUserIsActive = UserLoginSchemaOperate$ReasonGraphqlFullstack.updateIsActiveMutation;

var updateLoginUserCode = UserLoginSchemaOperate$ReasonGraphqlFullstack.updateCodeMutation;

var getLoginUserByUserName = UserLoginSchemaOperate$ReasonGraphqlFullstack.getUserLoginDataByUserName;

exports.updateLoginUserIsActive = updateLoginUserIsActive;
exports.updateLoginUserPassword = updateLoginUserPassword;
exports.updateLoginUserCode = updateLoginUserCode;
exports.addLoginUser = addLoginUser;
exports.getAllLoginUser = getAllLoginUser;
exports.getLoginUserByUserName = getLoginUserByUserName;
exports.getLoginUserByEmail = getLoginUserByEmail;
/* Crypto-ReasonGraphqlFullstack Not a pure module */
