//
// Created by daniel on 2/06/22.
//

#include "gtest/gtest.h"
#include "Digraph/digraph.h"
#include <vector>

TEST(Digraph, DefaultConstructor)
{
    Digraph graph;
    EXPECT_EQ(graph.numNodes(), 0);
    EXPECT_EQ(graph.numEdges(), 0);
}

TEST(Digraph, NumberOfNodesConstructor)
{
    Digraph graph(3);
    EXPECT_EQ(graph.numNodes(), 3);
    EXPECT_EQ(graph.numEdges(), 0);
}

TEST(Digraph, AddEdgesToGraph)
{
    Digraph graph(3);
    graph.addEdge(0, 1);

    EXPECT_EQ(graph.numEdges(), 1);
    EXPECT_EQ(graph.isEdge(0, 1), true);
    EXPECT_EQ(graph.isEdge(1, 0), false);

    graph.addEdge(1, 0);
    EXPECT_EQ(graph.numEdges(), 2);
    EXPECT_EQ(graph.isEdge(1, 0), true);
}

TEST(Digraph, AddingRepeatedEdgeDoesNotModifyTheGraph)
{
    Digraph graph(3);
    graph.addEdge(0, 1);
    graph.addEdge(0, 1);

    EXPECT_EQ(graph.numEdges(), 1);
    EXPECT_EQ(graph.isEdge(0, 1), true);
}

TEST(Digraph, InvalidNodeThrowsError)
{
    Digraph graph(3);
    EXPECT_THROW(graph.addEdge(0, 3), invalid_node_error);
    EXPECT_THROW(graph.addEdge(4, 0), invalid_node_error);
}

TEST(Digraph, AddNodesAndEdges)
{
    Digraph graph;
    graph.addNode();
    ASSERT_EQ(graph.numNodes(), 1);

    graph.addNode();
    graph.addNode();
    graph.addEdge(0, 1);
    ASSERT_EQ(graph.numNodes(), 3);
    ASSERT_EQ(graph.isEdge(0, 1), 1);
}

TEST(Digraph, NodeOutgoingEdges)
{
    Digraph graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(0, 4);
    graph.addEdge(1, 0);
    graph.addEdge(2, 0);

    EXPECT_EQ(graph.numOutEdges(0), 3);
    EXPECT_EQ(graph.numOutEdges(1), 1);
    EXPECT_EQ(graph.numOutEdges(2), 1);

    std::list<int> edges_0 {1, 3, 4};
    EXPECT_EQ(edges_0, graph.getOutNeighbors(0));
}

