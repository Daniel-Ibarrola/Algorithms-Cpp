//
// Created by daniel on 19/06/22.
//

#include "gtest/gtest.h"
#include "SuffixTrees/multipattern_match.h"

TEST(MultiplePatternMatching, EmptyPatterns)
{
    std::string text {"Hello World"};
    std::vector<std::string> patterns;
    std::vector<int> expectedPositions;
    ASSERT_EQ(findPatternPositions(text, patterns), expectedPositions);

}

TEST(MultiplePatternMatching, EmptyText)
{
    std::string text;
    std::vector<std::string> patterns {"oi", "an"};
    std::vector<int> expectedPositions;
    ASSERT_EQ(findPatternPositions(text, patterns), expectedPositions);
}

TEST(MultiplePatternMatching, FindPatternPositions)
{
    std::string text {"hola"};
    std::vector<std::string> patterns {"ola"};
    std::vector<int> expectedPositions {1};
    ASSERT_EQ(findPatternPositions(text, patterns), expectedPositions);

    std::string text_2 {"panamabananas"};
    std::vector<std::string> patterns_2 {"ana", "banana"};
    std::vector<int> expectedPositions_2 {1, 6, 7, 9};
    ASSERT_EQ(findPatternPositions(text_2, patterns_2), expectedPositions_2);

    std::string text_3 {"AATCGGGTTCAATCGGGGT"};
    std::vector<std::string> patterns_3 {"ATCG", "GGGT"};
    std::vector<int> expectedPositions_3 {1, 4, 11, 15};
    ASSERT_EQ(findPatternPositions(text_3, patterns_3), expectedPositions_3);
}