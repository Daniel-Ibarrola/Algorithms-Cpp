//
// Created by daniel on 6/09/22.
//
#include "gtest/gtest.h"
#include "hamiltonian_cycle.h"


TEST(TestHamiltonianCycle, CNFFormulaForHamiltonianPath)
{
    int numNodes {3};
    std::vector<std::pair<int, int>> edgeList {{1, 2}, {2, 3}};
    std::vector<std::vector<int>> expectedExpression {
            // Constrain 1
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
            // Constrain 2
            {-1, -2},
            {-1, -3},
            {-2, -3},
            {-4, -5},
            {-4, -6},
            {-5, -6},
            {-7, -8},
            {-7, -9},
            {-8, -9},
            // Constrain 3
            {1, 4, 7},
            {2, 5, 8},
            {3, 6, 9},
            // Constrain 4
            {-1, -4},
            {-1, -7},
            {-2, -7},
            {-2, -5},
            {-2, -8},
            {-5, -8},
            {-3, -6},
            {-3, -9},
            {-6, -9},
            // Constrain 5
            {-1, -5},
            {-2, -9},
    };
}