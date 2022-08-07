//
// Created by daniel on 6/08/22.
//

#include "gtest/gtest.h"
#include "SuffixTrees/suffix_tree.h"

TEST(TestSuffixTreeFromSuffixArray, CreateNewLeafNode)
{
    std::string text {"a$"};
    auto* root = new SuffixTreeNode(nullptr, 0, -1, -1);

    SuffixTreeNode* leaf_1 {SuffixTree::createNewLeaf(text, root, 1)};
    ASSERT_EQ(root->children.size(), 1);
    ASSERT_EQ(leaf_1->parent, root);
    ASSERT_EQ(leaf_1->stringDepth, 1);
    ASSERT_EQ(leaf_1->edgeStart, 1);
    ASSERT_EQ(leaf_1->edgeEnd, 1);

    SuffixTreeNode* leaf_2 {SuffixTree::createNewLeaf(text, root, 0)};
    ASSERT_EQ(root->children.size(), 2);
    ASSERT_EQ(leaf_2->parent, root);
    ASSERT_EQ(leaf_2->stringDepth, 2);
    ASSERT_EQ(leaf_2->edgeStart, 0);
    ASSERT_EQ(leaf_2->edgeEnd, 1);

    ASSERT_EQ(root->children['$'], leaf_1);
    ASSERT_EQ(root->children['a'], leaf_2);
}


TEST(TestSuffixTreeFromSuffixArray, BreakEdge)
{
    std::string text {"aa$"};
    auto* root = new SuffixTreeNode(nullptr, 0, -1, -1);
    SuffixTreeNode* leaf_1 {SuffixTree::createNewLeaf(text, root, 2)};
    SuffixTreeNode* leaf_2 {SuffixTree::createNewLeaf(text, root, 1)};

    SuffixTreeNode* midNode {SuffixTree::breakEdge(text, root, 1, 1)};
    ASSERT_EQ(midNode->children.size(), 1);
    ASSERT_EQ(midNode->stringDepth, 1);
    ASSERT_EQ(midNode->parent, root);
    ASSERT_EQ(midNode->edgeStart, 1);
    ASSERT_EQ(midNode->edgeEnd, 1);

    // Leaf 2 should be modified
    ASSERT_EQ(leaf_2->children.size(), 0);
    ASSERT_EQ(leaf_2->stringDepth, 2);
    ASSERT_EQ(leaf_2->parent, midNode);
    ASSERT_EQ(leaf_2->edgeStart, 2);
    ASSERT_EQ(leaf_2->edgeEnd, 2);

    // Leaf 1 should remain the same
    ASSERT_EQ(leaf_1->parent, root);
    ASSERT_EQ(leaf_1->stringDepth, 1);
    ASSERT_EQ(leaf_1->edgeStart, 2);
    ASSERT_EQ(leaf_1->edgeEnd, 2);
}

TEST(TestSuffixTreeFromSuffixArray, BuildTree)
{
    std::string text {"ababaa$"};
    SuffixTree tree(text);
    ASSERT_EQ(tree.numEdges(), 10);
    ASSERT_EQ(tree.numNodes(), 11);

    SuffixTreeNode* root {tree.getRoot()};
    ASSERT_EQ(root->children.size(), 3);
    ASSERT_EQ(root->children['$']->stringDepth, 1);

    // Middle node with edge label "a"
    SuffixTreeNode* midNode_1 {root->children['a']};
    ASSERT_EQ(midNode_1->children.size(), 3);
    ASSERT_EQ(midNode_1->children['$']->stringDepth, 2);
    ASSERT_EQ(midNode_1->children['a']->stringDepth, 3);
    // Middle node with edge label "ba"
    SuffixTreeNode* midNode_2 {midNode_1->children['b']};
    ASSERT_EQ(midNode_2->edgeStart, 3);
    ASSERT_EQ(midNode_2->edgeEnd, 4);
    ASSERT_EQ(midNode_2->children.size(), 2);
    ASSERT_EQ(midNode_2->children['a']->stringDepth, 5);
    ASSERT_EQ(midNode_2->children['b']->stringDepth, 7);
    // Middle node with edge label "ba". This edge goes from the root
    SuffixTreeNode* midNode_3 {root->children['b']};
    ASSERT_EQ(midNode_3->edgeStart, 3);
    ASSERT_EQ(midNode_3->edgeEnd, 4);
    ASSERT_EQ(midNode_3->children.size(), 2);
    ASSERT_EQ(midNode_3->children['a']->edgeStart, 5);
    ASSERT_EQ(midNode_3->children['b']->edgeStart, 3);

}
