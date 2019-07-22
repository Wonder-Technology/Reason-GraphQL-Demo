open TransactionType;

open WonderBsJson;

let rec _iterateTransactionArrayWithInsertId =
        (conn, transactionArray, handleParamWithInsertIdFunc, insertId) =>
  switch (transactionArray |> Js.Array.shift) {
  | None => Js.Promise.make((~resolve, ~reject) => resolve(. ignore()))
  | Some(transactionItem) =>
    let {sql, param} = transactionItem;

    let param =
      switch (insertId) {
      | None => param
      | Some(id) =>
        switch (handleParamWithInsertIdFunc) {
        | None => param
        | Some(handleFunc) => handleFunc(id)
        }
      };

    Js.Promise.make((~resolve, ~reject) =>
      MySql2.execute(conn, sql, param, result =>
        switch (result) {
        | `Error(e) => reject(. e |> MySql2.Exn.sqlErrorToExn)

        | `Select(_) =>
          resolve(.
            _iterateTransactionArrayWithInsertId(
              conn,
              transactionArray,
              handleParamWithInsertIdFunc,
              None,
            )
            |> Obj.magic,
          )

        | `Mutation(mutation) =>
          resolve(.
            _iterateTransactionArrayWithInsertId(
              conn,
              transactionArray,
              handleParamWithInsertIdFunc,
              SqlOperateType.convertMutationToJsObj(mutation)##insertId
              |> Js.Null_undefined.return
              |> Js.Null_undefined.toOption,
            )
            |> Obj.magic,
          )
        }
      )
    );
  };

let iterateHandleTransactionArray =
    (conn, transactionArray, handleParamWithInsertIdFunc) =>
  _iterateTransactionArrayWithInsertId(
    conn,
    transactionArray,
    handleParamWithInsertIdFunc,
    None,
  );