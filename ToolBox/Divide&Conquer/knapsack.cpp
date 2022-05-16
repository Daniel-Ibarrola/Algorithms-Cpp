//
// Created by daniel on 9/05/22.
//

#include "knapsack.h"

template <std::size_t size>
int knapsack(const std::array<int, size>& weights, const std::array<int, size>& profits,
             int knapsackWeight, int item)
{
    // Returns the optimal value of profit for a knapsack with a certain weight using a
    // recursive algorithm

    // Base case
    if (knapsackWeight == 0 || item == 0)
        return 0;

    if (weights[item] > knapsackWeight)
        return knapsack(weights, profits, knapsackWeight, item - 1);
    else
        return std::max(knapsack(weights, profits, knapsackWeight, item - 1),
                        profits[item] + knapsack(weights, profits, knapsackWeight - weights[item], item - 1));
}