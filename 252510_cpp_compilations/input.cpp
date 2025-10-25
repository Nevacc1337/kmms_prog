#include <iostream>
#include "input.h"

namespace input
{
    void readArray(double* arr, int size)
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << "Введите элемент [" << i + 1 << "]: ";
            std::cin >> arr[i];
        }
    }
}