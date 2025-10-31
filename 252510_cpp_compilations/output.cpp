#include <iostream>
#include "output.h"

namespace dsv
{
    namespace output
    {
        void showResults(const double* arr, int size, double avg, double minVal, double maxVal, bool increasing)
        {
            std::cout << "\n=== Результаты анализа ===" << std::endl;
            std::cout << "Среднее значение: " << avg << std::endl;
            std::cout << "Минимум: " << minVal << std::endl;
            std::cout << "Максимум: " << maxVal << std::endl;
            std::cout << "Последовательность: " << (increasing ? "возрастающая" : "не возрастающая") << std::endl;

            std::cout << "\nОтсортированный массив: ";
            for (int i = 0; i < size; i++)
            {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }
    }
}
