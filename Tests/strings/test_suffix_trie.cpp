//
// Created by daniel on 25/06/22.
//

#include "gtest/gtest.h"
#include "SuffixTrees/suffix_trie.h"

TEST(SuffixTrieNode, TestNode)
{
    Node node('c');
    ASSERT_EQ(node.getKey(), 'c');
    ASSERT_EQ(node.getChildren().empty(), true);
    ASSERT_EQ(node.hasChildren(), false);

    node.addChild(1);
    node.addChild(2);
    std::vector<int> children {1, 2};
    ASSERT_EQ(node.hasChildren(), true);
    ASSERT_EQ(node.getChildren(), children);
}


TEST(SuffixTrie, EmptyTree)
{
    SuffixTrie trie;
    ASSERT_EQ(trie.numNodes(), 1);
    ASSERT_EQ(trie.numEdges(), 0);
    ASSERT_EQ(trie.hasChildren(0), false);
    ASSERT_EQ(trie.getChildren(0).empty(), true);
}

TEST(SuffixTrie, BuildSmallTrie)
{
    SuffixTrie trie("aa$");
    ASSERT_EQ(trie.numNodes(), 6);
    ASSERT_EQ(trie.numEdges(), 5);

    ASSERT_EQ(trie.getKey(1), '$');
    ASSERT_EQ(trie.getKey(2), 'a');
    ASSERT_EQ(trie.getKey(3), '$');
    ASSERT_EQ(trie.getKey(4), 'a');
    ASSERT_EQ(trie.getKey(5), '$');
}

TEST(SuffixTrie, BuildSuffixTrie)
{
    SuffixTrie trie("ababaa$");
    ASSERT_EQ(trie.numNodes(), 22);
    ASSERT_EQ(trie.numEdges(), 21);

    // Root Node
    std::vector<int> root_children {1, 2, 6};
    ASSERT_EQ(trie.getChildren(0), root_children);
    // Node 1
    ASSERT_EQ(trie.getKey(1), '$');
    ASSERT_EQ(trie.hasChildren(1), false);
    // Node 2
    std::vector<int> children {3, 4, 10};
    ASSERT_EQ(trie.getKey(2), 'a');
    ASSERT_EQ(trie.getChildren(2), children);
    // Node 6
    children = {7};
    ASSERT_EQ(trie.getKey(6), 'b');
    ASSERT_EQ(trie.getChildren(6), children);
    // Node 7
    children = {8, 14};
    ASSERT_EQ(trie.getKey(7), 'a');
    ASSERT_EQ(trie.getChildren(7), children);
    // Node 11
    children = {12, 18};
    ASSERT_EQ(trie.getKey(11), 'a');
    ASSERT_EQ(trie.getChildren(11), children);

}