'use strict';


function buildFakeGetRequest(query) {
  return {
          query: query
        };
}

function buildFakePostRequest(bodyJson) {
  return {
          body: bodyJson
        };
}

exports.buildFakeGetRequest = buildFakeGetRequest;
exports.buildFakePostRequest = buildFakePostRequest;
/* No side effect */
