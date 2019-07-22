open WonderBsJson;

open ServerConfigParseType;

let handleSqlForGraphQL = (conn, sql, param, ()) =>
  Js.Promise.make((~resolve, ~reject) =>
    MySql2.execute(
      conn,
      sql,
      param,
      response => {
        switch (response) {
        | `Error(e) => reject(. e |> MySql2.Exn.sqlErrorToExn)
        | `Select(select) =>
          resolve(. SqlOperateType.convertSelectToJsObj(select)##rows)
        | `Mutation(mutation) =>
          resolve(.
            Json.Encode.object_([
              ("result", Json.Encode.string("success")),
              (
                "insertId",
                SqlOperateType.convertMutationToJsObj(mutation)##insertId,
              ),
            ])
            |> Js.Json.stringify,
          )
        };

        MySql2.Connection.close(conn);
      },
    )
  );

