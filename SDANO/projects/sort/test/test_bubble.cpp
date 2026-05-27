#include <gtest/gtest.h>
#include "bubble_sort.hpp"
#include <vector>

TEST(BubbleSortTest, SortsCorrectly)
{
    std::vector<int> v = {4, 2, 3, 1};
    bubbleSort(v);
    std::vector<int> expected = {1, 2, 3, 4};
    EXPECT_EQ(v, expected);
}
