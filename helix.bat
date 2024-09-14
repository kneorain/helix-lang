@echo off

rem Build the helix project using xmake
xmake

rem Run the helix project with all arguments passed to the batch file
build\debug\x64-msvc-windows\bin\helix %*