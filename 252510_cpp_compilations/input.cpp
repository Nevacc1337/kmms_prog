#include <iostream>
#include "input.h"

namespace dsv
{
    namespace input
    {
        void readArray(double* arr, int size)
        {
            for (int i = 0; i < size; i++)
            {
                std::cout << "Введите элемент [" << i + 1 << "]: ";
                std::cin >> arr[i];

                if (!std::cin)
                {
                    std::cerr << "Ошибка: введено не число!" << std::endl;
                    std::exit(1);
                }
            }
        }
    }
}