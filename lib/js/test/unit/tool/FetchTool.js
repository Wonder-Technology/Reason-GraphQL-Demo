'use strict';

var Curry = require("bs-platform/lib/js/curry.js");

function buildFakeFetchSucessResponse(param) {
  return {
          json: (function (param) {
              return Promise.resolve("success fetch reponse");
            })
        };
}

function buildFakeFetchFailResponse(param) {
  return {
          json: (function (param) {
              return Promise.resolve({
                          errors: /* :: */[
                            {
                              message: "error fetch response"
                            },
                            /* [] */0
                          ]
                        });
            })
        };
}

function buildFakeFetch(buildFakeFetchResponseFunc) {
  return (function (_url) {
      return Promise.resolve(Curry._1(buildFakeFetchResponseFunc, /* () */0));
    });
}

function buildFakeFetchWithInit(buildFakeFetchResponseFunc) {
  return (function (_url, _data) {
      return Promise.resolve(Curry._1(buildFakeFetchResponseFunc, /* () */0));
    });
}

exports.buildFakeFetchSucessResponse = buildFakeFetchSucessResponse;
exports.buildFakeFetchFailResponse = buildFakeFetchFailResponse;
exports.buildFakeFetch = buildFakeFetch;
exports.buildFakeFetchWithInit = buildFakeFetchWithInit;
/* No side effect */
