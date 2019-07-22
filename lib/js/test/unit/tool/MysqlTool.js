'use strict';

var MySql2 = require("wonder-bs-mysql2/lib/js/src/MySql2.bs.js");
var Json_encode$WonderBsJson = require("wonder-bs-json/lib/js/src/Json_encode.js");

function handleSqlForGraphQL(conn, sql, param, param$1) {
  return new Promise((function (resolve, reject) {
                return MySql2.execute(conn, sql, param, (function (response) {
                              var variant = response[0];
                              if (variant !== 516394780) {
                                if (variant >= 1035765577) {
                                  resolve(JSON.stringify(Json_encode$WonderBsJson.object_(/* :: */[
                                                /* tuple */[
                                                  "result",
                                                  "success"
                                                ],
                                                /* :: */[
                                                  /* tuple */[
                                                    "insertId",
                                                    response[1].insertId
                                                  ],
                                                  /* [] */0
                                                ]
                                              ])));
                                } else {
                                  reject(MySql2.Exn[/* sqlErrorToExn */2](response[1]));
                                }
                              } else {
                                resolve(response[1].rows);
                              }
                              return MySql2.Connection[/* close */5](conn);
                            }));
              }));
}

exports.handleSqlForGraphQL = handleSqlForGraphQL;
/* MySql2 Not a pure module */
