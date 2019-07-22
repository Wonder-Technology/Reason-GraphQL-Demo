let getQueryItem = () => {|
    type UserInfo{
      id: ID!
      user_id: ID!
      nick_name: String
      profile_picture:String
    }
|};

let getQueryHeader = () => {|
    userInfo(userId: ID!): [UserInfo]!
|};

let getMutation = () => {|
    addUserInfo(userId:ID!, nickName:String!, profilePicture:String!): String

    updateUserInfoProfilePicture(userId:ID!, profilePicture:String! ): String

    updateUserInfoNickName(userId:ID!, nickName:String! ): String
|};