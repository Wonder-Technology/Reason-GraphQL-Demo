'use strict';

var Most = require("most");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var GraphQL$WonderBsGraphql = require("wonder-bs-graphql/lib/js/src/GraphQL.js");
var AppGraphQL$ReasonGraphqlFullstack = require("../../../src/server/database/graphQL/AppGraphQL.js");

function runGraphql(source, rootValue) {
  return Most.fromPromise(GraphQL$WonderBsGraphql.run(Caml_option.some(rootValue), undefined, undefined, undefined, undefined, AppGraphQL$ReasonGraphqlFullstack.getSchema(/* () */0), source, /* () */0));
}

var getSchema = AppGraphQL$ReasonGraphqlFullstack.getSchema;

exports.getSchema = getSchema;
exports.runGraphql = runGraphql;
/* most Not a pure module */
