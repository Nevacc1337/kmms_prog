#include <iostream>
#include <vector>
#include "input.h"
#include "sort.h"
#include "output.h"

int main() {
    std::vector<int> numbers = input_numbers();
    sort_numbers(numbers);
    output_numbers(numbers);
    return 0;
}