#include <iostream>
#include "menu_items.hpp"

namespace dsv
{
    void showMainMenu()
    {
        std::cout << "\n=== ОБУЧАЙКА ===\n";
        std::cout << "1 - Хочу учиться математике\n";
        std::cout << "0 - Я лучше пойду полежу\n";
        std::cout << "Ваш выбор: ";
    }

    void showMathMenu()
    {
        std::cout << "\n=== МАТЕМАТИКА ===\n";
        std::cout << "1 - Алгебра\n";
        std::cout << "2 - Матан\n";
        std::cout << "0 - Выйти в меню\n";
        std::cout << "Ваш выбор: ";
    }

    void showAlgebraMenu()
    {
        std::cout << "\n=== АЛГЕБРА ===\n";
        std::cout << "1 - Хочу умножать\n";
        std::cout << "2 - Хочу складывать\n";
        std::cout << "3 - Хочу делить\n";
        std::cout << "4 - Хочу вычитать\n";
        std::cout << "0 - Вернуться к выбору предметов\n";
        std::cout << "Ваш выбор: ";
    }

    void showMatanMenu()
    {
        std::cout << "\n=== МАТАН ===\n";
        std::cout << "1 - Дифференциальное исчисление\n";
        std::cout << "2 - Интегральное исчисление\n";
        std::cout << "0 - Вернуться к выбору предметов\n";
        std::cout << "Ваш выбор: ";
    }
}
