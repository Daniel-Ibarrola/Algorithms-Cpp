//
// Created by daniel on 1/10/22.
//

#include "2-sat.h"
#include "gtest/gtest.h"


TEST(ImplicationGraph, CreateGraph)
{
    std::vector<std::vector<int>> formula_1 {
            {-1, 2},
            {-2, 3},
    };
    ImplicationGraph graph_1(formula_1, 3);
    ASSERT_EQ(graph_1.numNodes(), 6);
    ASSERT_EQ(graph_1.numEdges(), 4);

    std::vector<std::vector<int>> formula_2 {
            {1, 2},
            {1, -2},
            {-1, 2},
    };
    ImplicationGraph graph_2(formula_2, 2);
    ASSERT_EQ(graph_2.numNodes(), 4);
    ASSERT_EQ(graph_2.numEdges(), 6);

    std::vector<std::vector<int>> formula_3 {
            {1, 2},
            {-3},
    };
    ImplicationGraph graph_3(formula_3, 3);
    ASSERT_EQ(graph_3.numNodes(), 6);
    ASSERT_EQ(graph_3.numEdges(), 3);
}


TEST(ImplicationGraph, EdgeBetween)
{
    std::vector<std::vector<int>> formula_1 {
            {-1, 2},
            {-2, 3},
    };
    ImplicationGraph graph_1(formula_1, 3);
    ASSERT_TRUE(graph_1.isEdge(1, 2));
    ASSERT_TRUE(graph_1.isEdge(-2, -1));
    ASSERT_FALSE(graph_1.isEdge(-1, -2));
    ASSERT_FALSE(graph_1.isEdge(1, -3));
}


class ImplicationGraphTest : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    std::vector<std::pair<int, int>> edgeList_1 {
            {-1, -2},
            {1, 2},
            {1, -4},
            {-2, -3},
            {2, 3},
            {2, -4},
            {3, 1},
            {-3, -1},
            {-3, 4},
            {4, 2},
    };
    ImplicationGraph graph_1 {edgeList_1, 4};
};


TEST_F(ImplicationGraphTest, EdgeListConstructor)
{
    ASSERT_EQ(graph_1.numEdges(), 10);
    ASSERT_EQ(graph_1.numNodes(), 8);
}


TEST_F(ImplicationGraphTest, ReverseGraph)
{
    ImplicationGraph reverse {graph_1.reverse()};
    ASSERT_EQ(reverse.numEdges(), 10);
    ASSERT_EQ(reverse.numNodes(), 8);

    ASSERT_TRUE(reverse.isEdge(-2, -1));
    ASSERT_TRUE(reverse.isEdge(4, -3));
    ASSERT_TRUE(reverse.isEdge(1, 3));

    ASSERT_FALSE(reverse.isEdge(-1, -2));
    ASSERT_FALSE(reverse.isEdge(-3, 4));
    ASSERT_FALSE(reverse.isEdge(3, 1));
}


TEST_F(ImplicationGraphTest, StronglyConnectedComponents)
{
    std::vector<int> scc {graph_1.SCC()};
    std::vector<int> expectedSCC {3, 3, 3, 2, 1, 1, 1, 4};
    ASSERT_EQ(scc, expectedSCC);
}


TEST_F(ImplicationGraphTest, GetNodeSCC)
{
    std::vector<int> scc {graph_1.SCC()};

    ASSERT_EQ(graph_1.getNodeSCC(-1, scc), 1);
    ASSERT_EQ(graph_1.getNodeSCC(-2, scc), 1);
    ASSERT_EQ(graph_1.getNodeSCC(-3, scc), 1);

    ASSERT_EQ(graph_1.getNodeSCC(4, scc), 2);

    ASSERT_EQ(graph_1.getNodeSCC(1, scc), 3);
    ASSERT_EQ(graph_1.getNodeSCC(2, scc), 3);
    ASSERT_EQ(graph_1.getNodeSCC(3, scc), 3);
}


TEST_F(ImplicationGraphTest, NumberOfSCC)
{
    ASSERT_EQ(graph_1.numSCC(), 4);
}


class CNFFormula2Clause  : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    std::vector<std::vector<int>> satisfiable_1 {
        {1, 2},
        {-3},
        {3, -1},
    };

    std::vector<std::vector<int>> satisfiable_2 {
            {1, -3},
            {-1, 2},
            {-2, -3},
    };

    std::vector<std::vector<int>> unsat_1 {
            {1, 2},
            {-3},
            {3, -1},
            {-2},
    };

    std::vector<std::vector<int>> unsat_2 {
            {1, 2},
            {1, -2},
            {-1, 2},
            {-1, -2},
    };

    std::vector<std::vector<int>> unsat_3 {
            {1, 1},
            {-1, -1},
    };

};


TEST_F(CNFFormula2Clause, UnsatisfiableFormulas)
{
    std::vector<int> assignment_1 {twoSAT(unsat_1, 3)};
    std::vector<int> assignment_2 {twoSAT(unsat_2, 2)};
    std::vector<int> assignment_3 {twoSAT(unsat_3, 1)};

    ASSERT_TRUE(assignment_1.empty());
    ASSERT_TRUE(assignment_2.empty());
    ASSERT_TRUE(assignment_3.empty());
}


TEST_F(CNFFormula2Clause, SatisfiableFormulas)
{
    std::vector<int> assignment_1 {twoSAT(satisfiable_1, 3)};
    std::vector<int> expected_1 {-1, 2, -3};
    ASSERT_EQ(assignment_1, expected_1);

    std::vector<int> assignment_2 {twoSAT(satisfiable_2, 3)};
    std::vector<int> expected_2 {1, 2, -3};
    ASSERT_EQ(assignment_1, expected_1);
}
