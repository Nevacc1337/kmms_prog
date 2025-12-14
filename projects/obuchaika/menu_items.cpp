#include <iostream>
#include "menu_items.hpp"

namespace dsv
{
    void showMainMenu()
    {
        std::cout << "\n=== ОБУЧАЙКА ===\n";
        std::cout << "1 - Хочу учиться математике\n";
        std::cout << "0 - Я лучше пойду полежу\n";
        std::cout << "Выбор: ";
    }

    void showMathMenu()
    {
        std::cout << "\n=== МАТЕМАТИКА ===\n";
        std::cout << "1 - Алгебра\n";
        std::cout << "2 - Матан\n";
        std::cout << "0 - Назад\n";
        std::cout << "Выбор: ";
    }

    void showAlgebraMenu()
    {
        std::cout << "\n=== АЛГЕБРА ===\n";
        std::cout << "1 - Умножать\n";
        std::cout << "2 - Складывать\n";
        std::cout << "3 - Делить\n";
        std::cout << "4 - Вычитать\n";
        std::cout << "0 - Назад\n";
        std::cout << "Выбор: ";
    }

    void showMatanMenu()
    {
        std::cout << "\n=== МАТАН ===\n";
        std::cout << "1 - Дифференциальное исчисление\n";
        std::cout << "2 - Интегральное исчисление\n";
        std::cout << "0 - Назад\n";
        std::cout << "Выбор: ";
    }
}
