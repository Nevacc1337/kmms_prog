#include <iostream>
#include "menu_functions.hpp"
#include "menu_items.hpp"

namespace dsv
{
    void mainMenu()
    {
        int choice;
        do
        {
            showMainMenu();
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                mathMenu();
                break;
            case 0:
                std::cout << "Вы решили отдохнуть. Пока!\n";
                break;
            default:
                std::cout << "Неверный выбор!\n";
            }
        } while (choice != 0);
    }

    void mathMenu()
    {
        int choice;
        do
        {
            showMathMenu();
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                algebraMenu();
                break;
            case 2:
                matanMenu();
                break;
            case 0:
                break;
            default:
                std::cout << "Неверный выбор!\n";
            }
        } while (choice != 0);
    }

    void algebraMenu()
    {
        int choice;
        do
        {
            showAlgebraMenu();
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                std::cout << "Вы выбрали умножение.\n";
                break;
            case 2:
                std::cout << "Вы выбрали сложение.\n";
                break;
            case 3:
                std::cout << "Вы выбрали деление.\n";
                break;
            case 4:
                std::cout << "Вы выбрали вычитание.\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Неверный выбор!\n";
            }
        } while (choice != 0);
    }

    void matanMenu()
    {
        int choice;
        do
        {
            showMatanMenu();
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                std::cout << "Вы выбрали дифференциальное исчисление.\n";
                break;
            case 2:
                std::cout << "Вы выбрали интегральное исчисление.\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Неверный выбор!\n";
            }
        } while (choice != 0);
    }
}
