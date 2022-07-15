//
// Created by daniel on 15/07/22.
//
#include "gtest/gtest.h"
#include "KnuthMorris/prefix_function.h"
#include "KnuthMorris/pattern_matching.h"


TEST(KnuthMorris, PrefixFunction)
{
    std::string text_1 {"abababcaab"};
    std::vector<int> prefix_expected_1 {0, 0, 1, 2, 3, 4, 0, 1, 1, 2};
    ASSERT_EQ(prefix_expected_1, prefixFunction(text_1));

    std::string text_2 {"abcabcabca"};
    std::vector<int> prefix_expected_2 {0, 0, 0, 1, 2, 3 ,4, 5, 6, 7};
    ASSERT_EQ(prefix_expected_2, prefixFunction(text_2));
}

TEST(KnuthMorris, PatternMatching)
{
    std::string pattern_1 {"abra"};
    std::string text_1 {"abracadabra"};
    std::vector<int> occurrences {0, 7};
    ASSERT_EQ(occurrences, findAllOccurrences(pattern_1, text_1));

    std::string pattern_2 {"ana"};
    std::string text_2 {"panamabananas"};
    std::vector<int> occurrences_2 {1, 7, 9};
    ASSERT_EQ(occurrences_2, findAllOccurrences(pattern_2, text_2));

    std::string pattern_3 {"AAA"};
    std::string text_3 {"A"};
    ASSERT_EQ(findAllOccurrences(pattern_3, text_3).empty(), true);

    std::string pattern_4;
    ASSERT_EQ(findAllOccurrences(pattern_4, text_3).empty(), true);
}
