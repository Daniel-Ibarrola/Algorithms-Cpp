//
// Created by daniel on 6/07/22.
//

#include "gtest/gtest.h"
#include "SuffixArray/suffix_array.h"


TEST(TestSuffixArray, ConstructSuffixArray)
{
    std::vector<int> expectedArray_1 {13, 5, 3, 1, 7, 9, 11, 6, 4, 2, 8, 10, 0, 12};
    ASSERT_EQ(expectedArray_1, suffixArray("panamabananas$"));

    std::vector<int> expectedArray_2 {3, 1, 2, 0};
    ASSERT_EQ(expectedArray_2, suffixArray("GAC$"));

    std::vector<int> expectedArray_3 {8, 7, 5, 3, 1, 6, 4, 2, 0};
    ASSERT_EQ(expectedArray_3, suffixArray("GAGAGAGA$"));

    std::vector<int> expectedArray_4 {15, 14, 0, 1, 12, 6, 4, 2, 8, 13, 3, 7, 9, 10, 11, 5};
    ASSERT_EQ(expectedArray_4, suffixArray("AACGATAGCGGTAGA$"));
}

