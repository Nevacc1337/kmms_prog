@echo off
chcp 65001 > nul

set EXE=program

g++ -finput-charset=utf-8 after_refactoring.cpp -o %EXE%
if errorlevel 1 (
    echo Ошибка компиляции!
    exit /b
)

echo Запуск программы...
%EXE%.exe