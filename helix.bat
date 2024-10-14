@echo off
setlocal enabledelayedexpansion

rem Initialize an empty variable to collect the remaining arguments
set "ARGS="

rem Check if the first argument is '--'
if "%1"=="--" (
    rem Shift to remove the '--'
    shift
) else (
    rem Build the Helix project using xmake
    xmake
)

rem Collect all the remaining arguments after '--'
:loop
if "%1"=="" goto endloop
    set "ARGS=!ARGS! %1"
    shift
    goto loop

:endloop

rem Get the path of the binary
for /f "tokens=2" %%a in ('xmake show -t helix ^| findstr "targetfile"') do (
    set "PATH_TO_BINARY=%%a"
)

rem Convert to an absolute path using for loop to append to current directory
for %%i in ("%cd%\%PATH_TO_BINARY%") do set "ABS_PATH=%%~fi"

rem Debug output (optional)
echo Running %ABS_PATH% with arguments: %ARGS%

rem Run the binary with the remaining arguments
%ABS_PATH% %ARGS%

endlocal
