@echo off
cls

@REM :: Run CMake setup
@REM call build-cmake.bat

gcc src/main.c -o main 

@REM :: Prompt before running
set /p choice="Do you want to run the executable? (y/n): "
if /i "%choice%"=="y" (
    call "C:\Users\jayxw\Desktop\C And CPP Projects\C Memory Allocator\main.exe"
) else (
    echo Exiting without running the executable.
)


