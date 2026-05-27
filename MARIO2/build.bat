@echo off
chcp 65001 > nul

echo Сборка проекта "Mario"...

g++ -std=c++17 263004_mario.cpp -o mario.exe

if %errorlevel% neq 0 (
    echo Ошибка сборки!
    pause
    exit /b
)

echo Сборка успешно завершена.
pause