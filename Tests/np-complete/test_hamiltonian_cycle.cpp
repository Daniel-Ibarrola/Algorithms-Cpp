//
// Created by daniel on 6/09/22.
//
#include "gtest/gtest.h"
#include "hamiltonian_cycle.h"


class CNFFormulaHamiltonianCycle : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    std::vector<std::vector<int>> constrain_1 {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
    };

    std::vector<std::vector<int>> constrain_2 {
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

    std::vector<std::vector<int>> constrain_3 {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9},
    };

    std::vector<std::vector<int>> constrain_4 {
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

    std::vector<std::vector<int>> constrain_5 {
        {-1, -5},
        {-2, -9},
    };
};


TEST_F(CNFFormulaHamiltonianCycle, Constrain_1)
{
    std::vector<std::vector<int>> expression {nodeBelongsToPath(3)};
    ASSERT_EQ(constrain_1, expression);
}

TEST_F(CNFFormulaHamiltonianCycle, Constrain_2)
{
    std::vector<std::vector<int>> expression {nodeAppearsOnce(3)};
    ASSERT_EQ(constrain_2, expression);
}


TEST_F(CNFFormulaHamiltonianCycle, Constrain_3)
{
    std::vector<std::vector<int>> expression {positionsOccupied(3)};
    ASSERT_EQ(constrain_3, expression);
}


TEST_F(CNFFormulaHamiltonianCycle, Constrain_4)
{
    std::vector<std::vector<int>> expression {differentPositions(3)};
    ASSERT_EQ(constrain_4, expression);
}


TEST_F(CNFFormulaHamiltonianCycle, CompleteExpression)
{
    int numNodes {3};
    std::vector<std::pair<int, int>> edgeList {{1, 2}, {2, 3}};

    std::vector<std::vector<int>> completeExpression;
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

    std::vector<std::pair<int, int>> edgeList_1 {{1, 2}, {2, 3}};
    std::vector<std::pair<int, int>> edgeList_2 {
        {1, 2}, {1, 3}, {1, 4}};

    HCGraph graph_1 {edgeList_1, 3};
    HCGraph graph_2 {edgeList_2, 4};
};


TEST_F(HCGraphTest, ConnectivityClause)
{
    std::vector<std::vector<int>> expression_1 {
            {-1, -5},
            {-2, -9},
    };

    ASSERT_EQ(expression_1, graph_1.connectivityCNF());

    std::vector<std::vector<int>> expression_2 {
            {-1, -5},
            {-2, -9},
    };

    ASSERT_EQ(expression_2, graph_2.connectivityCNF());
}
