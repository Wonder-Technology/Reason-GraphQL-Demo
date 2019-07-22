
type transactionItem = {
    sql:string,
    param: option(MySql2.Params.t)
};

type transactionArray = array(transactionItem);