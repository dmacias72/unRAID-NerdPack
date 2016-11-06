/* jshint quotmark:false,indent:4,maxlen:600 */
var should = require("should");
var _ = require('underscore');

var buildQueryString = function(params){
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
};

describe("keen", function() {

    var keen;
    var Keen = require("../");
    var projectId = "fakeProjectId";
    var writeKey = "fakeWriteKey";
    var readKey = "fakeReadKey";
    var nock = require("nock");

    beforeEach(function() {
        nock.cleanAll();
        keen = require("../");
        keen = keen.configure({
            projectId: projectId,
            writeKey: writeKey
        });
    });

    afterEach(function() {
      nock.cleanAll();
    });

    it("configure should set up client correctly", function() {
        keen = require("../");
        var projectId = "projectId";
        var writeKey = "writeKey";
        var readKey = "readKey";
        var masterKey = "masterKey";
        keen = keen.configure({
            projectId: projectId,
            writeKey: writeKey,
            readKey: readKey,
            masterKey: masterKey
        });

        should.exist(keen);
        keen.projectId.should.equal(projectId);
        keen.writeKey.should.equal(writeKey);
        keen.readKey.should.equal(readKey);
        keen.masterKey.should.equal(masterKey);
        keen.baseUrl.should.equal("https://api.keen.io/");
        keen.apiVersion.should.equal("3.0");
    });

    it("configure should allow overriding baseUrl and apiVersion", function() {
        keen = require("../");
        var projectId = "projectId";
        var baseUrl = "blah";
        var apiVersion = "foo";
        keen = keen.configure({
            projectId: projectId,
            baseUrl: baseUrl,
            apiVersion: apiVersion
        });

        should.exist(keen);
        keen.projectId.should.equal(projectId);
        keen.baseUrl.should.equal(baseUrl);
        keen.apiVersion.should.equal(apiVersion);
    });

    it("configure should error on bad input", function() {
        keen = require("../");

        var badInputHelper = function(config, expectedErrorMessage) {
            try {
                keen.configure();
                should.fail();
            } catch (error) {
                should.exist(error);
                if (expectedErrorMessage) {
                    error.message.should.equal(expectedErrorMessage);
                }
            }
        };

        badInputHelper(undefined, "The 'config' parameter must be specified and must be a JS object.");
        badInputHelper(null, "The 'config' parameter must be specified and must be a JS object.");
        badInputHelper({}, "The 'config' parameter must be specified and must be a JS object.");
    });

    it("addEvent should require a writeKey", function(done) {
        keen = require("../");

        keen = keen.configure({
            projectId: projectId
        });

        keen.addEvent("eventCollection", {}, function(error) {
            should.exist(error);
            error.message.should.equal("You must specify a non-null, non-empty 'writeKey' in your 'config' object when calling keen.configure()!");
            done();
        });
    });

    var mockPostRequest = function(path, responseCode, responseBody) {
        nock("https://api.keen.io")
        .post(path)
        .reply(responseCode, responseBody, {"Content-Type": "application/json"});
    };

    var mockGetRequest = function(path, responseCode, responseBody) {
        nock("https://api.keen.io")
        .get(path)
        .reply(responseCode, responseBody, {"Content-Type": "application/json"});
    };

    var mockDeleteRequest = function(path, responseCode, responseBody) {
        nock("https://api.keen.io")
        .delete(path)
        .reply(responseCode, responseBody, {"Content-Type": "application/json"});
    };

    it("addEvent should make correct HTTP request", function(done) {
        var eventCollection = "purchases";

        mockPostRequest("/3.0/projects/" + projectId + "/events/" + eventCollection, 201, {success: true});

        keen.addEvent(eventCollection, {"a": "b"}, function(error, responseBody) {
            should.not.exist(error);
            JSON.stringify(responseBody).should.equal(JSON.stringify({success: true}));
            done();
        });
    });

    it("addEvents should make correct HTTP request", function(done) {
        mockPostRequest("/3.0/projects/" + projectId + "/events", 200, {
            "collection1": [{success: true}]
        });

        keen.addEvents({
            "collection1": [{"a": "b"}]
        }, function(error, responseBody) {
            should.not.exist(error);
            JSON.stringify(responseBody).should.equal(JSON.stringify({"collection1": [{success: true}]}));
            done();
        });
    });

    it("encrypt should generate a usable scoped key", function() {
        keen = require("../");
        var apiKey = "80ce00d60d6443118017340c42d1cfaf";
        var options = {
            "allowed_operations": ["read"],
            "filters": [ {
                "property_name": "purchase.amount",
                "operator": "eq",
                "property_value": 56
            }, {
                "property_name": "purchase.name",
                "operator": "ne",
                "property_value": "Barbie"
            }]
        };
        var scopedKey = keen.encryptScopedKey(apiKey, options);

        // decrypt
        var decryptedOptions = keen.decryptScopedKey(apiKey, scopedKey);
        decryptedOptions.should.eql(options);
    });

    it("decrypt should return the correct options", function() {
        keen = require("../");
        var apiKey = "f5d7c745ba4f437a82db02ca8b416556";
        var scopedKey = "7b8f357fa55e35efb2f7fa51a03ec2835c5537e57457c5a7c1c40c454fc00d5addef7ed911303fc2fa9648d3ae13e638192b86e90cd88657c9dc5cf03990cbf6eb2a7994513d34789bd25447f3dccaf5a3de3b9cacf6c11ded581e0506fca147ea32c13169787bbf8b4d3b8f2952bc0bea1beae3cfbbeaa1f421be2eac4cc223";
        var options = keen.decryptScopedKey(apiKey, scopedKey);
        var expected = {
            filters:[ { property_name: 'account_id',
            operator: 'eq',
            property_value: '4d9a4c421d011c553e000001' } ]
        };
        expected.should.eql(options);
    });

    it("should handle API errors", function(done) {
        var id = 'foo';
        var mockResponse = {error_code: 'FooError', message: 'no foo'};
        mockPostRequest("/3.0/projects/"+projectId+"/events/"+id, 500, mockResponse);

        keen.addEvent(id, {}, function(err) {
            err.should.be.an.instanceOf(Error);
            err.should.have.property('message', mockResponse.message);
            err.should.have.property('code', mockResponse.error_code);
            done();
        });
    });

    describe('request', function() {
        it("should expect a GET/POST/DEL method", function() {
            should(function() {
                keen.request('foo', 'write', '/');
            }).throwError('Method must be of type: GET/POST/DEL');
        });

        it("should expect a write/read/master keytype", function() {
            should(function() {
                keen.request('get', 'foo', '/');
            }).throwError('Key must be of type: master/write/read');
        });

        it("should require a string path", function() {
            should(function() {
                keen.request('get', 'read');
            }).throwError('\'path\' must be a string.');
        });

        it("should expect a key to be set", function() {
            should(function() {
                keen.request('get', 'read', '/');
            }).throwError('You must specify a nun-null, non-empty \'readKey\' in your config object.');
        });

        describe('send the request', function() {
            var projectId = "projectId";
            var baseUrl = "https://api.keen.io/";
            var apiVersion = "3.0";
            var mockResponse = {result: 1};
            var keen = require('../').configure({
                projectId: projectId,
                baseUrl: baseUrl,
                apiVersion: apiVersion,
                readKey: 'foo'
            });

            it('should send the request', function() {
                mockGetRequest("/"+ apiVersion +"/projects/"+ projectId +"/queries/count?event_collection=foo", 200, mockResponse);
                keen.request('get', 'read', '/queries/count', {event_collection:'foo'}, function(err, res) {
                    (err === null).should.be.true;
                    res.should.eql(mockResponse);
                });
            });

            it('has optional params', function() {
                mockGetRequest("/"+ apiVersion +"/projects/"+projectId+"/queries/count?event_collection=bar", 200, mockResponse);
                keen.request('get', 'read', '/queries/count', {event_collection:'bar'}, function(err, res) {
                    (err === null).should.be.true;
                    res.should.eql(mockResponse);
                });
            });
        });
    });

    describe('Public Methods', function() {
      var projectId = "projectId";
      var baseUrl = "https://api.keen.io/";
      var apiVersion = "3.0";
      var mockResponse = {result: 1};
      var keen = require('../').configure({
          projectId: projectId,
          baseUrl: baseUrl,
          apiVersion: apiVersion,
          readKey: 'foo'
      });

      describe('projects', function() {
        it('should be able to call "list"', function(done) {
          mockGetRequest("/" + apiVersion + "/projects", 200, mockResponse);
          keen.projects.list( function ( err, res ) {
            (err === null).should.be.true;
            res.should.eql(mockResponse);
            done();
          });
        });

        it('should be able to call "view"', function(done) {
          mockGetRequest("/" + apiVersion + "/projects/" + projectId, 200, mockResponse);
          keen.projects.view( projectId, function ( err, res ) {
            (err === null).should.be.true;
            res.should.eql(mockResponse);
            done();
          });
        });
      });

      describe('events', function() {
        it('should be able to call "list"', function(done) {
          mockGetRequest("/" + apiVersion + "/projects/" + projectId + "/events", 200, mockResponse);
          keen.events.list( projectId, function ( err, res ) {
            (err === null).should.be.true;
            res.should.eql(mockResponse);
            done();
          });
        });

        it('should be able to call "insert"', function(done) {
          mockPostRequest("/" + apiVersion + "/projects/" + projectId + "/events", 200, mockResponse);
          keen.events.insert( projectId, null, function ( err, res ) {
            (err === null).should.be.true;
            res.should.eql(mockResponse);
            done();
          });
        });
      });

      describe('properties', function() {
        var collection = "test_collection";
        var property = "test_property";
        it('should be able to call "view"', function(done) {
          mockGetRequest("/" + apiVersion + "/projects/" + projectId + "/events/" + collection + "/properties/" + property, 200, mockResponse);
          keen.properties.view( projectId, collection, property, function ( err, res ) {
            (err === null).should.be.true;
            res.should.eql(mockResponse);
            done();
          });
        });

        it('should be able to call "remove"', function(done) {
          mockDeleteRequest("/" + apiVersion + "/projects/" + projectId + "/events/" + collection + "/properties/" + property, 200, mockResponse);
          keen.properties.remove( projectId, collection, property, function ( err, res ) {
            (err === null).should.be.true;
            res.should.eql(mockResponse);
            done();
          });
        });
      });

      describe('collections', function() {
        var collection = "test_collection";
        it('should be able to call "view"', function(done) {
          mockGetRequest("/" + apiVersion + "/projects/" + projectId + "/events/" + collection, 200, mockResponse);
          keen.collections.view( projectId, collection, function ( err, res ) {
            (err === null).should.be.true;
            res.should.eql(mockResponse);
            done();
          });
        });

        it('should be able to call "remove"', function(done) {
          mockDeleteRequest("/" + apiVersion + "/projects/" + projectId + "/events/" + collection, 200, mockResponse);
          keen.collections.remove( projectId, collection, function ( err, res ) {
            (err === null).should.be.true;
            res.should.eql(mockResponse);
            done();
          });
        });
      });

      describe('queries', function() {
        var collection = "test_collection";
        it('should be able to call "extraction" with no params', function(done) {
          var qs = buildQueryString( { event_collection: collection } );
          mockGetRequest("/" + apiVersion + "/projects/" + projectId + "/queries/extraction" + qs, 200, mockResponse);
          keen.queries.extraction( projectId, collection, null, function ( err, res ) {
            (err === null).should.be.true;
            res.should.eql(mockResponse);
            done();
          });
        });

        it('should not be able to override the "extraction" collection from params hash', function(done) {
          var qs = buildQueryString( { event_collection: collection } );
          mockGetRequest("/" + apiVersion + "/projects/" + projectId + "/queries/extraction" + qs, 200, mockResponse);
          keen.queries.extraction( projectId, collection, { event_collection: "attempt_override" }, function ( err, res ) {
            (err === null).should.be.true;
            res.should.eql(mockResponse);
            done();
          });
        });
      });
    });

    describe('Queries', function() {

      beforeEach(function() {
        nock.cleanAll();
        Keen = require("../");
        keen = Keen.configure({
          projectId: projectId,
          readKey: readKey
        });
      });

      describe('<Client>.run method', function(){

        it('should be a method', function(){
          keen['run'].should.be.a.Function;
        });

        it('should throw an error when passed an invalid object', function(){
          (function(){
            keen.run(null);
          }).should.throwError();
          (function(){
            keen.run({});
          }).should.throwError();
          (function(){
            keen.run(0);
          }).should.throwError();

          // This should be removed when 'saved_query' support is validated
          (function(){
            keen.run('string');
          }).should.throwError();
        });

      });

      describe('Analysis Types', function(){

        var analyses = [
          'count',
          'count_unique',
          'sum',
          'median',
          'percentile',
          'average',
          'minimum',
          'maximum',
          'select_unique',
          'extraction'
        ];

        _.each(analyses, function(type){
          var analysis = new Keen.Query(type, {
            eventCollection: 'eventCollection',
            timeframe: 'this_7_days'
          });
          var query_path = "/3.0/projects/" + projectId + "/queries/" + type;

          it('should be an instance of Keen.Query', function(){
            analysis.should.be.an.instanceOf(Keen.Query);
          });

          it('should have a correct path propery', function(){
            analysis.should.have.property('path');
            analysis.path.should.eql('/queries/' + type);
          });

          it('should have a params property with supplied parameters', function(){
            analysis.should.have.property('params');
            analysis.params.should.have.property('event_collection', 'eventCollection');
            analysis.params.should.have.property('timeframe', 'this_7_days');
          });

          it('should have a #get method that returns a requested parameter', function(){
            analysis.get.should.be.a.Function;
            analysis.get('timeframe').should.eql('this_7_days');
          });

          it('should have a #set method that sets all supplied properties', function(){
            analysis.set.should.be.a.Function;
            analysis.set({ group_by: 'property', target_property: 'referrer' });
            analysis.params.should.have.property('group_by', 'property');
            analysis.params.should.have.property('target_property', 'referrer');
          });

          it('should #set under_score attributes when camelCase attributes are supplied', function(){
            analysis.set({ groupBy: 'property' });
            analysis.params.should.have.property('group_by', 'property');
          });

          describe('When handled by <Client>.run method', function(){

            beforeEach(function() {
              nock.cleanAll();
            });

            describe('Single analyses', function(){

              it('should return a response when successful', function(done){
                var mockResponse = { result: 1 };
                mockGetRequest(query_path, 200, mockResponse);
                analysis.params = {};
                var test = keen.run(analysis, function(err, res){
                  (err === null).should.be.true;
                  res.should.eql(mockResponse);
                  done();
                });
              });

              it('should return an error when unsuccessful', function(done){
                var mockResponse = { error_code: 'ResourceNotFoundError', message: 'no foo' };
                mockGetRequest(query_path, 500, mockResponse);
                analysis.params = {};
                var test = keen.run(analysis, function(err, res){
                  err.should.be.an.instanceOf(Error);
                  err.should.have.property('code', mockResponse.error_code);
                  done();
                });
              });

            });


            describe('Multiple analyses', function(){

              it('should return a single response when successful', function(done){
                var mockResponse = { result: 1 };
                mockGetRequest(query_path, 200, mockResponse);
                mockGetRequest(query_path, 200, mockResponse);
                mockGetRequest(query_path, 200, mockResponse);
                analysis.params = {};
                var test = keen.run([analysis, analysis, analysis], function(err, res){
                  (err === null).should.be.true;
                  res.should.be.an.Array;
                  res.should.have.length(3);
                  res.should.eql([mockResponse, mockResponse, mockResponse]);
                  done();
                });
              });

              it('should return a single error when unsuccessful', function(done){
                var mockResponse = { error_code: 'ResourceNotFoundError', message: 'no foo' };
                mockGetRequest(query_path, 500, mockResponse);
                analysis.params = {};
                var test = keen.run([analysis, analysis, analysis], function(err, res){
                  err.should.be.an.instanceOf(Error);
                  err.should.have.property('code', mockResponse.error_code);
                  done();
                });
              });
            });


          });

        });

      });


      describe('Funnels', function(){

        var funnel = new Keen.Query('funnel', {
          steps: [
            { event_collection: "view_landing_page", actor_property: "user.id" },
            { eventCollection: "sign_up", actorProperty: "user.id" }
          ],
          timeframe: "this_21_days"
        });
        var funnel_path = "/3.0/projects/" + projectId + "/queries/funnel" + buildQueryString(funnel.params);

        it('should be an instance of Keen.Query', function(){
          funnel.should.be.an.instanceOf(Keen.Query);
        });

        it('should have a correct path propery', function(){
          funnel.should.have.property('path');
          funnel.path.should.eql('/queries/funnel');
        });

        it('should have a params property with supplied parameters', function(){
          funnel.should.have.property('params');
          funnel.params.should.have.property('steps');
          funnel.params.steps.should.be.an.Array.with.lengthOf(2);
        });

        it('should have steps with parameters in proper case', function(){
          funnel.params.steps[1].should.have.property('event_collection');
          funnel.params.steps[1].should.have.property('actor_property');
        });

        it('should have a #get method that returns a requested parameter', function(){
          funnel.get.should.be.a.Function;
          funnel.get('steps').should.be.an.Array;
          funnel.get('timeframe').should.eql('this_21_days');
        });

        it('should have a #set method that sets all supplied properties', function(){
          funnel.set.should.be.a.Function;
          funnel.set({ timeframe: 'this_21_days' });
          funnel.params.should.have.property('timeframe', 'this_21_days');
        });

        it('should #set under_score step attributes when camelCase are supplied ', function(){
          funnel.set({ steps: [
              { eventCollection: "view_landing_page", actorProperty: "user.id" },
              { eventCollection: "sign_up", actorProperty: "user.id" }
            ] });
          funnel.params.steps[0].should.have.property('event_collection', 'view_landing_page');
          funnel.params.steps[0].should.have.property('actor_property', 'user.id');
          funnel.params.steps[1].should.have.property('event_collection', 'sign_up');
          funnel.params.steps[1].should.have.property('actor_property', 'user.id');
        });



        describe('When handled by <Client>.run method', function(){

          beforeEach(function() {
            nock.cleanAll();
          });

          describe('Single analyses', function(){

            it('should return a response when successful', function(done){
              var mockResponse = { result: 1 };
              mockGetRequest(funnel_path, 200, mockResponse);
              var test = keen.run(funnel, function(err, res){
                (err === null).should.be.true;
                res.should.eql(mockResponse);
                done();
              });
            });

            it('should return an error when unsuccessful', function(done){
              var mockResponse = { error_code: 'ResourceNotFoundError', message: 'no foo' };
              mockGetRequest(funnel_path, 500, mockResponse);
              var test = keen.run(funnel, function(err, res){
                err.should.be.an.instanceOf(Error);
                err.should.have.property('code', mockResponse.error_code);
                done();
              });
            });

          });


          describe('Multiple analyses', function(){

            it('should return a single response when successful', function(done){
              var mockResponse = { result: 1 };
              mockGetRequest(funnel_path, 200, mockResponse);
              mockGetRequest(funnel_path, 200, mockResponse);
              mockGetRequest(funnel_path, 200, mockResponse);
              var test = keen.run([funnel, funnel, funnel], function(err, res){
                (err === null).should.be.true;
                res.should.be.an.Array;
                res.should.have.length(3);
                res.should.eql([mockResponse, mockResponse, mockResponse]);
                done();
              });
            });

            it('should return a single error when unsuccessful', function(done){
              var mockResponse = { error_code: 'ResourceNotFoundError', message: 'no foo' };
              mockGetRequest(funnel_path, 500, mockResponse);
              var test = keen.run([funnel, funnel, funnel], function(err, res){
                err.should.be.an.instanceOf(Error);
                err.should.have.property('code', mockResponse.error_code);
                done();
              });
            });

          });


        });



      });

    });

});
