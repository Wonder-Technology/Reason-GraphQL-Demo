let getQueryItem = () => {|
    scalar Date

    type LoginUser{
      id: ID!
      user_name: String
      password: String
      email: String
      create_date: Date
      code: String
      is_active: Int
    }
|};

let getQueryHeader = () => {|
    loginUsers: [LoginUser]!

    loginUser(id:ID = "",userName: String = "", email:String = "" ): [LoginUser]!
|};

let getMutation = () => {|
    addLoginUser(userName:String!,  password:String!, email:String!, createDate: Date!, code:String!, isActive:Int! ): String

    updateLoginUserIsActive(userName:String!, isActive:Int! ): String

    updateLoginUserPassword(userName:String!, password:String! ): String

    updateLoginUserCode(userName:String!, code:String! ): String
|};