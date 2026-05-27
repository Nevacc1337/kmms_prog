#include "menuFunctions.hpp"
#include "menuItems.hpp"

const dsv::MenuItem dsv::EXIT = {
    "0 Выход",
    dsv::exit
};

const dsv::MenuItem dsv::MAIN_MENU = {
    "0 Выйти в главное меню",
    dsv::mainMenu,
    &dsv::MAIN
};

const dsv::MenuItem dsv::RUBLEV = {
    "1 Андрей Иванов сын Рублёв",
    dsv::blank,
    &dsv::PAINTERS
};

const dsv::MenuItem dsv::POLENOV = {
    "2 Василий Дмитриевич Поленов",
    dsv::blank,
    &dsv::PAINTERS
};

const dsv::MenuItem dsv::AIVAZOVSKY = {
    "3 Иван Константинович Айвазовский",
    dsv::blank,
    &dsv::PAINTERS
};

const dsv::MenuItem dsv::GO_BACK_PAINTERS = {
    "0 Выйти в предыдущее меню",
    dsv::goBack,
    &dsv::ART_RUSSIA
};

namespace {
    const dsv::MenuItem* const paintersChildren[] = {
        &dsv::GO_BACK_PAINTERS,
        &dsv::RUBLEV,
        &dsv::POLENOV,
        &dsv::AIVAZOVSKY
    };
    const int paintersSize = sizeof(paintersChildren) / sizeof(paintersChildren[0]);
}

const dsv::MenuItem dsv::PAINTERS = {
    "1 Русские художники",
    dsv::thirdLevelMenu,
    &dsv::MAIN,
    paintersChildren,
    paintersSize
};

const dsv::MenuItem dsv::MUSICIANS = {
    "2 Русские музыканты",
    dsv::blank,
    &dsv::MAIN
};

namespace {
    const dsv::MenuItem* const artChildren[] = {
        &dsv::MAIN_MENU,
        &dsv::PAINTERS,
        &dsv::MUSICIANS
    };
    const int artSize = sizeof(artChildren) / sizeof(artChildren[0]);
}

const dsv::MenuItem dsv::ART_RUSSIA = {
    "1 Искусство России",
    dsv::secondLevelMenu,
    &dsv::MAIN,
    artChildren,
    artSize
};

namespace {
    const dsv::MenuItem* const mainChildren[] = {
        &dsv::EXIT,
        &dsv::ART_RUSSIA
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