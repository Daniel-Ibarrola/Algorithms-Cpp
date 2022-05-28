//
// Created by daniel on 27/05/22.
//

#include "gtest/gtest.h"
#include "Hashing/substring.h"

TEST(TestSubstring, PolyHash)
{
    long long multiplier {263};
    long long prime {1000000007};
    long long hash {polyHash("world", prime, multiplier)};
    EXPECT_EQ(hash % 5, 4);

    hash = polyHash("Hell0", prime, multiplier);
    EXPECT_EQ(hash % 5, 4);

    hash = polyHash("GooD", prime, multiplier);
    EXPECT_EQ(hash % 5, 2);

    hash = polyHash("luck", prime, multiplier);
    EXPECT_EQ(hash % 5, 2);
}

TEST(TestSubstring, PrecoumputeHashes)
{
    std::string text {"world"};
    std::string pattern {"orl"};
    long long multiplier {263};
    long long prime {1000000007};
    std::vector<long long> hashes {precomputeHashes(text, static_cast<int>(pattern.size()),
                                                    prime, multiplier)};
    std::vector<long long> expected {7914578, 7500345, 6945418};

    EXPECT_EQ(hashes, expected);
}

TEST(TestSubstring, EmptyString)
{
    std::string text {"Hello World"};
    std::vector<int> positions {searchSubstring(text, "")};
    EXPECT_EQ(positions.empty(), true);
}

TEST(TestSubstring, PatternLargerThanText)
{
    std::string text {"banana"};
    std::string pattern {"banana-split"};
    std::vector<int> positions {searchSubstring(text, pattern)};
    EXPECT_EQ(positions.empty(), true);
}

TEST(TestSubstring, PatternEqualsText)
{
    std::string text {"Hello World"};
    std::string pattern {"Hello World"};
    std::vector<int> positions {searchSubstring(text, pattern)};
    std::vector<int> expected {0};
    EXPECT_EQ(positions, expected);
}

TEST(TestSubstring, PatternPositions)
{
    std::string text_1 {"world"};
    std::string pattern_1 {"orl"};
    std::vector<int> positions_1 {searchSubstring(text_1, pattern_1)};
    std::vector<int> expected_1 {1};
    ASSERT_EQ(positions_1, expected_1);

    std::string text {"abacaba"};
    std::string pattern {"aba"};
    std::vector<int> positions {searchSubstring(text, pattern)};
    std::vector<int> expected {0, 4};
    EXPECT_EQ(positions, expected);

    text = "testTesttesT";
    pattern = "Test";
    positions = searchSubstring(text, pattern);
    expected = {4};
    EXPECT_EQ(positions, expected);

    text = "baaaaaaa";
    pattern = "aaaaa";
    positions = searchSubstring(text, pattern);
    expected = {1, 2, 3};
    EXPECT_EQ(positions, expected);

    text = "banana";
    pattern = "ana";
    positions = searchSubstring(text, pattern);
    expected = {1, 3};
    EXPECT_EQ(positions, expected);

    text = "My dog ate all the pizza.";
    pattern = "dog";
    positions = searchSubstring(text, pattern);
    expected = {3};
    EXPECT_EQ(positions, expected);

    text = "Hello book duck table duck cellphone duck";
    pattern = "duck";
    positions = searchSubstring(text, pattern);
    expected = {11, 22, 37};
    EXPECT_EQ(positions.size(), 3);
}