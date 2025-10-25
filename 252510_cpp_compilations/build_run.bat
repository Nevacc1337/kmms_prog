@echo off
call build.bat
if exist array_analysis.exe (
    echo.
    echo Запуск программы...
    array_analysis.exe
) else (
    echo Ошибка при сборке!
)