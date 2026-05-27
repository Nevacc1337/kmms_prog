#include <iostream>
#include "input.h"
#include "analysis.h"
#include "sort.h"
#include "output.h"

int main()
{
    std::cout << "=== Анализ массива чисел ===" << std::endl;

    int size = 0;
    std::cout << "Введите количество элементов: ";
    std::cin >> size;

    if (!std::cin || size <= 0)
    {
        std::cerr << "Ошибка: размер массива должен быть положительным числом!" << std::endl;
        return 1;
    }

    double* data = new double[size];

    dsv::input::readArray(data, size);

    double avg = dsv::analysis::average(data, size);
    double minValue = dsv::analysis::minimum(data, size);
    double maxValue = dsv::analysis::maximum(data, size);
    bool increasing = dsv::analysis::isIncreasing(data, size);

    dsv::sort::bubbleSort(data, size);

    dsv::output::showResults(data, size, avg, minValue, maxValue, increasing);

    delete[] data;
    return 0;
}
