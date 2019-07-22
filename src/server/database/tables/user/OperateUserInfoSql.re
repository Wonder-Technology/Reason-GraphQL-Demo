let updateProfilePictureSql = "UPDATE user_info SET profile_picture=:profilePicture WHERE user_id=:userId;";

let updateNickNameSql = "UPDATE user_info SET nick_name=:nickName WHERE user_id=:userId;";

let addSql = "INSERT INTO
user_info(user_id, nick_name, profile_picture) VALUES(:userId, :nickName, :profilePicture);";

let deleteSql = "delete from user_info WHERE id=:id;";


let selectByParamSql = "select * from user_info where user_id=:userId ;";