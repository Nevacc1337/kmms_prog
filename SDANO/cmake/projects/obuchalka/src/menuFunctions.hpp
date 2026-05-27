#pragma once
#include "menu.hpp"

namespace dsv {
    const MenuItem* firstLevelMenu(const MenuItem* current);
    const MenuItem* secondLevelMenu(const MenuItem* current);
    const MenuItem* thirdLevelMenu(const MenuItem* current);
    const MenuItem* mainMenu(const MenuItem* current);
    const MenuItem* exit(const MenuItem* current);
    const MenuItem* goBack(const MenuItem* current);
    const MenuItem* blank(const MenuItem* current);
}