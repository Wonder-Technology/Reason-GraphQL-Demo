open JustgageReasonCookie;

module GetLoginUserInfos = [%graphql
  {|
    query getUserInfos($id:ID!){
      loginUser(id:$id){
        id
        user_name
        email
        create_date
        is_active
      }
      userInfo(userId:$id){
        profile_picture
        nick_name
      }
   }
|}
];

module GetUserQuery = ReasonApollo.CreateQuery(GetLoginUserInfos);

let component = ReasonReact.statelessComponent("UserHomePage");

let render = (userData, _self) => {
  let userDataObj = JsonType.convertToJsObj(userData);

  let getLoginUserInfoQuery =
    GetLoginUserInfos.make(~id=userDataObj##userId, ());
  <GetUserQuery variables=getLoginUserInfoQuery##variables>
    ...{
         ({result}) =>
           <div>
             <h1> {"User: " |> DomHelper.textEl} </h1>
             {
               switch (result) {
               | Data(response) =>
                 switch (
                   response##loginUser |> ArrayUtils.getFirst,
                   response##userInfo |> ArrayUtils.getFirst,
                 ) {
                 | (Some(user), Some(userInfo)) =>
                   <div className="">
                     <div className="">
                       {DomHelper.textEl("profile picture")}
                     </div>
                     <img
                       src=userInfo##profile_picture
                       width="100"
                       height="100"
                     />
                     <div className="">
                       {DomHelper.textEl(user##user_name)}
                     </div>
                     <button
                       className=""
                       onClick=(_e => DomHelper.locationHref("/homePage"))>
                       {DomHelper.textEl("show user info")}
                     </button>
                   </div>

                 | (None, None)
                 | _ =>
                   JustgageReasonCookie.Cookie.remove("userData");

                   DomHelper.locationHref("/");

                   ReasonReact.null;
                 }

               | Loading => "Loading" |> DomHelper.textEl
               | _ => "Something Went Wrong" |> DomHelper.textEl
               }
             }
           </div>
       }
  </GetUserQuery>;
};

let make = (~userData, _children) => {
  ...component,
  render: _self => render(userData, _self),
};