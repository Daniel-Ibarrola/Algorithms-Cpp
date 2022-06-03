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

TEST(Digraph, TopologicalOrderCyclicGraphReturnsEmptyVector)
{
    Digraph graph_1(4);
    graph_1.addEdge(0, 1);
    graph_1.addEdge(1, 2);
    graph_1.addEdge(2, 0);
    graph_1.addEdge(3, 0);
    ASSERT_EQ(graph_1.topologicalOrder().empty(), true);
}

TEST(Digraph, ToplogicalOrdering)
{
    Digraph graph_1(4);
    graph_1.addEdge(0, 1);
    graph_1.addEdge(2, 0);
    graph_1.addEdge(3, 0);
    std::vector<int> topologicalOrder {3, 2, 0, 1};
    ASSERT_EQ(graph_1.topologicalOrder(), topologicalOrder);

    Digraph graph_2(4);
    graph_2.addEdge(2, 0);
    topologicalOrder = {3, 2, 1, 0};
    ASSERT_EQ(graph_2.topologicalOrder(), topologicalOrder);

    Digraph graph_3(5);
    graph_3.addEdge(1, 0);
    graph_3.addEdge(2, 0);
    graph_3.addEdge(2, 1);
    graph_3.addEdge(3, 0);
    graph_3.addEdge(3, 2);
    graph_3.addEdge(4, 1);
    graph_3.addEdge(4, 2);
    topologicalOrder = {4, 3, 2, 1, 0};
    ASSERT_EQ(graph_3.topologicalOrder(), topologicalOrder);

    Digraph graph_4(4);
    graph_4.addEdge(0, 1);
    graph_4.addEdge(0, 2);
    graph_4.addEdge(1, 3);
    graph_4.addEdge(2, 3);
    topologicalOrder = {0, 2, 1, 3};
    ASSERT_EQ(graph_4.topologicalOrder(), topologicalOrder);
}

TEST(Digraph, TestReverseGraph)
{
    Digraph emptyGraph;
    Digraph reverse {emptyGraph.reverseGraph()};
    ASSERT_EQ(reverse.numNodes(), 0);
    ASSERT_EQ(reverse.numEdges(), 0);

    Digraph graph_1(4);
    graph_1.addEdge(0, 1);
    graph_1.addEdge(2, 0);
    graph_1.addEdge(3, 0);

    Digraph reverseGraph_1 {graph_1.reverseGraph()};
    ASSERT_EQ(reverseGraph_1.numNodes(), 4);
    ASSERT_EQ(reverseGraph_1.numEdges(), 3);

    ASSERT_EQ(reverseGraph_1.isEdge(0, 1), false);
    ASSERT_EQ(reverseGraph_1.isEdge(2, 0), false);
    ASSERT_EQ(reverseGraph_1.isEdge(3, 0), false);

    ASSERT_EQ(reverseGraph_1.isEdge(1, 0), true);
    ASSERT_EQ(reverseGraph_1.isEdge(0, 2), true);
    ASSERT_EQ(reverseGraph_1.isEdge(0, 3), true);
}

TEST(Digraph, NumberStronglyConnectedComponents)
{
    // The empty graph should have 0 SCC
    Digraph emptyGraph;
    ASSERT_EQ(emptyGraph.numStronglyConnectedComponents(), 0);

    // A non-empty graph must have at least 1 SCC
    Digraph singleNodeGraph(1);
    ASSERT_EQ(singleNodeGraph.numStronglyConnectedComponents(), 1);

    // For graphs with no edges the number of SCC is equal to the number of nodes
    Digraph noEdgesGraph(20);
    ASSERT_EQ(noEdgesGraph.numStronglyConnectedComponents(), 20);

    // Continue with non-trivial test cases

    Digraph graph_1(4);
    graph_1.addEdge(0, 1);
    graph_1.addEdge(1, 2);
    graph_1.addEdge(2, 0);
    graph_1.addEdge(3, 0);
    ASSERT_EQ(graph_1.numStronglyConnectedComponents(), 2);

    Digraph graph_2(5);
    graph_2.addEdge(1, 0);
    graph_2.addEdge(2, 0);
    graph_2.addEdge(2, 1);
    graph_2.addEdge(3, 0);
    graph_2.addEdge(3, 2);
    graph_2.addEdge(4, 1);
    graph_2.addEdge(4, 2);
    ASSERT_EQ(graph_2.numStronglyConnectedComponents(), 5);

    Digraph graph_3(9);
    graph_3.addEdge(0, 1);
    graph_3.addEdge(1, 4);
    graph_3.addEdge(1, 5);
    graph_3.addEdge(2, 1);
    graph_3.addEdge(3, 0);
    graph_3.addEdge(3, 6);
    graph_3.addEdge(4, 0);
    graph_3.addEdge(4, 2);
    graph_3.addEdge(4, 7);
    graph_3.addEdge(6, 7);
    graph_3.addEdge(7, 8);
    graph_3.addEdge(8, 5);
    graph_3.addEdge(8, 7);
    ASSERT_EQ(graph_3.numEdges(), 13);
    ASSERT_EQ(graph_3.numStronglyConnectedComponents(), 5);
}