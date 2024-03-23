@ECHO OFF

REM Check if the GCC compiler exists
IF NOT EXIST "c:\Programing Languages\LLVM\bin\gcc.exe" (
    ECHO The path does not exist. THIS IS MEANT TO ONLY be run on my computer. Please change the path to your own gcc compiler.
    EXIT /B
)

REM Check if file name argument is provided
IF "%~1"=="" (
    ECHO No file name provided.
    EXIT /B
)

REM Call the Python script passing all arguments
python compile.py %*