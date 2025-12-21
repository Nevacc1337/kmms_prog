#include <iostream>
#include "menuItems.hpp"
#include "menuFunctions.hpp"
#include "menu.hpp"

int main(){
    const dsv::MenuItem* current = &dsv::MAIN;
    while (true){
        current = current->func(current);
    }
}