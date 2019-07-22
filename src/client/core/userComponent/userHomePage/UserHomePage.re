open JustgageReasonCookie;

open WonderBsMost;

open WonderBsJson;

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

module Method = {};

let component = ReasonReact.statelessComponent("UserHomePage");

let render = _self =>
  switch (Cookie.getAsJson("userData")) {
  | None =>
    DomHelper.locationHref("/");

    ReasonReact.null;
  | Some(userData) =>
    let userDataObj = JsonType.convertToJsObj(userData);

    let getLoginUserInfoQuery =
      GetLoginUserInfos.make(~id=userDataObj##userId, ());

    <GetUserQuery variables=getLoginUserInfoQuery##variables>
      ...(
           ({result}) =>
             <div>
               <h1> {"User Info: " |> DomHelper.textEl} </h1>
               {
                 switch (result) {
                 | Data(response) =>
                   switch (
                     response##loginUser |> ArrayUtils.getFirst,
                     response##userInfo |> ArrayUtils.getFirst,
                   ) {
                   | (Some(user), Some(userInfo)) =>
                     <div className="">
                       <table>
                         <thead>
                           <tr>
                             <th> {DomHelper.textEl("id")} </th>
                             <th> {DomHelper.textEl("userName")} </th>
                             <th> {DomHelper.textEl("nickname")} </th>
                             <th> {DomHelper.textEl("email")} </th>
                             <th> {DomHelper.textEl("create_date")} </th>
                             <th> {DomHelper.textEl("is_active")} </th>
                           </tr>
                         </thead>
                         <tbody>
                           <tr>
                             <td> {user##id |> DomHelper.textEl} </td>
                             <td> {user##user_name |> DomHelper.textEl} </td>
                             <td>
                               {userInfo##nick_name |> DomHelper.textEl}
                             </td>
                             <td> {user##email |> DomHelper.textEl} </td>
                             <td>
                               {
                                 user##create_date
                                 |> Js.Json.stringify
                                 |> DomHelper.textEl
                               }
                             </td>
                             <td>
                               {
                                 user##is_active
                                 |> string_of_int
                                 |> DomHelper.textEl
                               }
                             </td>
                           </tr>
                         </tbody>
                       </table>
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
         )
    </GetUserQuery>;
  };

let make = _children => {...component, render};