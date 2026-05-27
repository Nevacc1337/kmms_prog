#include "menuFunctions.hpp"
#include "menuItems.hpp"

const dsv::MenuItem dsv::EXIT = {
    "0 Я уже всё знаю",
    dsv::exit
};

const dsv::MenuItem dsv::MAIN_MENU = {
    "0 Выйти в главное меню",
    dsv::mainMenu,
    &dsv::MAIN
};

// === Подменю Алгебры ===
const dsv::MenuItem dsv::POLYNOMIALS = {
    "1 Полиномы",
    dsv::blank,
    &dsv::ALGEBRA
};

const dsv::MenuItem dsv::EQUATIONS = {
    "2 Уравнения",
    dsv::blank,
    &dsv::ALGEBRA
};

const dsv::MenuItem dsv::GO_BACK_ALGEBRA = {
    "0 Вернуться в предыдущее меню",
    dsv::goBack,
    &dsv::STUDY_CHOICE
};

namespace {
    const dsv::MenuItem* const algebraChildren[] = {
        &dsv::GO_BACK_ALGEBRA,
        &dsv::POLYNOMIALS,
        &dsv::EQUATIONS
    };
    const int algebraSize = sizeof(algebraChildren) / sizeof(algebraChildren[0]);
}

const dsv::MenuItem dsv::ALGEBRA = {
    "1 Хочу изучать алгебру",
    dsv::thirdLevelMenu,
    &dsv::MAIN,
    algebraChildren,
    algebraSize
};

// === Подменю Матанализа ===
const dsv::MenuItem dsv::CAUCHY_THEOREM = {
    "1 Теорема Коши",
    dsv::blank,
    &dsv::CALCULUS
};

const dsv::MenuItem dsv::MONOTONICITY = {
    "2 Монотонность функции",
    dsv::blank,
    &dsv::CALCULUS
};

const dsv::MenuItem dsv::GO_BACK_CALCULUS = {
    "0 Вернуться в предыдущее меню",
    dsv::goBack,
    &dsv::STUDY_CHOICE
};

namespace {
    const dsv::MenuItem* const calculusChildren[] = {
        &dsv::GO_BACK_CALCULUS,
        &dsv::CAUCHY_THEOREM,
        &dsv::MONOTONICITY
    };
    const int calculusSize = sizeof(calculusChildren) / sizeof(calculusChildren[0]);
}

const dsv::MenuItem dsv::CALCULUS = {
    "2 Хочу изучать матанализ",
    dsv::thirdLevelMenu,
    &dsv::MAIN,
    calculusChildren,
    calculusSize
};

// === Меню выбора разделов (второй уровень) ===
namespace {
    const dsv::MenuItem* const studyChildren[] = {
        &dsv::MAIN_MENU,
        &dsv::ALGEBRA,
        &dsv::CALCULUS
    };
    const int studySize = sizeof(studyChildren) / sizeof(studyChildren[0]);
}

const dsv::MenuItem dsv::STUDY_CHOICE = {
    "1 Я хочу учиться",
    dsv::secondLevelMenu,
    &dsv::MAIN,
    studyChildren,
    studySize
};

// === Главное меню ===
namespace {
    const dsv::MenuItem* const mainChildren[] = {
        &dsv::EXIT,
        &dsv::STUDY_CHOICE
    };
    const int mainSize = sizeof(mainChildren) / sizeof(mainChildren[0]);
}

const dsv::MenuItem dsv::MAIN = {
    nullptr,
    dsv::firstLevelMenu,
    nullptr,
    mainChildren,
    mainSize
};