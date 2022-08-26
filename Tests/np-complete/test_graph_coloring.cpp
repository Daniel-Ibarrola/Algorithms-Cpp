//
// Created by daniel on 24/08/22.
//
#include "gtest/gtest.h"
#include "graph_coloring.h"

std::vector<std::vector<int>> threeColorC3Expression()
{
    // Returns the CNF formula for the 3-coloring of C3 graph
    std::vector<std::vector<int>> expression {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {-1, -2},
        {-1, -3},
        {-2, -3},
        {-4, -5},
        {-4, -6},
        {-5, -6},
        {-7, -8},
        {-7, -9},
        {-8, -9},
        {-1, -4},
        {-2, -5},
        {-3, -6},
        {-1, -7},
        {-2, -8},
        {-3, -9},
        {-4, -7},
        {-5, -8},
        {-6, -9},
    };
    for (auto& clause : expression)
        clause.push_back(0);
    return expression;
}

TEST(TestGraphColoring, CreateGraphFromEdgeList)
{
    std::vector<std::pair<int, int>> edgeList {
            {1, 2}, {1, 3}, {2, 3}
    };
    Graph3C graph (3, edgeList);
    ASSERT_EQ(graph.numEdges(), 3);
    ASSERT_EQ(graph.numNodes(), 3);
}


TEST(TestGraphColoring, CNFExpression)
{
    std::vector<std::pair<int, int>> edgeList {
            {1, 2}, {1, 3}, {2, 3}
    };
    Graph3C graph (3, edgeList);
    ASSERT_EQ(graph.threeColorCNF(), threeColorC3Expression());
}

TEST(TestGraphColoring, EdgeToLiteral)
{
    std::vector<int> expected {1, 4, 7, 10};
    ASSERT_EQ(Graph3C::edgeToLit(12), expected);
}