open UserInfoDataTool;
let updateUserInfoProfilePicture = (userId, picture) => {j|
    mutation{
        updateUserInfoProfilePicture(userId:"$userId", profilePicture:"$picture")
    }
|j};

let updateUserInfoNickName = (userId, nickName) => {j|
    mutation{
        updateUserInfoNickName(userId:"$userId", nickName:"$nickName")
    }
|j};

let addUserInfo = ({userId, nickName, profilePicture}) => {j|
    mutation{
        addUserInfo(userId:"$userId", nickName:"$nickName", profilePicture: "$profilePicture")
    }
|j};

let getUserInfoByUserId = userId => {j|
    {
        userInfo(userId:"$userId"){
            id
            user_id
            nick_name
            profile_picture
        }
    }
|j};