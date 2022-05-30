//
// Created by daniel on 29/05/22.
//

#include "gtest/gtest.h"
#include "Graph/adjacency_list.h"
#include <vector>

TEST(AdjacencyListGraph, EmptyConstructor)
{
    ListGraph g;
    EXPECT_EQ(g.numNodes(), 0);
    EXPECT_EQ(g.numEdges(), 0);
}

TEST(AdjacencyListGraph, NumberOfNodesConstructor)
{
    ListGraph g(5);
    EXPECT_EQ(g.numNodes(), 5);
    EXPECT_EQ(g.numEdges(), 0);
}

TEST(AdjacencyListGraph, AddNode)
{
    // Test with an empty graph
    ListGraph g;
    g.addNode();
    EXPECT_EQ(g.numNodes(), 1);

    // Test with a non-empty graph
    ListGraph j(3);
    j.addNode();
    EXPECT_EQ(j.numNodes(), 4);
}

TEST(AdjacencyListGraph, IsEdgeAndAddEdge)
{
    ListGraph g(3);
    EXPECT_EQ(g.isEdge(0, 1), false);
    EXPECT_EQ(g.isEdge(1, 0), false);

    EXPECT_EQ(g.isEdge(0, 2), false);
    EXPECT_EQ(g.isEdge(2, 0), false);

    ListGraph j(3);
    j.addEdge(0, 2);
    j.addEdge(0, 1);
    j.addEdge(1, 2);
    ASSERT_EQ(j.numEdges(), 3);

    EXPECT_EQ(j.isEdge(0, 1), true);
    EXPECT_EQ(j.isEdge(1, 0), true);

    EXPECT_EQ(j.isEdge(0, 2), true);
    EXPECT_EQ(j.isEdge(2, 0), true);

    EXPECT_EQ(j.isEdge(1, 2), true);
    EXPECT_EQ(j.isEdge(2, 1), true);

}

TEST(AdjacencyListGraph, AddAlreadyPresentEdge)
{
    ListGraph j(3);
    j.addEdge(0, 2);
    j.addEdge(0, 1);
    j.addEdge(1, 2);
    ASSERT_EQ(j.numEdges(), 3);

    // Adding an already present edge should not change the graph
    j.addEdge(0, 1);
    j.addEdge(0, 1);
    EXPECT_EQ(j.numEdges(), 3);
    EXPECT_EQ(j.isEdge(0, 1), true);
    EXPECT_EQ(j.isEdge(1, 0), true);
}

class AdjacencyListGraphFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // graph_1 has one connected component
        graph_1.addEdge(0, 1);
        graph_1.addEdge(0, 2);
        graph_1.addEdge(0, 3);
        graph_1.addEdge(0, 4);
        graph_1.addEdge(0, 6);
        graph_1.addEdge(0, 7);
        graph_1.addEdge(1, 2);
        graph_1.addEdge(1, 4);
        graph_1.addEdge(2, 3);
        graph_1.addEdge(3, 8);
        graph_1.addEdge(4, 5);
        graph_1.addEdge(4, 8);
        graph_1.addEdge(5, 6);
        graph_1.addEdge(6, 7);

        // c4 has one connected component
        c4.addEdge(0, 1);
        c4.addEdge(0, 2);
        c4.addEdge(1, 3);
        c4.addEdge(2, 3);

        // graph_2 has two connected components
        graph_2.addEdge(0, 1);
        graph_2.addEdge(1, 2);

        // graph_3 has two connected components
        graph_3.addEdge(0, 1);
        graph_3.addEdge(0, 2);
        graph_3.addEdge(1, 2);
        graph_3.addEdge(3, 4);

        // graph_4 has three connected components
        graph_4.addEdge(0, 1);
        graph_4.addEdge(0, 2);
        graph_4.addEdge(1, 2);
        graph_4.addEdge(3, 4);
        graph_4.addEdge(5, 6);
        graph_4.addEdge(6, 7);
    }

    ListGraph graph_1{9};
    ListGraph c4 {4};
    ListGraph graph_2 {4};
    ListGraph graph_3 {5};
    ListGraph graph_4{8};
};

TEST_F(AdjacencyListGraphFixture, NumberOfNeighbors)
{
    EXPECT_EQ(graph_1.numEdges(), 14);
    EXPECT_EQ(graph_1.numNeighbors(0), 6);
    EXPECT_EQ(graph_1.numNeighbors(1), 3);
    EXPECT_EQ(graph_1.numNeighbors(2), 3);
    EXPECT_EQ(graph_1.numNeighbors(3), 3);
    EXPECT_EQ(graph_1.numNeighbors(4), 4);
    EXPECT_EQ(graph_1.numNeighbors(5), 2);
    EXPECT_EQ(graph_1.numNeighbors(6), 3);
    EXPECT_EQ(graph_1.numNeighbors(7), 2);
    EXPECT_EQ(graph_1.numNeighbors(8), 2);
}

TEST_F(AdjacencyListGraphFixture, GetNeighbors)
{
    std::vector<int> neighbors {1, 2, 3, 4, 6, 7};
    EXPECT_EQ(graph_1.getNeighbors(0), neighbors);

    neighbors = {0, 2, 4};
    EXPECT_EQ(graph_1.getNeighbors(1), neighbors);

    neighbors = {0, 1, 3};
    EXPECT_EQ(graph_1.getNeighbors(2), neighbors);

    neighbors = {0, 2, 8};
    EXPECT_EQ(graph_1.getNeighbors(3), neighbors);
}

TEST_F(AdjacencyListGraphFixture, IsTherePathBetween)
{
    EXPECT_EQ(c4.pathBetween(0, 1), true);
    EXPECT_EQ(c4.pathBetween(0, 2), true);
    EXPECT_EQ(c4.pathBetween(0, 3), true);

    EXPECT_EQ(graph_2.pathBetween(0, 4), false);
    EXPECT_EQ(graph_2.pathBetween(1, 4), false);
    EXPECT_EQ(graph_2.pathBetween(0, 2), true);

    EXPECT_EQ(graph_3.pathBetween(0, 2), true);
    EXPECT_EQ(graph_3.pathBetween(3, 4), true);
    EXPECT_EQ(graph_3.pathBetween(0, 4), false);
    EXPECT_EQ(graph_3.pathBetween(1, 4), false);

    EXPECT_EQ(graph_4.pathBetween(5, 7), true);
    EXPECT_EQ(graph_4.pathBetween(6, 2), false);
}