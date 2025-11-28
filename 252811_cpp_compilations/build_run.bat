@echo off
chcp 65001 > nul
echo Компиляция программы...
g++ -o obywaha.exe main.cpp

if %errorlevel% == 0 (
    echo Программа успешно скомпилирована!
    echo.
    echo Запуск программы...
    echo.
    obywaha.exe
) else (
    echo Ошибка компиляции!
    pause
)