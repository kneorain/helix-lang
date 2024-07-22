@echo off

rem Build the tests project using xmake
xmake build tests

rem Run the tests project with all arguments passed to the batch file
xmake run tests %*