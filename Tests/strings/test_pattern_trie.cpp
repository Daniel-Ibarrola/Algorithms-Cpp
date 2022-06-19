//
// Created by daniel on 19/06/22.
//
#include "gtest/gtest.h"
#include "SuffixTrees/pattern_trie.h"

TEST(PatternTrie, SinglePatternConstructor)
{
    std::string emptyPattern;
    PatternTrie emptyTrie(emptyPattern);
    ASSERT_EQ(emptyTrie.numPatterns(), 1);
    ASSERT_EQ(emptyTrie.numNodes(), 1);

    std::string pattern {"hola"};
    PatternTrie trie(pattern);
    ASSERT_EQ(trie.numPatterns(), 1);
    ASSERT_EQ(trie.numNodes(), 5);

    std::vector<std::vector<int>> expectedAdjList {
            {1},
            {2},
            {3},
            {4},
            { },
    };
    std::vector<char> expectedKeys {char(0), 'h', 'o', 'l', 'a'};
    ASSERT_EQ(trie.getKeys(), expectedKeys);
    ASSERT_EQ(trie.getAdjacencyList(), expectedAdjList);

    std::string pattern_2 {"ATA"};
    PatternTrie trie_2 (pattern_2);
    ASSERT_EQ(trie_2.numNodes(), 4);

    std::vector<std::vector<int>> expectedAdjList_2 {
            {1},
            {2},
            {3},
            { },
    };
    std::vector<char> expectedKeys_2 {char(0), 'A', 'T', 'A'};
}

TEST(PatternTrie, MultiplePatternConstructor)
{
    std::vector<std::string> patterns {"bola", "bomba", "bolo"};
    PatternTrie trie(patterns);
    ASSERT_EQ(trie.numPatterns(), 3);
    ASSERT_EQ(trie.numNodes(), 9);
    std::vector<std::vector<int>> expectedAdjList {
            {1},
            {2},
            {3, 5},
            {4, 8},
            { },
            {6},
            {7},
            { },
            { },
    };
    std::vector<char> expectedKeys
            {char(0), 'b', 'o', 'l', 'a', 'm', 'b', 'a', 'o'};
    ASSERT_EQ(trie.getKeys(), expectedKeys);
    ASSERT_EQ(trie.getAdjacencyList(), expectedAdjList);

    std::vector<std::string> patterns_2 {"AT", "AG", "AC"};
    PatternTrie trie_2 (patterns_2);
    ASSERT_EQ(trie_2.numNodes(), 5);
    ASSERT_EQ(trie_2.numPatterns(), 3);
    std::vector<std::vector<int>> expectedAdjList_2 {
            {1},
            {2, 3, 4},
            { },
            { },
            { },
    };
    std::vector<char> expectedKeys_2 {char(0), 'A', 'T', 'G', 'C'};
    ASSERT_EQ(trie_2.getAdjacencyList(), expectedAdjList_2);
    ASSERT_EQ(trie_2.getKeys(), expectedKeys_2);

    std::vector<std::string> patterns_3 {"ATAGA", "ATC", "GAT"};
    PatternTrie trie_3 (patterns_3);
    ASSERT_EQ(trie_3.numNodes(), 10);
    ASSERT_EQ(trie_3.numPatterns(), 3);
    std::vector<std::vector<int>> expectedAdjList_3 {
            {1, 7},
            {2},
            {3, 6},
            {4},
            {5},
            { },
            { },
            {8},
            {9},
            { },
    };
    std::vector<char> expectedKeys_3
        {char(0), 'A', 'T', 'A', 'G', 'A', 'C', 'G', 'A', 'T'};
    ASSERT_EQ(trie_3.getAdjacencyList(), expectedAdjList_3);
    ASSERT_EQ(trie_3.getKeys(), expectedKeys_3);

}

