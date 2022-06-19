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

class MinimumSpanningTree : public ::testing::Test
{
protected:
    void SetUp() override
    {
        graph_1.addEdges({
            {0, 1, 4},
            {0, 3, 2},
            {0, 4, 1},
            {1, 2, 8},
            {1, 4, 5},
            {1, 5, 6},
            {2, 5, 1},
            {3, 4, 3},
            {4, 5, 9}
        });

        graph_2.addEdges({
            {0, 1, 2},
            {0, 2, 2},
            {1, 2, 1},
            {1, 3, 5},
            {2, 3, 3},
            {2, 4, 4},
            {3, 4, 6},
            {3, 5, 2},
            {4, 5, 6}
        });
    }

    WeightedGraph emptyGraph;
    WeightedGraph graph_1 {6};
    WeightedGraph graph_2 {6};
};


TEST_F(MinimumSpanningTree, KruskalAlgorithm)
{
    WeightedGraph mstEmptyGraph_kruskal {emptyGraph.kruskalMST()};
    ASSERT_EQ(mstEmptyGraph_kruskal.numNodes(), 0);
    ASSERT_EQ(mstEmptyGraph_kruskal.numEdges(), 0);

    WeightedGraph mst_1_kruskal {graph_1.kruskalMST()};
    ASSERT_EQ(mst_1_kruskal.numNodes(), graph_1.numNodes());
    ASSERT_EQ(mst_1_kruskal.numEdges(), 5);
    ASSERT_EQ(mst_1_kruskal.isEdge(0, 1), true);
    ASSERT_EQ(mst_1_kruskal.isEdge(0, 3), true);
    ASSERT_EQ(mst_1_kruskal.isEdge(0, 4), true);
    ASSERT_EQ(mst_1_kruskal.isEdge(1, 5), true);
    ASSERT_EQ(mst_1_kruskal.isEdge(5, 2), true);

    WeightedGraph mst_2_kruskal {graph_2.kruskalMST()};
    ASSERT_EQ(mst_2_kruskal.numNodes(), graph_2.numNodes());
    ASSERT_EQ(mst_2_kruskal.numEdges(), 5);
    ASSERT_EQ(mst_2_kruskal.isEdge(0, 2), true);
    ASSERT_EQ(mst_2_kruskal.isEdge(1, 2), true);
    ASSERT_EQ(mst_2_kruskal.isEdge(2, 3), true);
    ASSERT_EQ(mst_2_kruskal.isEdge(4, 2), true);
    ASSERT_EQ(mst_2_kruskal.isEdge(5, 3), true);
}

TEST_F(MinimumSpanningTree, PrimsAlgorithm)
{
    WeightedGraph mstEmptyGraph_prim {emptyGraph.primsMST()};
    ASSERT_EQ(mstEmptyGraph_prim.numNodes(), 0);
    ASSERT_EQ(mstEmptyGraph_prim.numEdges(), 0);

    WeightedGraph mst_1_prim {graph_1.primsMST()};
    ASSERT_EQ(mst_1_prim.numNodes(), graph_1.numNodes());
    ASSERT_EQ(mst_1_prim.numEdges(), 5);
    ASSERT_EQ(mst_1_prim.isEdge(0, 1), true);
    ASSERT_EQ(mst_1_prim.isEdge(0, 3), true);
    ASSERT_EQ(mst_1_prim.isEdge(0, 4), true);
    ASSERT_EQ(mst_1_prim.isEdge(1, 5), true);
    ASSERT_EQ(mst_1_prim.isEdge(5, 2), true);

    WeightedGraph mst_2_prim {graph_2.primsMST()};
    ASSERT_EQ(mst_2_prim.numNodes(), graph_2.numNodes());
    ASSERT_EQ(mst_2_prim.numEdges(), 5);
    ASSERT_EQ(mst_2_prim.isEdge(0, 1), true);
    ASSERT_EQ(mst_2_prim.isEdge(1, 2), true);
    ASSERT_EQ(mst_2_prim.isEdge(2, 3), true);
    ASSERT_EQ(mst_2_prim.isEdge(4, 2), true);
    ASSERT_EQ(mst_2_prim.isEdge(5, 3), true);
}
