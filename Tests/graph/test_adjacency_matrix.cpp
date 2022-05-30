//
// Created by daniel on 29/05/22.
//

#include "gtest/gtest.h"
#include "Graph/adjacency_matrix.h"
#include <vector>

TEST(AdjacencyMatrix, ConstructorWorks)
{
    MatrixGraph g(5);
    EXPECT_EQ(g.numNodes(), 5);
}

TEST(AdjacencyMatrix, AddEdge)
{
    MatrixGraph g(5);
    g.addEdge(0, 2);

    EXPECT_EQ(g.numEdges(), 1);
    EXPECT_EQ(g.isEdge(0, 2), true);
    EXPECT_EQ(g.isEdge(2, 0), true);

    g.addEdge(3, 4);
    EXPECT_EQ(g.numEdges(), 2);
    EXPECT_EQ(g.isEdge(3, 4), true);
    EXPECT_EQ(g.isEdge(4, 3), true);
}

class AdjacencyMatrixGraph : public ::testing::Test
{
protected:
    void SetUp() override
    {
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(0, 3);
        g.addEdge(0, 4);
        g.addEdge(0, 6);
        g.addEdge(0, 7);
        g.addEdge(1, 2);
        g.addEdge(1, 4);
        g.addEdge(2, 3);
        g.addEdge(3, 8);
        g.addEdge(4, 5);
        g.addEdge(4, 8);
        g.addEdge(5, 6);
        g.addEdge(6, 7);
    }

    MatrixGraph g{9};
};

TEST_F(AdjacencyMatrixGraph, GetNumberOfNeighbors)
{

    EXPECT_EQ(g.numEdges(), 14);
    EXPECT_EQ(g.numNeighbors(0), 6);
    EXPECT_EQ(g.numNeighbors(1), 3);
    EXPECT_EQ(g.numNeighbors(2), 3);
    EXPECT_EQ(g.numNeighbors(3), 3);
    EXPECT_EQ(g.numNeighbors(4), 4);
    EXPECT_EQ(g.numNeighbors(5), 2);
    EXPECT_EQ(g.numNeighbors(6), 3);
    EXPECT_EQ(g.numNeighbors(7), 2);
    EXPECT_EQ(g.numNeighbors(8), 2);

}

TEST_F(AdjacencyMatrixGraph, GetNeighbors)
{
    std::vector<int> neighbors {1, 2, 3, 4, 6, 7};
    EXPECT_EQ(g.getNeighbors(0), neighbors);

    neighbors = {0, 2, 4};
    EXPECT_EQ(g.getNeighbors(1), neighbors);

    neighbors = {0, 1, 3};
    EXPECT_EQ(g.getNeighbors(2), neighbors);

    neighbors = {0, 2, 8};
    EXPECT_EQ(g.getNeighbors(3), neighbors);
}