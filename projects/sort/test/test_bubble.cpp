#include "bubble_sort.hpp"
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v = {4, 2, 3, 1};
    bubbleSort(v);

    for (int x : v)
        std::cout << x << " ";

    return 0;
}
