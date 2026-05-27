#include <iostream>
#include <vector>
#include "output.h"

void output_numbers(const std::vector<int>& arr) {
    std::cout << "Отсортированные числа: ";
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}