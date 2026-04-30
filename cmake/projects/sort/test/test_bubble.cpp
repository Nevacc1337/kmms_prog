#include <gtest/gtest.h>
#include "bubble_sort.hpp"

TEST(BubbleSortШкола, BasicSort) {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    bubbleSort(arr);
    std::vector<int> expected = {11, 12, 22, 25, 34, 64, 90};
    EXPECT_EQ(arr, expected);
}

TEST(BubbleSortШкола, AlreadySorted) {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    bubbleSort(arr);
    EXPECT_EQ(arr, std::vector<int>({1, 2, 3, 4, 5}));
}

TEST(BubbleSortШкола, EmptyAndSingle) {
    std::vector<int> empty;
    bubbleSort(empty);
    EXPECT_TRUE(empty.empty());

    std::vector<int> single = {42};
    bubbleSort(single);
    EXPECT_EQ(single, std::vector<int>({42}));
}

TEST(BubbleSortШкола, WithDuplicates) {
    std::vector<int> arr = {5, 5, 2, 8, 2};
    bubbleSort(arr);
    EXPECT_EQ(arr, std::vector<int>({2, 2, 5, 5, 8}));
}