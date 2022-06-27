//
// Created by daniel on 20/06/22.
//
#include <algorithm>
#include "gtest/gtest.h"
#include "SuffixTrees/suffix_tree.h"

TEST(SuffixTreeNode, TestNode)
{
    TreeNode node(1, 4);
    ASSERT_EQ(node.start(), 1);
    ASSERT_EQ(node.end(), 4);
    ASSERT_EQ(node.hasChildren(), false);

    node.addChild(2);
    node.addChild(3);
    std::vector<int> children {2, 3};
    ASSERT_EQ(node.getChildren(), children);
}

TEST(SuffixTree, CreateEmptyTree)
{
    SuffixTree tree;
    ASSERT_EQ(tree.numNodes(), 1);
    ASSERT_EQ(tree.numEdges(), 0);
}

TEST(SuffixTrees, TextWithNoRepeatedCharacters)
{
    std::string text {"barco"};
    SuffixTree tree(text);
    std::vector<int> children {1, 2, 3, 4, 5};
    ASSERT_EQ(tree.numNodes(), 6);
    ASSERT_EQ(tree.numEdges(), 5);
    ASSERT_EQ(tree.getNode(0).getChildren(), children);

    ASSERT_EQ(tree.getNode(1).start(), 4);
    ASSERT_EQ(tree.getNode(1).end(), 4);
    ASSERT_EQ(tree.getNode(1).hasChildren(), false);

    ASSERT_EQ(tree.getNode(2).start(), 3);
    ASSERT_EQ(tree.getNode(2).end(), 4);
    ASSERT_EQ(tree.getNode(2).hasChildren(), false);

    ASSERT_EQ(tree.getNode(3).start(), 2);
    ASSERT_EQ(tree.getNode(3).end(), 4);
    ASSERT_EQ(tree.getNode(3).hasChildren(), false);

    ASSERT_EQ(tree.getNode(4).start(), 1);
    ASSERT_EQ(tree.getNode(4).end(), 4);
    ASSERT_EQ(tree.getNode(4).hasChildren(), false);

    ASSERT_EQ(tree.getNode(5).start(), 0);
    ASSERT_EQ(tree.getNode(5).end(), 4);
    ASSERT_EQ(tree.getNode(5).hasChildren(), false);
}

TEST(SuffixTrees, BuildSmallTree)
{
    std::string text {"babaa$"};
    SuffixTree tree(text);
    ASSERT_EQ(tree.numNodes(), 9);
    ASSERT_EQ(tree.numEdges(), 8);

    std::vector<int> children {1, 2, 6};
    ASSERT_EQ(tree.getNode(0).getChildren(), children);

    ASSERT_EQ(tree.getNode(1).hasChildren(), false);
    ASSERT_EQ(tree.getNode(1).start(), 5);
    ASSERT_EQ(tree.getNode(1).end(), 5);

    children = {3, 4, 5};
    ASSERT_EQ(tree.getNode(2).getChildren(), children);
    ASSERT_EQ(tree.getNode(2).start(), 4);
    ASSERT_EQ(tree.getNode(2).end(), 4);

    ASSERT_EQ(tree.getNode(3).hasChildren(), false);
    ASSERT_EQ(tree.getNode(3).start(), 5);
    ASSERT_EQ(tree.getNode(3).end(), 5);

    ASSERT_EQ(tree.getNode(4).hasChildren(), false);
    ASSERT_EQ(tree.getNode(4).start(), 4);
    ASSERT_EQ(tree.getNode(4).end(), 5);

    ASSERT_EQ(tree.getNode(5).hasChildren(), false);
    ASSERT_EQ(tree.getNode(5).start(), 2);
    ASSERT_EQ(tree.getNode(5).end(), 5);

    children = {7, 8};
    ASSERT_EQ(tree.getNode(6).getChildren(), children);
    ASSERT_EQ(tree.getNode(6).start(), 2);
    ASSERT_EQ(tree.getNode(6).end(), 3);

    ASSERT_EQ(tree.getNode(7).hasChildren(), false);
    ASSERT_EQ(tree.getNode(7).start(), 4);
    ASSERT_EQ(tree.getNode(7).end(), 5);

    ASSERT_EQ(tree.getNode(8).hasChildren(), false);
    ASSERT_EQ(tree.getNode(8).start(), 2);
    ASSERT_EQ(tree.getNode(8).end(), 5);
}

TEST(SuffixTrees, FindSuffixInTree)
{
    std::string text_1 {"A$"};
    SuffixTree tree_1("A$");
    std::vector<std::string> suffixes_1 {tree_1.getAllSuffixes(text_1)};
    ASSERT_EQ(tree_1.numNodes(), 3);
    ASSERT_EQ(tree_1.numEdges(), 2);
    ASSERT_NE(std::find(suffixes_1.begin(), suffixes_1.end(), "A$"), suffixes_1.end());
    ASSERT_NE(std::find(suffixes_1.begin(), suffixes_1.end(), "$"), suffixes_1.end());

    std::string text_2 {"ACA$"};
    SuffixTree tree_2("ACA$");
    std::vector<std::string> suffixes_2 {tree_2.getAllSuffixes(text_2)};
    ASSERT_EQ(tree_2.numNodes(), 6);
    ASSERT_EQ(tree_2.numEdges(), 5);
    ASSERT_EQ(suffixes_2.size(), 5);
    ASSERT_NE(std::find(suffixes_2.begin(), suffixes_2.end(), "A"), suffixes_2.end());
    ASSERT_NE(std::find(suffixes_2.begin(), suffixes_2.end(), "$"), suffixes_2.end());
    ASSERT_NE(std::find(suffixes_2.begin(), suffixes_2.end(), "CA$"), suffixes_2.end());

    std::string text_3 {"ATAAATG$"};
    SuffixTree tree_3(text_3);
    std::vector<std::string> suffixes_3 {tree_3.getAllSuffixes(text_3)};
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

