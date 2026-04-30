#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "shell_sorting.hpp"

TEST(ShellSortTest, AnyElementsCount) {
    int* actual = new int[]{1, 8, 2, 5, 3, 11};
    gpi::shell_sort(actual, 6); 
    int* expected = new int[]{1, 5, 3, 2, 8, 11};


    for (int i = 0; i < 6; i++) {
        ASSERT_EQ(expected[i], actual[i]) 
            << "Массив ожидаемый и отсортированный отличаются в элементе с индексом "
            << i;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}