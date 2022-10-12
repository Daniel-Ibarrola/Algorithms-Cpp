//
// Created by daniel on 6/09/22.
//
#include "gtest/gtest.h"
#include "hamiltonian_cycle/hamiltonian_cycle.h"


class CNFFormulaHamiltonianCycle : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    matrix constrain_1 {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
    };

    matrix constrain_2 {
        {-1, -2},
        {-1, -3},
        {-2, -3},
        {-4, -5},
        {-4, -6},
        {-5, -6},
        {-7, -8},
        {-7, -9},
        {-8, -9},
    };

    matrix constrain_3 {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9},
    };

    matrix constrain_4 {
        {-1, -4},
        {-1, -7},
        {-4, -7},
        {-2, -5},
        {-2, -8},
        {-5, -8},
        {-3, -6},
        {-3, -9},
        {-6, -9},
    };

    matrix constrain_5 {
        {-1, -8},
        {-2, -9},
        {-7, -2},
        {-8, -3},
    };
};


TEST_F(CNFFormulaHamiltonianCycle, Constrain_1)
{
    matrix expression;
    nodeBelongsToPath(3, expression);
    ASSERT_EQ(constrain_1, expression);
}

TEST_F(CNFFormulaHamiltonianCycle, Constrain_2)
{
    matrix expression;
    nodeAppearsOnce(3, expression);
    ASSERT_EQ(constrain_2, expression);
}


TEST_F(CNFFormulaHamiltonianCycle, Constrain_3)
{
    matrix expression;
    positionsOccupied(3, expression);
    ASSERT_EQ(constrain_3, expression);
}


TEST_F(CNFFormulaHamiltonianCycle, Constrain_4)
{
    matrix expression;
    differentPositions(3, expression);
    ASSERT_EQ(constrain_4, expression);
}


TEST_F(CNFFormulaHamiltonianCycle, CompleteExpression)
{
    int numNodes {3};
    std::vector<std::pair<int, int>> edgeList {{1, 2}, {2, 3}};

    matrix completeExpression;
    completeExpression.insert(completeExpression.end(),
                              constrain_1.begin(), constrain_1.end());
    completeExpression.insert(completeExpression.end(),
                              constrain_2.begin(), constrain_2.end());
    completeExpression.insert(completeExpression.end(),
                              constrain_3.begin(), constrain_3.end());
    completeExpression.insert(completeExpression.end(),
                              constrain_4.begin(), constrain_4.end());
    completeExpression.insert(completeExpression.end(),
                              constrain_5.begin(), constrain_5.end());

    ASSERT_EQ(completeExpression, hamiltonianCycleCNF(numNodes, edgeList));
}


class HCGraphTest : public testing::Test
{
protected:
    void SetUp() override
    {

    }

    std::vector<std::pair<int, int>> edgeList_1 {
        {1, 2}, {2, 3}};
    HCGraph graph_1 {edgeList_1, 3};

    std::vector<std::pair<int, int>> edgeList_2 {
        {1, 2}, {1, 3}, {1, 4}};
    HCGraph graph_2 {edgeList_2, 4};
};


TEST_F(HCGraphTest, AdjacencyMatrix)
{
    adjMatrix adjMatrix_1 {
            {false, true, false},
            {true, false, true},
            {false, true, false},
    };
    ASSERT_EQ(3, graph_1.numNodes());
    ASSERT_EQ(adjMatrix_1, graph_1.getAdjacencyMatrix());

    adjMatrix adjMatrix_2 {
            {false, true, true, true},
            {true, false, false, false},
            {true, false, false, false},
            {true, false, false, false},
    };
    ASSERT_EQ(4, graph_2.numNodes());
    ASSERT_EQ(adjMatrix_2, graph_2.getAdjacencyMatrix());
}


TEST_F(HCGraphTest, ConnectivityClause)
{
    matrix expectedExpression_1 {
            {-1, -8},
            {-2, -9},
            {-7, -2},
            {-8, -3},
    };
    matrix expression;
    graph_1.connectivityCNF(expression);
    ASSERT_EQ(expectedExpression_1, expression);

    matrix expectedExpression_2 {
        {-5, -10},
        {-6, -11},
        {-7, -12},
        {-5, -14},
        {-6, -15},
        {-7, -16},
        {-9, -6},
        {-10, -7},
        {-11, -8},
        {-9, -14},
        {-10, -15},
        {-11, -16},
        {-13, -6},
        {-14, -7},
        {-15, -8},
        {-13, -10},
        {-14, -11},
        {-15, -12},
    };
    matrix expression_2;
    graph_2.connectivityCNF(expression_2);
    ASSERT_EQ(expectedExpression_2, expression_2);
}
