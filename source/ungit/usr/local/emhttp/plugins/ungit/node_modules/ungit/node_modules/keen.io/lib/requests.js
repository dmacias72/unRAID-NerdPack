var rest = require('superagent');
var crypto = require('crypto');

// Handle logic of processing response, including error messages
// The error handling should be strengthened over time to be more
// meaningful and robust
// ---------------------------------------------------------------

function processResponse(err, res, callback) {
  callback = callback || function() {};

  if (res && !res.ok && !err) {
    var is_err = res.body && res.body.error_code;
    err = new Error(is_err ? res.body.message : 'Unknown error occurred');
    err.code = is_err ? res.body.error_code : 'UnknownError';
  }

  if (err) return callback(err);
  return callback(null, res.body);
}

function buildQueryString(params){
  var query = [];
  for (var key in params) {
    if (params[key]) {
      var value = params[key];
      if (Object.prototype.toString.call(value) !== '[object String]') {
        value = JSON.stringify(value);
      }
      value = encodeURIComponent(value);
      query.push(key + '=' + value);
    }
  }
  return "?" + query.join('&');
}

module.exports = {
  get: function(apiKey, path, data, callback) {
    rest
    .get(this.baseUrl + this.apiVersion + path + buildQueryString(data))
    .set('Authorization', apiKey)
    .end(function(err, res) {
      processResponse(err, res, callback);
    });
  },
  post: function(apiKey, path, data, callback) {
    rest
    .post(this.baseUrl + this.apiVersion + path)
    .set('Authorization', apiKey)
    .set('Content-Type', 'application/json')
    .send(data || {})
    .end(function(err, res) {
      processResponse(err, res, callback);
    });
  },
  del: function(apiKey, path, callback) {
    rest
    .del(this.baseUrl + this.apiVersion + path)
    .set('Authorization', apiKey)
    .set('Content-Length', 0)
    .end(function(err, res) {
      processResponse(err, res, callback);
    });
  }
};
