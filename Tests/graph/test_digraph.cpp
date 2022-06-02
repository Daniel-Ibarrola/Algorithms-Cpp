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

TEST(Digraph, IsCyclic)
{
    Digraph graph_1(4);
    graph_1.addEdge(0, 1);
    graph_1.addEdge(1, 2);
    graph_1.addEdge(2, 0);
    graph_1.addEdge(3, 0);

    EXPECT_EQ(graph_1.isCyclic(), true);

    Digraph graph_2(5);
    graph_2.addEdge(0, 3);
    graph_2.addEdge(0, 2);
    graph_2.addEdge(0, 1);
    graph_2.addEdge(1, 2);
    graph_2.addEdge(1, 4);
    graph_2.addEdge(2, 3);
    graph_2.addEdge(2, 4);

    EXPECT_EQ(graph_2.isCyclic(), false);

    Digraph graph_3(8);
    graph_3.addEdge(0, 1);
    graph_3.addEdge(1, 2);
    graph_3.addEdge(2, 3);
    graph_3.addEdge(3, 4);
    graph_3.addEdge(4, 5);
    graph_3.addEdge(5, 6);
    graph_3.addEdge(6, 7);
    graph_3.addEdge(7, 0);

    EXPECT_EQ(graph_3.isCyclic(), true);

    Digraph graph_4(8);
    graph_4.addEdge(0, 1);
    graph_4.addEdge(1, 2);
    graph_4.addEdge(2, 3);
    graph_4.addEdge(3, 4);
    graph_4.addEdge(4, 5);
    graph_4.addEdge(5, 6);
    graph_4.addEdge(6, 7);
    graph_4.addEdge(0, 7);

    EXPECT_EQ(graph_4.isCyclic(), false);

}