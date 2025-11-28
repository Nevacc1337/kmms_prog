#include <clocale>
#include <iostream>

#include "menu.hpp"
#include "menu_functions.hpp"

int main() {
    std::setlocale(LC_ALL, "");

    // ПУНКТЫ МЕНЮ МАТЕМАТИКИ (уровень 2)
    SDurnev::MenuItem study_sum = { "1 - Хочу учиться сложению!", SDurnev::study_sum };
    SDurnev::MenuItem study_subtract = { "2 - Хочу учиться вычитанию!", SDurnev::study_subtract };
    SDurnev::MenuItem study_multiply = { "3 - Хочу учиться умножению!", SDurnev::study_multiply };
    SDurnev::MenuItem study_divide = { "4 - Хочу учиться делению!", SDurnev::study_divide };
    SDurnev::MenuItem study_math_back = { "0 - Вернуться назад", SDurnev::study_math_back };

    SDurnev::MenuItem* study_children[] = {
        &study_math_back,
        &study_sum,
        &study_subtract, 
        &study_multiply,
        &study_divide
    };
    const int study_size = sizeof(study_children) / sizeof(study_children[0]);

    // Функция для меню математики
    auto study_math_menu = [&]() {
        int math_choice;
        do {
            std::cout << "\n=== МАТЕМАТИКА ===" << std::endl;
            for (int i = 1; i < study_size; i++) {
                std::cout << study_children[i]->title << std::endl;
            }
            std::cout << study_children[0]->title << std::endl;
            std::cout << "Математика > ";
            std::cin >> math_choice;
            
            if (math_choice == 0) break;
            if (math_choice >= 1 && math_choice < study_size) {
                study_children[math_choice]->func();
            }
            std::cout << std::endl;
        } while (true);
    };

    // ГЛАВНОЕ МЕНЮ (уровень 1)
    SDurnev::MenuItem study = { "1 - Хочу учиться математике!", study_math_menu };
    SDurnev::MenuItem exit = { "0 - Я лучше пойду полежу...", SDurnev::exit };

    SDurnev::MenuItem* main_children[] = { &exit, &study };
    const int main_size = sizeof(main_children) / sizeof(main_children[0]);

    // ОСНОВНОЙ ЦИКЛ
    int user_input;
    do {
        std::cout << "Обучайка приветствует тебя, мой юный ученик!" << std::endl;
        for (int i = 1; i < main_size; i++) {
            std::cout << main_children[i]->title << std::endl;
        }
        std::cout << main_children[0]->title << std::endl;
        std::cout << "Обучайка > ";
        std::cin >> user_input;
        
        if (user_input >= 0 && user_input < main_size) {
            main_children[user_input]->func();
        }
        std::cout << std::endl;
    } while (true);

    return 0;
}