type userInfoRecord = {
  id: string,
  userId: string,
  nickName: string,
  profilePicture: string,
};

let getUserInfoData = () => [|
  {
    id: "1",
    userId: "1",
    nickName: "mickey1",
    profilePicture: "/image/logo.png",
  },
  {
    id: "2",
    userId: "2",
    nickName: "mickey2",
    profilePicture: "/image/logo.png",
  },
  {
    id: "3",
    userId: "3",
    nickName: "mickey3",
    profilePicture: "/image/logo.png",
  },
|];

let buildGraphQLResult = userInfoRecord => {
  "id": userInfoRecord.id,
  "user_id": userInfoRecord.userId,
  "nick_name": userInfoRecord.nickName,
  "profile_picture": userInfoRecord.profilePicture,
};

let buildGraphQLDataByUserId = (userId, dataArray) =>
  dataArray
  |> Js.Array.filter(userInfoItem =>
       ValueUtils.isValueEqual(userInfoItem.userId, userId)
     )
  |> Js.Array.map(userInfoItem => buildGraphQLResult(userInfoItem));