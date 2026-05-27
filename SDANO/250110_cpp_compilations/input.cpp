#include <iostream>
#include <vector>
#include "input.h"

std::vector<int> input_numbers() {
    int n;
    std::cout << "Введите количество чисел: ";
    std::cin >> n;

    std::vector<int> arr(n);
    std::cout << "Введите числа через пробел: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    return arr;
}