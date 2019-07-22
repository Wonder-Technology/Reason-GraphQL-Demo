'use strict';

var Most = require("most");
var Sinon = require("wonder-bs-sinon/lib/js/src/sinon.js");

function buildFakeResponse(sandbox) {
  return {
          json: Sinon.createEmptyStubWithJsObjSandbox(sandbox),
          sendFile: Sinon.createEmptyStubWithJsObjSandbox(sandbox),
          send: Sinon.createEmptyStubWithJsObjSandbox(sandbox),
          sendStatus: Sinon.createEmptyStubWithJsObjSandbox(sandbox),
          status: Sinon.createEmptyStubWithJsObjSandbox(sandbox),
          redirect: Sinon.createEmptyStubWithJsObjSandbox(sandbox),
          set: Sinon.createEmptyStubWithJsObjSandbox(sandbox),
          links: Sinon.createEmptyStubWithJsObjSandbox(sandbox)
        };
}

function throwError(error) {
  return Most.throwError(error);
}

exports.buildFakeResponse = buildFakeResponse;
exports.throwError = throwError;
/* most Not a pure module */
