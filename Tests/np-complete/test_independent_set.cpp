//
// Created by daniel on 12/10/22.
//

#include "independent_set/independent_set.h"
#include "gtest/gtest.h"


TEST(TreeNodeTest, CreateNode)
{
    TreeNode node(5);
    ASSERT_EQ(node.getWeight(), 5);
    ASSERT_FALSE(node.hasChildren());
}


TEST(TreeNodeTest, AddChildToNode)
{
    TreeNode node(5);
    ASSERT_FALSE(node.hasChildren());

    node.addChild(1);
    ASSERT_TRUE(node.hasChildren());
}


class WeightedTreeTest : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    int numNodes {5};
    std::vector<int> weights_1 {1, 5, 3, 7, 5};
    std::vector<std::pair<int, int>> nodes_1 {
            {4, 5},
            {2, 3},
            {2, 4},
            {1, 2},
    };
    WeightedTree tree_1{numNodes, nodes_1, weights_1};

    std::vector<int> weights_2 {3, 5, 1, 6, 2, 3, 7, 2, 1, 2, 1};
    std::vector<std::pair<int, int>> nodes_2{
            {1, 2},
            {1, 3},
            {1, 4},
            {2, 5},
            {3, 6},
            {4, 7},
            {4, 8},
            {7, 9},
            {7, 10},
            {7, 11},
    };
    WeightedTree tree_2{11, nodes_2, weights_2};
};


TEST_F(WeightedTreeTest, CreateTreeFromList)
{
    ASSERT_EQ(tree_1.size(), 5);
}


TEST_F(WeightedTreeTest, TreeNodes)
{
    std::vector<TreeNode> nodes {tree_1.getNodes()};
    ASSERT_EQ(nodes.size(), 5);

    // Test weights are correct
    ASSERT_EQ(nodes[0].getWeight(), 1);
    ASSERT_EQ(nodes[1].getWeight(), 5);
    ASSERT_EQ(nodes[2].getWeight(), 3);
    ASSERT_EQ(nodes[3].getWeight(), 7);
    ASSERT_EQ(nodes[4].getWeight(), 5);

    // Test children are correct
    std::vector<int> children_0 {1};
    std::vector<int> children_1 {2, 3};
    std::vector<int> children_3 {4};
    ASSERT_EQ(nodes[0].getChildren(), children_0);
    ASSERT_EQ(nodes[1].getChildren(), children_1);
    ASSERT_EQ(nodes[3].getChildren(), children_3);
    ASSERT_TRUE(nodes[2].getChildren().empty());
    ASSERT_TRUE(nodes[4].getChildren().empty());
}


TEST_F(WeightedTreeTest, MaxIndependentSetWeight)
{
    ASSERT_EQ(tree_1.maxISWeight(), 11);
    ASSERT_EQ(tree_2.maxISWeight(), 18);
}