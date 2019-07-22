let updateIsActiveSql = "UPDATE user_login SET is_active=:isActive WHERE user_name=:userName;";

let updatePasswordSql = "UPDATE user_login SET password=:password WHERE user_name=:userName;";

let updateCodeSql = "UPDATE user_login SET code=:code WHERE user_name=:userName;";

let addSql = "INSERT INTO
user_login(user_name, password, email, create_date, code, is_active) VALUES(:userName,:password, :email, :createDate, :code, :isActive);";

let deleteSql = "delete from user_login WHERE id=:id;";

let selectAllSql = "select date_format(create_date,'%Y-%m-%d %H:%i:%S') as create_date, id, user_name, password, email, code, is_active from user_login;";

let selectByParamSql = "select date_format(create_date,'%Y-%m-%d %H:%i:%S') as create_date, id, user_name, password, email, code, is_active from user_login where user_name=:userName or email=:email or id=:id;";