@echo off
set MAIN=main
set EXE=example
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

:build
g++ %CHARSET% %MAIN%.cpp -o %EXE%
if errorlevel 1 (
    echo Ошибка компиляции
    exit /b 1
)

:run
%EXE%.exe

:clean
del %EXE%.exe