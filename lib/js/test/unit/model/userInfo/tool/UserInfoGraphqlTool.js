'use strict';


function updateUserInfoProfilePicture(userId, picture) {
  return "\n    mutation{\n        updateUserInfoProfilePicture(userId:\"" + (String(userId) + ("\", profilePicture:\"" + (String(picture) + "\")\n    }\n")));
}

function updateUserInfoNickName(userId, nickName) {
  return "\n    mutation{\n        updateUserInfoNickName(userId:\"" + (String(userId) + ("\", nickName:\"" + (String(nickName) + "\")\n    }\n")));
}

function addUserInfo(param) {
  return "\n    mutation{\n        addUserInfo(userId:\"" + (String(param[/* userId */1]) + ("\", nickName:\"" + (String(param[/* nickName */2]) + ("\", profilePicture: \"" + (String(param[/* profilePicture */3]) + "\")\n    }\n")))));
}

function getUserInfoByUserId(userId) {
  return "\n    {\n        userInfo(userId:\"" + (String(userId) + "\"){\n            id\n            user_id\n            nick_name\n            profile_picture\n        }\n    }\n");
}

exports.updateUserInfoProfilePicture = updateUserInfoProfilePicture;
exports.updateUserInfoNickName = updateUserInfoNickName;
exports.addUserInfo = addUserInfo;
exports.getUserInfoByUserId = getUserInfoByUserId;
/* No side effect */
