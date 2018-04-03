var exec = require('cordova/exec');

exports.login = function(ip, port, user, passwd, success, error) {
    exec(success, error, "DahuaSDK", "login", [ip, port, user, passwd]);
};

exports.talk = function(success, error) {
    exec(success, error, "DahuaSDK", "talk", []);
};
