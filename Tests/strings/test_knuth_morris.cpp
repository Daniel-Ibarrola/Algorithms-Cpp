//
// Created by daniel on 15/07/22.
//
#include "gtest/gtest.h"
#include "KnuthMorris/prefix_function.h"


TEST(KnuthMorris, PrefixFunction)
{
    std::string text_1 {"abababcaab"};
    std::vector<int> prefix_expected_1 {0, 0, 1, 2, 3, 4, 0, 1, 1, 2};
    ASSERT_EQ(prefix_expected_1, prefixFunction(text_1));

    std::string text_2 {"abcabcabca"};
    std::vector<int> prefix_expected_2 {0, 0, 0, 1, 2, 3 ,4, 5, 6, 7};
    ASSERT_EQ(prefix_expected_2, prefixFunction(text_2));
}