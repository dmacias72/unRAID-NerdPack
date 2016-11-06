'use strict';

var Bluebird = require('bluebird');
var fs = Bluebird.promisifyAll(require("fs"));
var semver = require('semver');

if (semver.satisfies(process.version, '>0.10')) {
  fs.isExists = function (file) {
    return fs.accessAsync(file, fs.F_OK).then(function () {
      return true;
    }).catch(function () {
      return false;
    });
  };
} else {
  fs.isExists = function (file) {
    return new Bluebird(function (resolve) {
      return fs.exists(file, resolve);
    });
  };
}

module.exports = fs;
