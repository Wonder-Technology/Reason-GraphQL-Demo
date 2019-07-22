open WonderBsMost;

open WonderBsJson;

open MySql2;

module Connection = {
  let beginTransaction = conn =>
    Js.Promise.make((~resolve, ~reject) =>
      MySql2.Connection.beginTransaction(conn, error =>
        switch (error |> Js.Null_undefined.toOption) {
        | Some(error) => reject(. error |> MySql2.Exn.transationErrorToExn)
        | None => resolve(. ignore())
        }
      )
    )
    |> Most.fromPromise;

  let commit = conn =>
    Js.Promise.make((~resolve, ~reject) =>
      MySql2.Connection.commit(conn, error =>
        switch (error |> Js.Null_undefined.toOption) {
        | Some(error) => reject(. error |> MySql2.Exn.transationErrorToExn)
        | None => resolve(. ignore())
        }
      )
    )
    |> Most.fromPromise;

  let rollback = conn =>
    Js.Promise.make((~resolve, ~reject) =>
      MySql2.Connection.rollback(conn, error =>
        switch (error |> Js.Null_undefined.toOption) {
        | Some(error) => reject(. error |> MySql2.Exn.transationErrorToExn)
        | None => resolve(. ignore())
        }
      )
    )
    |> Most.fromPromise;
};

module Transaction = {
  let rollbackAndThrowError = (conn, stream) =>
    stream
    |> Most.recoverWith(err =>
         Connection.rollback(conn) |> Most.flatMap(_ => Most.throwError(err))
       );
};

module GraphqlOperate = {
  let handleSqlForGraphQL = (mysqlPool, sql, param, ()) =>
    Js.Promise.make((~resolve, ~reject) =>
      MySql2.Pool.getConnection(mysqlPool, (error, conn) =>
        switch (
          error |> Js.Null_undefined.toOption,
          conn |> Js.Null_undefined.toOption,
        ) {
        | (Some(error), None) =>
          reject(.
            error
            |> MysqlCommon.convertJsExnToMysqlExn
            |> MySql2.Exn.transationErrorToExn,
          )
        | (None, Some(conn)) =>
          MySql2.execute(conn, sql, param, response =>
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
            }
          );

          MySql2.Pool.release(conn);
        | _ => reject(. Failure("get mysql connection error"))
        }
      )
    );
};