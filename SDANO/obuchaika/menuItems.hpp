#pragma once
#include "menu.hpp"

namespace dsv {
    // Основные узлы
    extern const MenuItem MAIN;
    extern const MenuItem STUDY_CHOICE;   // "Я хочу учиться" → разделы математики
    extern const MenuItem EXIT;

    // Меню выбора разделов математики
    extern const MenuItem MAIN_MENU;      // 0 Выйти в главное меню
    extern const MenuItem ALGEBRA;
    extern const MenuItem CALCULUS;

    // Подменю Алгебры
    extern const MenuItem GO_BACK_ALGEBRA;
    extern const MenuItem POLYNOMIALS;
    extern const MenuItem EQUATIONS;

    // Подменю Матанализа
    extern const MenuItem GO_BACK_CALCULUS;
    extern const MenuItem CAUCHY_THEOREM;
    extern const MenuItem MONOTONICITY;
}