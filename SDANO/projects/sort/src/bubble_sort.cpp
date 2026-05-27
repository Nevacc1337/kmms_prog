#include "bubble_sort.hpp"
#include <utility>

void bubbleSort(std::vector<int>& v)
{
    for (size_t i = 0; i < v.size(); ++i)
        for (size_t j = 0; j + 1 < v.size(); ++j)
            if (v[j] > v[j + 1])
                std::swap(v[j], v[j + 1]);
}
