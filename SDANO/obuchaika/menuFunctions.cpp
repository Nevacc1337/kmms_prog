#include <iostream>
#include "menuFunctions.hpp"
#include "menu.hpp"

namespace {
    const dsv::MenuItem* showElements(const dsv::MenuItem* current){
        for (int i = 1; i < current->childrenCount; i++){
            std::cout << current->children[i]->title << std::endl;
        }
        std::cout << current->children[0]->title << std::endl;
        int userInput;
        std::cin >> userInput;
        return current->children[userInput];
    }
}

const dsv::MenuItem* dsv::secondLevelMenu(const dsv::MenuItem* current){
    std::cout << "Второй уровень меню:" << std::endl;
    return showElements(current);
}

const dsv::MenuItem* dsv::firstLevelMenu(const dsv::MenuItem* current){
    std::cout << "Главное меню:" << std::endl;
    return showElements(current);
}

const dsv::MenuItem* dsv::thirdLevelMenu(const dsv::MenuItem* current){
    std::cout << "Третий уровень меню:" << std::endl;
    return showElements(current);
}

const dsv::MenuItem* dsv::exit(const dsv::MenuItem* current){
    std::exit(0);
    return current;
}

const dsv::MenuItem* dsv::goBack(const dsv::MenuItem* current){
    return current->parent;
}

const dsv::MenuItem* dsv::mainMenu(const dsv::MenuItem* current){
    return current->parent;
}

const dsv::MenuItem* dsv::blank(const dsv::MenuItem* current){
    return current->parent;
}