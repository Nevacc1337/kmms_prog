@echo off
chcp 65001 > nul

if not exist build (
    mkdir build
)

cd build
cmake ..
cmake --build .

echo.
echo ===== ЗАПУСК ОБУЧАЙКИ =====
cd obuchaika
obuchaika.exe

pause
