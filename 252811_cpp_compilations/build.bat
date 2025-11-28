@echo off
chcp 65001 > nul
echo Компиляция программы...
g++ -o obywaha.exe main.cpp menu_functions.cpp
if %errorlevel% == 0 (
    echo Программа успешно скомпилирована!
) else (
    echo Ошибка компиляции!
    pause
)