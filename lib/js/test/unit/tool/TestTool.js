'use strict';

var Most = require("most");
var Curry = require("bs-platform/lib/js/curry.js");
var Process = require("process");
var CamlinternalOO = require("bs-platform/lib/js/camlinternalOO.js");
var ValueUtils$ReasonGraphqlFullstack = require("../../../src/utils/ValueUtils.js");
var ResponseTool$ReasonGraphqlFullstack = require("./ResponseTool.js");
var ResponseUtils$ReasonGraphqlFullstack = require("../../../src/server/routes/utils/ResponseUtils.js");

function getTestFileChunkStoreDir(param) {
  return Process.cwd() + "/test/res/fileChunk/";
}

function getTestImageStoreDir(param) {
  return Process.cwd() + "/test/res/image/";
}

function getTestImageAccessDir(param) {
  return "/image/";
}

var class_tables = [
  0,
  0,
  0
];

function buildTestResultAndErrRef(param) {
  if (!class_tables[0]) {
    var $$class = CamlinternalOO.create_table(0);
    var env = CamlinternalOO.new_variable($$class, "");
    var env_init = function (env$1) {
      var self = CamlinternalOO.create_object_opt(0, $$class);
      self[env] = env$1;
      return self;
    };
    CamlinternalOO.init_class($$class);
    class_tables[0] = env_init;
  }
  return /* tuple */[
          /* record */[/* contents */Curry._1(class_tables[0], 0)],
          /* record */[/* contents */undefined]
        ];
}

var class_tables$1 = [
  0,
  0,
  0
];

function getEmptyJsObj(param) {
  if (!class_tables$1[0]) {
    var $$class = CamlinternalOO.create_table(0);
    var env = CamlinternalOO.new_variable($$class, "");
    var env_init = function (env$1) {
      var self = CamlinternalOO.create_object_opt(0, $$class);
      self[env] = env$1;
      return self;
    };
    CamlinternalOO.init_class($$class);
    class_tables$1[0] = env_init;
  }
  return Curry._1(class_tables$1[0], 0);
}

function handleRunGraphQLFail(stream) {
  return Most.flatMap((function (response) {
                var errors = response.errors;
                var match = ValueUtils$ReasonGraphqlFullstack.isValueValid(errors);
                if (match) {
                  return ResponseTool$ReasonGraphqlFullstack.throwError(ResponseUtils$ReasonGraphqlFullstack.GraphQLResponse[/* getErrorMessage */1](errors));
                } else {
                  return Most.just(response.data);
                }
              }), stream);
}

function setResultOrErrorValue(resultRef, errorRef, stream) {
  return Most.forEach((function (response) {
                resultRef[0] = response;
                return /* () */0;
              }), Most.recoverWith((function (error) {
                    errorRef[0] = error;
                    return Most.just(getEmptyJsObj(/* () */0));
                  }), stream));
}

exports.getTestFileChunkStoreDir = getTestFileChunkStoreDir;
exports.getTestImageStoreDir = getTestImageStoreDir;
exports.getTestImageAccessDir = getTestImageAccessDir;
exports.buildTestResultAndErrRef = buildTestResultAndErrRef;
exports.getEmptyJsObj = getEmptyJsObj;
exports.handleRunGraphQLFail = handleRunGraphQLFail;
exports.setResultOrErrorValue = setResultOrErrorValue;
/* most Not a pure module */
