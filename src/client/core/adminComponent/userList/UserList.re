module GetAllLoginUser = [%graphql
  {|
    query getAllLoginUser {
      loginUsers{
        id
        user_name
        email
        create_date
        is_active
      }
   }
|}
];

module GetAllUserQuery = ReasonApollo.CreateQuery(GetAllLoginUser);

let component = ReasonReact.statelessComponent("UserList");

let make = _children => {
  ...component,
  render: _self =>
    <GetAllUserQuery>
      ...{
           ({result}) =>
             <div>
               <h1> {"Persons: " |> DomHelper.textEl} </h1>
               {
                 switch (result) {
                 | Error(e) => "Something Went Wrong" |> DomHelper.textEl
                 | Loading => "Loading" |> DomHelper.textEl
                 | Data(response) =>
                   <table>
                     <thead>
                       <tr>
                         <th> {DomHelper.textEl("id")} </th>
                         <th> {DomHelper.textEl("userName")} </th>
                         <th> {DomHelper.textEl("email")} </th>
                         <th> {DomHelper.textEl("create_date")} </th>
                         <th> {DomHelper.textEl("is_active")} </th>
                       </tr>
                     </thead>
                     <tbody>
                       {
                         response##loginUsers
                         |> Array.mapi((index, user) =>
                              <tr key={index |> string_of_int}>
                                <td> {user##id |> DomHelper.textEl} </td>
                                <td>
                                  {user##user_name |> DomHelper.textEl}
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
                            )
                         |> ReasonReact.array
                       }
                     </tbody>
                   </table>
                 }
               }
             </div>
         }
    </GetAllUserQuery>,
};