let getUserInfoDataByUserId = userId => {j|
  {
    userInfo(userId:$userId){
        id
        profile_picture
        nick_name
    }
  }
|j};

let updateProfilePicture = (userId, profilePicture) => {j|
    mutation {
        updateUserInfoProfilePicture(userId: $userId, profilePicture : "$profilePicture")
      }
  |j};