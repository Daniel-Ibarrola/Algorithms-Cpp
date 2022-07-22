//
// Created by daniel on 22/07/22.
//

#include "gtest/gtest.h"
#include "SuffixArray/count_sort.h"

TEST(CountSortTest, SortArrayOfInt)
{
    std::vector<int> array {4, 2, 2, 8, 3, 3, 1};
    std::vector<int> sortedExpected {1, 2, 2, 3, 3, 4, 8};
    ASSERT_EQ(countSort(array), sortedExpected);
}


TEST(CountSortTest, SortCharacters)
{
    std::string text {"ababaa$"};
    std::vector<int> orderExpected {6, 0, 2, 4, 5, 1, 3};
    ASSERT_EQ(sortCharacters(text), orderExpected);
}