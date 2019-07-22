open UserLoginDataTool;

let updateLoginUserIsActive = UserLoginSchemaOperate.updateIsActiveMutation;
let updateLoginUserPassword = (userName, password) => {j|
    mutation{
        updateLoginUserPassword(userName:"$userName", password:"$password")
    }
|j};

let updateLoginUserCode = UserLoginSchemaOperate.updateCodeMutation;

let addLoginUser = ({userName, password, email, date, code, isActive}) => {
  let password = password |> Crypto.getCryptoValue;

  {j|
    mutation{
        addLoginUser(userName:"$userName",password:"$password",email:"$email",createDate:"$date",isActive:$isActive,code:"$code")
    }
|j};
};

let getAllLoginUser = () => {|
    {
        loginUsers{
            id
            user_name
            password
            email
            code
            create_date
            is_active
        }
    }
|};

let getLoginUserByUserName = UserLoginSchemaOperate.getUserLoginDataByUserName;

let getLoginUserByEmail = email => {j|
    {
        loginUser(email:"$email"){
            id
            user_name
            password
            email
            code
            create_date
            is_active
        }
    }
|j};