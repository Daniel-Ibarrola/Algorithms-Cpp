//
// Created by daniel on 9/05/22.
//

#ifndef ALGORITHMS_KNAPSACK_H
#define ALGORITHMS_KNAPSACK_H

#include <array>

template <std::size_t size>
int knapsack(const std::array<int, size>& weights, const std::array<int, size>& profits,
             int knapsackWeight, int item);

#endif //ALGORITHMS_KNAPSACK_H
