@echo off
chcp 65001 > nul
set EXE=array_analysis

g++ -finput-charset=utf-8 -fexec-charset=utf-8 main.cpp input.cpp analysis.cpp sort.cpp output.cpp -o %EXE%

echo Сборка завершена!