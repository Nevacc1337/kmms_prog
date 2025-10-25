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

    double* data = new double[size];

    input::readArray(data, size);

    double avg = analysis::average(data, size);
    double minValue = analysis::minimum(data, size);
    double maxValue = analysis::maximum(data, size);
    bool increasing = analysis::isIncreasing(data, size);

    sort::bubbleSort(data, size);

    output::showResults(data, size, avg, minValue, maxValue, increasing);

    delete[] data;
    return 0;
}