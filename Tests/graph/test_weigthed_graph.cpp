//
// Created by daniel on 14/06/22.
//

#include "gtest/gtest.h"
#include "Graph/weighted_graph.h"

TEST(WeightedGraph, AddingEdgesAndNodes)
{
    WeightedGraph graph(3);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(2, 1, 3);
    graph.addNode();
    graph.addEdge(3, 2, 7);

    ASSERT_EQ(graph.numNodes(), 4);
    ASSERT_EQ(graph.numEdges(), 4);

    ASSERT_EQ(graph.isEdge(0, 1), true);
    ASSERT_EQ(graph.getWeight(0, 1), 10);
    ASSERT_EQ(graph.getWeight(1, 0), 10);

    ASSERT_EQ(graph.isEdge(2, 0), true);
    ASSERT_EQ(graph.getWeight(2, 0), 5);
    ASSERT_EQ(graph.getWeight(0, 2), 5);

    ASSERT_EQ(graph.isEdge(1, 2), true);
    ASSERT_EQ(graph.getWeight(2, 1), 3);

    ASSERT_EQ(graph.isEdge(3, 2), true);
    ASSERT_EQ(graph.getWeight(2, 3), 7);
}

TEST(WeightedGraph, KruskalAlgorithm)
{

}

TEST(WeightedGraph, PrimAlgorithm)
{

}