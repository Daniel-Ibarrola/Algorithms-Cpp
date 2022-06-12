//
// Created by daniel on 12/06/22.
//
#include "gtest/gtest.h"
#include "Digraph/weighted_digraph.h"

TEST(WeightedDigraph, EmptyConstructor)
{
    WeightedDigraph graph;
    ASSERT_EQ(graph.numNodes(), 0);
    ASSERT_EQ(graph.numEdges(), 0);
}

TEST(WeightedDigraph, NumberOfNodesConstructor)
{
    WeightedDigraph graph(3);
    ASSERT_EQ(graph.numNodes(), 3);
    ASSERT_EQ(graph.numEdges(), 0);
}

TEST(WeightedDigraph, AddEdgesToGraph)
{
    WeightedDigraph graph(3);
    graph.addEdge(0, 1, 5);

    ASSERT_EQ(graph.numEdges(), 1);
    ASSERT_EQ(graph.isEdge(0, 1), true);
    ASSERT_EQ(graph.getWeight(0, 1), 5);
    ASSERT_EQ(graph.isEdge(1, 0), false);

    graph.addEdge(1, 0, 3);
    ASSERT_EQ(graph.numEdges(), 2);
    ASSERT_EQ(graph.isEdge(1, 0), true);
    ASSERT_EQ(graph.getWeight(1, 0), 3);
}

TEST(WeightedDigraph, AddingRepeatedEdgeDoesNotModifyTheGraph)
{
    WeightedDigraph graph(3);
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 1, 3);

    ASSERT_EQ(graph.numEdges(), 1);
    ASSERT_EQ(graph.isEdge(0, 1), true);
    // Weight should be the original one
    ASSERT_EQ(graph.getWeight(0, 1), 2);
}


TEST(WeightedDigraph, InvalidNodeThrowsError)
{
    WeightedDigraph graph(3);
    EXPECT_THROW(graph.addEdge(0, 3, 5), invalid_node_error);
    EXPECT_THROW(graph.addEdge(4, 0, 3), invalid_node_error);
}

TEST(WeightedDigraph, AddNodesAndEdges)
{
    WeightedDigraph graph;
    graph.addNode();
    ASSERT_EQ(graph.numNodes(), 1);

    graph.addNode();
    graph.addNode();
    graph.addEdge(0, 1, 10);
    ASSERT_EQ(graph.numNodes(), 3);
    ASSERT_EQ(graph.isEdge(0, 1), 1);
    ASSERT_EQ(graph.getWeight(0, 1), 10);
}

TEST(WeightedDigraph, NodeOutgoingEdges)
{
    WeightedDigraph graph(5);
    graph.addEdges({
        {0, 1, 2},
        {0, 3, 3},
        {0, 4, 4},
        {1, 0, 5},
        {2, 0, 5},
        });

    ASSERT_EQ(graph.outDegree(0), 3);
    ASSERT_EQ(graph.outDegree(1), 1);
    ASSERT_EQ(graph.outDegree(2), 1);

    std::list<Edge> edges {
            {1, 2},
            {3, 3},
            {4, 4},
    };
    ASSERT_EQ(edges, graph.getOutNeighbors(0));
}


