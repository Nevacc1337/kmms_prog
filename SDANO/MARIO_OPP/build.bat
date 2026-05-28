@echo off
g++ -std=c++17 mario.cpp -o mario.exe
if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b
)
echo Build OK.
pause