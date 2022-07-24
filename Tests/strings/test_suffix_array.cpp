//
// Created by daniel on 6/07/22.
//

#include "gtest/gtest.h"
#include "SuffixArray/count_sort.h"
#include "SuffixArray/suffix_array.h"


TEST(TestSuffixArray, ConstructSuffixArrayNaive)
{
    std::vector<int> expectedArray_1 {13, 5, 3, 1, 7, 9, 11, 6, 4, 2, 8, 10, 0, 12};
    ASSERT_EQ(expectedArray_1, suffixArrayNaive("panamabananas$"));

    std::vector<int> expectedArray_2 {3, 1, 2, 0};
    ASSERT_EQ(expectedArray_2, suffixArrayNaive("GAC$"));

    std::vector<int> expectedArray_3 {8, 7, 5, 3, 1, 6, 4, 2, 0};
    ASSERT_EQ(expectedArray_3, suffixArrayNaive("GAGAGAGA$"));

    std::vector<int> expectedArray_4 {15, 14, 0, 1, 12, 6, 4, 2, 8, 13, 3, 7, 9, 10, 11, 5};
    ASSERT_EQ(expectedArray_4, suffixArrayNaive("AACGATAGCGGTAGA$"));
}


TEST(TestSuffixArray, GetCharClasses)
{
    std::string text {"ababaa$"};
    std::vector<int> order {sortCharacters(text)};
    std::vector<int> classesExpected {1, 2, 1, 2, 1, 1, 0};
    ASSERT_EQ(classesExpected, getCharClasses(text, order));
}