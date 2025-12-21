@echo off
chcp 65001 > nul

set FILES=menuFunctions.cpp menuItems.cpp main.cpp
set DIST=bin\example.exe

if not exist bin (
    mkdir bin
)

g++ %FILES% -o %DIST%

if %errorlevel% neq 0 (
    echo Ошибка компиляции
    pause
    exit /b
)

%DIST%

pause
