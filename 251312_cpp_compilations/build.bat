@echo off
chcp 65001 > nul
REM 650111

echo Сборка проекта "Обучайка"...

g++ -std=c++17 ^
    main.cpp ^
    menu_functions.cpp ^
    menu_items.cpp ^
    -o obuchaika.exe

if %errorlevel% neq 0 (
    echo Ошибка сборки!
    pause
    exit /b
)

echo Сборка успешно завершена.
pause

