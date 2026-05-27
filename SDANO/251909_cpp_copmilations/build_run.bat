@echo off
chcp 65001 > nul

set MAIN=main
set EXE=example
set CHARSET=-finput-charset=utf-8

g++ %CHARSET% %MAIN%.cpp -o %EXE%
if errorlevel 1 (
    echo Ошибка компиляции!
    exit /b
)

%EXE%.exe