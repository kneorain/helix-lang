@echo off

rem Build the helix project using xmake
xmake build helix

rem Run the helix project with all arguments passed to the batch file
xmake run helix %*