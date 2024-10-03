@echo off
setlocal

rem Initialize an empty variable to collect the remaining arguments
set "ARGS="

rem Check if the first argument is '--'
if "%1" == "--" (
    rem Shift to remove the '--'
    shift
) else (
    rem Build the Helix project using xmake
    xmake
)

rem Collect all the remaining arguments after '--'
:loop
if "%1"=="" goto endloop
    set "ARGS=%ARGS% %1"
    shift
    goto loop

:endloop
rem Now run the binary with the collected arguments, without passing '--'
build\debug\x64-msvc-windows\bin\helix %ARGS%

endlocal
