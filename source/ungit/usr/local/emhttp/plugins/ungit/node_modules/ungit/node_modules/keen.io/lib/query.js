var _ = require('underscore');
var KeenRequests = require('./requests');

/*!
* -----------------
* Keen IO Query JS
* -----------------
*/

var Keen = {};

// ------------------------------
// Keen.Request
// ------------------------------

Keen.Request = function(){
  this.data = {};
  this.configure.apply(this, arguments);
}

Keen.Request.prototype.configure = function(client, queries, callback){
  this.client = client;
  this.queries = queries;
  this.callback = callback;
  this.run();
  return this;
};

Keen.Request.prototype.run = function(){
  var self = this,
      completions = 0,
      response = [];

  var handleResponse = function(err, res){
    if (err && self.callback) {
      return self.callback(err, null);
    }
    response[arguments[2]] = res, completions++;
    if (completions == self.queries.length) {
      self.data = (self.queries.length == 1) ? response[0] : response;
      if (self.callback) self.callback(null, self.data);
    }
  };

  _.each(self.queries, function(query, index){
    var data, path = '/projects/' + self.client.projectId;
    var callbackSequencer = function(err, res){
      handleResponse(err, res, index);
    };

    if (query instanceof Keen.Query) {
      path += query.path;
      data = query.params || {};
    }
    /* TODO: Test and deploy this
    else if (_.isString(query)) {
      path += '/saved_queries/' + query + '/result';
      data = { api_key: self.client.readKey };
    }*/
    else {
      throw new Error('Query #' + (index+1)  +' is not valid');

    }

    KeenRequests.get.call(self.client, self.client.readKey, path, data, callbackSequencer);
  });

  return self;
};


// ------------------------------
// Keen.Query
// ------------------------------

Keen.Query = function(){
  this.configure.apply(this, arguments);
};

Keen.Query.prototype.configure = function(analysisType, params){
  //if (!collection) throw new Error('Event Collection name is required');
  var self = this;
  self.path = '/queries/' + analysisType;
  self.params = {};
  self.set(params);
  return self;
};

Keen.Query.prototype.get = function(attribute) {
  if (this.params) {
    return this.params[attribute] || null;
  }
};

Keen.Query.prototype.set = function(attributes) {
  var self = this;
  _.each(attributes, function(v, k){
    var key = k, value = v;
    if (k.match(new RegExp("[A-Z]"))) {
      key = k.replace(/([A-Z])/g, function($1) { return "_"+$1.toLowerCase(); });
    }
    self.params[key] = value;

    if (_.isArray(value)) {
      _.each(value, function(dv, index){
        if (_.isObject(dv)) {
          _.each(dv, function(deepValue, deepKey){
            if (deepKey.match(new RegExp("[A-Z]"))) {
              var _deepKey = deepKey.replace(/([A-Z])/g, function($1) { return "_"+$1.toLowerCase(); });
              delete self.params[key][index][deepKey];
              self.params[key][index][_deepKey] = deepValue;
            }
          });
        }
      });
    }

  });
  return self;
};


// Export Methods
// ------------------------------
module.exports = {
  client: {
    run: function(query, callback){
      if (!query) throw new Error('At least one query is required');
      var queries = (_.isArray(query)) ? query : [query];
      return new Keen.Request(this, queries, callback);
    }
  },
  Query: Keen.Query
};
