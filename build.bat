@echo off
cls

:: Run CMake setup
call build-cmake.bat

:: Prompt before running
set /p choice="Do you want to run the executable? (y/n): "

if /i "%choice%"=="y" (
    call "C:\Users\jayxw\Desktop\C And CPP Projects\C Memory Allocator\build\Debug\main.exe"
) else (
    echo Exiting without running the executable.
)
