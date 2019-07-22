var fs = require('fs')
var gulp = require("gulp");
var gulpSync = require("gulp-sync")(gulp);
var path = require("path");
var exec = require('child_process').exec;

var _safeExec = (commandStr, handleErrFunc, handleSuccessFunc, done) => exec(commandStr, { maxBuffer: 1024 * 500 }, function (err, stdout, stderr) {
    if (err) {
        handleErrFunc(err, done);

        return;
    }

    handleSuccessFunc(done);
});

gulp.task("setConfigIsProdToBeTrue", function (done) {
    const systemConfigFilePath = path.join(__dirname, "src/config/SystemConfig.re");

    var configData = fs.readFileSync(systemConfigFilePath, "utf8");

    var result = configData.replace(/(let\sisProd\s=\s\(\)\s=>\s)(.+)\;$/img, function (match, p1, p2) {
        return p1 + "true" + "\;";
    });

    fs.writeFileSync(
        systemConfigFilePath, result, "utf8"
    );

    done();
});

gulp.task("bsb:build", function (done) {
    _safeExec("sudo npm run bsb:build", (err, done) => { throw err }, (done) => done(), done);
});


gulp.task("webpack:dev", function (done) {
    _safeExec("sudo npm run webpack:dev", (err, done) => { throw err }, (done) => done(), done);
});


gulp.task("webpack:prod", function (done) {
    _safeExec("sudo npm run webpack:prod", (err, done) => { throw err }, (done) => done(), done);
});


gulp.task("build:online", gulpSync.sync(["setConfigIsProdToBeTrue", "bsb:build", "webpack:dev"]));

gulp.task("buildProd:online", gulpSync.sync(["setConfigIsProdToBeTrue", "bsb:build", "webpack:prod"]));
