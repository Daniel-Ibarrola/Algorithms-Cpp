//
// Created by daniel on 29/05/22.
//

#include "gtest/gtest.h"
#include "Graph/graph.h"
#include <tuple>
#include <vector>
#include <limits>

TEST(AdjacencyListGraph, EmptyConstructor)
{
    Graph g;
    EXPECT_EQ(g.numNodes(), 0);
    EXPECT_EQ(g.numEdges(), 0);
}

TEST(AdjacencyListGraph, NumberOfNodesConstructor)
{
    Graph g(5);
    EXPECT_EQ(g.numNodes(), 5);
    EXPECT_EQ(g.numEdges(), 0);
}

TEST(AdjacencyListGraph, AddNode)
{
    // Test with an empty graph
    Graph g;
    g.addNode();
    EXPECT_EQ(g.numNodes(), 1);

    // Test with a non-empty graph
    Graph j(3);
    j.addNode();
    EXPECT_EQ(j.numNodes(), 4);
}

TEST(AdjacencyListGraph, IsEdgeAndAddEdge)
{
    Graph g(3);
    EXPECT_EQ(g.isEdge(0, 1), false);
    EXPECT_EQ(g.isEdge(1, 0), false);

    EXPECT_EQ(g.isEdge(0, 2), false);
    EXPECT_EQ(g.isEdge(2, 0), false);

    Graph j(3);
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
    Graph j(3);
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

class ShortestPathGraphs : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::vector<std::tuple<int, int>> edges {
                {0, 1}, {0, 2}, {0, 3}, {1, 2}
        };
        testGraph_1.addEdges(edges);

        edges = {
                {0, 2}, {0, 3}, {1, 4}, {2, 3}
        };
        testGraph_2.addEdges(edges);

        testGraph_3.addEdgesToNode(0, std::vector<int> {1, 2, 4, 5});
        testGraph_3.addEdgesToNode(1, std::vector<int> {0, 2, 5, 6, 7});
        testGraph_3.addEdgesToNode(2, std::vector<int> {0, 1, 3, 7});
        testGraph_3.addEdgesToNode(3, std::vector<int> {2, 4, 7, 8});
        testGraph_3.addEdgesToNode(4, std::vector<int> {0, 3, 5, 8});
        testGraph_3.addEdgesToNode(5, std::vector<int> {0, 1, 4, 6, 8});
        testGraph_3.addEdgesToNode(6, std::vector<int> {1, 5, 7, 8});
        testGraph_3.addEdgesToNode(7, std::vector<int> {1, 2, 3, 6, 8});
        testGraph_3.addEdgesToNode(8, std::vector<int> {3, 4, 5, 6, 7});
    }

    Graph testGraph_1 {4};
    Graph testGraph_2 {5};
    Graph testGraph_3 {9};
};

TEST_F(ShortestPathGraphs, DistancesAndShortestPath)
{
    std::vector<int> expectedDistances {1, 0, 1, 2};
    ASSERT_EQ(testGraph_1.distancesFromNode(1), expectedDistances);
    ASSERT_EQ(testGraph_1.shortestPath(1, 0), 1);
    ASSERT_EQ(testGraph_1.shortestPath(1, 2), 1);
    ASSERT_EQ(testGraph_1.shortestPath(1, 3), 2);

    expectedDistances = {0, std::numeric_limits<int>::max(),
                         1, 1, std::numeric_limits<int>::max()};
    ASSERT_EQ(testGraph_2.distancesFromNode(0), expectedDistances);
    ASSERT_EQ(testGraph_2.shortestPath(0, 2), 1);
    ASSERT_EQ(testGraph_2.shortestPath(0, 3), 1);
    ASSERT_EQ(testGraph_2.shortestPath(0, 4), -1);
    ASSERT_EQ(testGraph_2.shortestPath(4, 1), 1);
    ASSERT_EQ(testGraph_2.shortestPath(4, 2), -1);

    expectedDistances = {2, 1, 2, 2, 2, 1, 0, 1, 1};
    ASSERT_EQ(expectedDistances.size(), 9);
    ASSERT_EQ(testGraph_3.distancesFromNode(6), expectedDistances);
    ASSERT_EQ(testGraph_3.shortestPath(6, 1), 1);
    ASSERT_EQ(testGraph_3.shortestPath(6, 2), 2);
    ASSERT_EQ(testGraph_3.shortestPath(0, 6), 2);
}


class AdjacencyListGraphFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // graph_1 has one connected component

        std::vector<std::tuple<int, int>> edges {
                {0, 1}, {0, 2}, {0, 3}, {0, 4},
                {0, 6}, {0, 7}, {1, 2}, {1, 4},
                {2, 3}, {3, 8}, {4, 5}, {4,8},
                {5, 6}, {6, 7}
        };
        graph_1.addEdges(edges);

        // c4 has one connected component
        edges = {
                {0, 1}, {0, 2}, {1, 3}, {2, 3}
        };
        c4.addEdges(edges);

        // graph_2 has two connected components
        graph_2.addEdge(0, 1);
        graph_2.addEdge(1, 2);

        // graph_3 has two connected components
        edges = {
                {0, 1}, {0, 2}, {1, 2}, {3, 4}
        };
        graph_3.addEdges(edges);

        // graph_4 has three connected components
        edges = {
                {0, 1}, {0, 2}, {1, 2},
                {3, 4}, {5, 6}, {6, 7}

        };
        graph_4.addEdges(edges);
    }

    Graph graph_1{9};
    Graph c4 {4};
    Graph graph_2 {4};
    Graph graph_3 {5};
    Graph graph_4{8};
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
    // A node is always reachable form itself
    EXPECT_EQ(c4.pathBetween(0, 0), true);

    EXPECT_EQ(c4.pathBetween(0, 1), true);
    EXPECT_EQ(c4.pathBetween(0, 2), true);
    EXPECT_EQ(c4.pathBetween(0, 3), true);

    EXPECT_EQ(graph_2.pathBetween(0, 3), false);
    EXPECT_EQ(graph_2.pathBetween(1, 3), false);
    EXPECT_EQ(graph_2.pathBetween(0, 2), true);

    EXPECT_EQ(graph_3.pathBetween(0, 2), true);
    EXPECT_EQ(graph_3.pathBetween(3, 4), true);
    EXPECT_EQ(graph_3.pathBetween(0, 4), false);
    EXPECT_EQ(graph_3.pathBetween(1, 4), false);

    EXPECT_EQ(graph_4.pathBetween(5, 7), true);
    EXPECT_EQ(graph_4.pathBetween(6, 2), false);
    EXPECT_EQ(graph_4.pathBetween(6, 3), false);
}

TEST_F(AdjacencyListGraphFixture, NumberOfConnectedComponents)
{
    // Test with an empty graph
    Graph g;
    EXPECT_EQ(g.numConnectedComponents(), 0);

    // Test a graph with no edges
    Graph j(20);
    EXPECT_EQ(j.numConnectedComponents(), 20);

    // Test non-trivial graphs
    EXPECT_EQ(c4.numConnectedComponents(), 1);
    EXPECT_EQ(graph_2.numConnectedComponents(), 2);
    EXPECT_EQ(graph_3.numConnectedComponents(), 2);
    EXPECT_EQ(graph_4.numConnectedComponents(), 3);
}

TEST(AdjacencyListGraph, IsGraphBipartite)
{
    // Empty graph should be bipartite
    Graph emptyGraph;
    ASSERT_EQ(emptyGraph.isBipartite(), true);

    // A graph with no edges is also bipartite
    Graph noEdgesGraph(5);
    ASSERT_EQ(noEdgesGraph.isBipartite(), true);

    Graph graph(4);
    graph.addEdges({
        {0, 1}, {0, 2}, {0, 3}, {1, 2}
    });
    ASSERT_EQ(graph.numEdges(), 4);
    ASSERT_EQ(graph.isBipartite(), false);

    Graph graph_2(5);
    graph_2.addEdges({
        {0, 3}, {1, 3}, {1, 4}, {2, 3}
    });
    ASSERT_EQ(graph_2.numEdges(), 4);
    ASSERT_EQ(graph_2.isBipartite(), true);

    Graph graph_3(5);
    graph_3.addEdges({
        {0, 1}, {1, 2}, {1, 3}, {2, 4}, {3, 4}
    });
    ASSERT_EQ(graph_3.numEdges(), 5);
    ASSERT_EQ(graph_3.isBipartite(), true);

    // Test a multiple component graph
    Graph graph_4(7);
    graph_4.addEdges({
        {0, 1}, {1, 2}, {2, 3},
        {4, 5}, {4, 6}, {5, 6}
    });
    ASSERT_EQ(graph_4.numEdges(), 6);
    ASSERT_EQ(graph_4.isBipartite(), false);

    Graph graph_5(8);
    graph_5.addEdges({
         {0, 1}, {1, 2}, {2, 3},
         {4, 5}, {5, 6}, {6, 7},
         {7, 4}
    });
    ASSERT_EQ(graph_5.numEdges(), 7);
    ASSERT_EQ(graph_5.isBipartite(), true);
}