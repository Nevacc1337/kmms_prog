#pragma once
#include "menu.hpp"

namespace dsv {
    // Первый 
    extern const MenuItem MAIN;
    extern const MenuItem ART_RUSSIA;     // 1 - выбор искусства 
    extern const MenuItem EXIT;           // стоп проги 

    // Второй 
    extern const MenuItem MAIN_MENU;      // 0 бэкаемся на узлы
    extern const MenuItem PAINTERS;       // 1 художники
    extern const MenuItem MUSICIANS;      // 2 музыканты

    // Третий — Художники
    extern const MenuItem GO_BACK_PAINTERS; // бэк на второй уровень 
    extern const MenuItem RUBLEV;
    extern const MenuItem POLENOV;
    extern const MenuItem AIVAZOVSKY;
}