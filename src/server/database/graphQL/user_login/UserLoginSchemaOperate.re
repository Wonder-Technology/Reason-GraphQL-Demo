let getUserLoginDataByUserName = ( userName:string ) => {j|
  {
    loginUser(userName:"$userName"){
      id
      user_name
      password
      email
      create_date
      code
      is_active
    }
  }
|j};

let updateIsActiveMutation = (userName:string, isActive:int) => {j|
    mutation {
        updateLoginUserIsActive(userName:"$userName", isActive: $isActive )
    }
|j};

let updateCodeMutation = (userName:string, code:string) => {j|
    mutation {
        updateLoginUserCode(userName:"$userName", code: "$code" )
    }
|j};