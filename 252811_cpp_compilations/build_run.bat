@echo off
chcp 65001 > nul
echo Компиляция программы...
g++ -o obychalka.exe main.cpp menu_functions.cpp

if %errorlevel% == 0 (
    echo Программа успешно скомпилирована!
    echo.
    echo Запуск программы...
    echo.
    obychalka.exe
) else (
    echo Ошибка компиляции!
    pause
)