var exec = require('cordova/exec');

exports.echo = function(arg0, success, error) {
    exec(success, error, "DahuaSDK", "echo", [arg0]);
};

exports.login = function(ip, port, user, passwd, success, error) {
    exec(success, error, "DahuaSDK", "login", [ip, port, user, passwd]);
};

exports.talk = function(success, error) {
    exec(success, error, "DahuaSDK", "talk", []);
};

