//
// Created by daniel on 20/06/22.
//
#include <algorithm>
#include "gtest/gtest.h"
#include "SuffixTrees/suffix_tree.h"


TEST(SuffixTrees, BuildSuffixTree)
{
    SuffixTree tree_1("A$");
    std::vector<std::string> suffixes_1 {tree_1.traversal()};
    ASSERT_EQ(tree_1.numNodes(), 3);
    ASSERT_EQ(tree_1.numEdges(), 2);
    ASSERT_NE(std::find(suffixes_1.begin(), suffixes_1.end(), "A$"), suffixes_1.end());
    ASSERT_NE(std::find(suffixes_1.begin(), suffixes_1.end(), "$"), suffixes_1.end());

    SuffixTree tree_2("ACA$");
    std::vector<std::string> suffixes_2 {tree_2.traversal()};
    ASSERT_EQ(tree_2.numNodes(), 6);
    ASSERT_EQ(tree_2.numEdges(), 5);
    ASSERT_EQ(suffixes_2.size(), 5);
    ASSERT_NE(std::find(suffixes_2.begin(), suffixes_2.end(), "A"), suffixes_2.end());
    ASSERT_NE(std::find(suffixes_2.begin(), suffixes_2.end(), "$"), suffixes_2.end());
    ASSERT_NE(std::find(suffixes_2.begin(), suffixes_2.end(), "CA$"), suffixes_2.end());

    SuffixTree tree_3("ATAAATG$");
    std::vector<std::string> suffixes_3 {tree_3.traversal()};
    ASSERT_EQ(tree_3.numNodes(), 13);
    ASSERT_EQ(tree_3.numEdges(), 12);
    ASSERT_EQ(suffixes_3.size(), 12);
    ASSERT_NE(std::find(suffixes_3.begin(), suffixes_3.end(), "AAATG$"), suffixes_3.end());
    ASSERT_NE(std::find(suffixes_3.begin(), suffixes_3.end(), "G$"), suffixes_3.end());
    ASSERT_NE(std::find(suffixes_3.begin(), suffixes_3.end(), "T"), suffixes_3.end());
    ASSERT_NE(std::find(suffixes_3.begin(), suffixes_3.end(), "ATG$"), suffixes_3.end());
    ASSERT_NE(std::find(suffixes_3.begin(), suffixes_3.end(), "TG$"), suffixes_3.end());
    ASSERT_NE(std::find(suffixes_3.begin(), suffixes_3.end(), "A"), suffixes_3.end());
    ASSERT_NE(std::find(suffixes_3.begin(), suffixes_3.end(), "$"), suffixes_3.end());
}

