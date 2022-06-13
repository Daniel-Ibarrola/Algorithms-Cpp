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


TEST(DijkstraShortestPath, DistancesAndShortestPath)
{
    WeightedDigraph noEdgesGraph(4);
    std::vector<int> distances(4, std::numeric_limits<int>::max());
    distances[0] = 0;
    ASSERT_EQ(noEdgesGraph.getDistances(0), distances);
    ASSERT_EQ(noEdgesGraph.shortestPathLength(0, 3), -1);

    WeightedDigraph graphWithNoPath(3);
    graphWithNoPath.addEdges({
        {0, 1, 7},
        {0, 2, 5},
        {1, 2, 2}
    });
    std::vector<int> distances_no_path(3, std::numeric_limits<int>::max());
    distances_no_path[2] = 0;
    ASSERT_EQ(graphWithNoPath.getDistances(2), distances_no_path);
    ASSERT_EQ(graphWithNoPath.shortestPathLength(2, 1), -1);

    WeightedDigraph graph_1(4);
    graph_1.addEdges({
        {0, 1, 1},
        {0, 2, 5},
        {1, 2, 2},
        {3, 0, 2},
    });
    std::vector<int> distances_1 {0, 1, 3, std::numeric_limits<int>::max()};
    ASSERT_EQ(graph_1.getDistances(0), distances_1);
    ASSERT_EQ(graph_1.shortestPathLength(0, 2), 3);
    ASSERT_EQ(graph_1.shortestPathLength(0, 3), -1);

    WeightedDigraph graph_2(5);
    graph_2.addEdges({
        {0, 1, 4},
        {0, 2, 2},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 3},
        {2, 1, 1},
        {2, 3, 4},
        {2, 4, 4},
        {4, 3, 1}
    });
    std::vector<int> distances_2 {
        0, 3, 2, 5, 6
    };
    ASSERT_EQ(graph_2.numEdges(), 9);
    ASSERT_EQ(graph_2.getDistances(0), distances_2);
    ASSERT_EQ(graph_2.shortestPathLength(0, 4), 6);
}