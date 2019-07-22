open MysqlOperate;

open WonderBsMost;

let transactionMonitor = (conn, transactionArray, generateParamFunc) =>
  Connection.beginTransaction(conn)
  |> Transaction.rollbackAndThrowError(conn)
  |> Most.concatMap(_ =>
       TransactionUtils.iterateHandleTransactionArray(
         conn,
         transactionArray,
         generateParamFunc,
       )
       |> Most.fromPromise
       |> Transaction.rollbackAndThrowError(conn)
     )
  |> Most.concatMap(_ =>
       Connection.commit(conn) |> Transaction.rollbackAndThrowError(conn)
     );