//
// Created by daniel on 9/05/22.
//

#ifndef ALGORITHMS_KNAPSACK_H
#define ALGORITHMS_KNAPSACK_H

#include <utility>
#include <vector>

class Knapsack
{
private:
    std::vector<int> m_weights;
    std::vector<int> m_profits;
    int m_weight;

public:

    explicit Knapsack(int weight)
        : m_weight {weight}
    {

    }

    Knapsack(int weight, std::vector<int>  weights, std::vector<int>  profits)
        : m_weight {weight}, m_weights {std::move(weights)}, m_profits {std::move(profits)}
    {

    }

    void addItem(int itemWeight, int profit);

    int getWeight() const {return m_weight;}

    void setKnapsackWeight(int weight) {m_weight = weight;}

    int maxProfit() const;

};

#endif //ALGORITHMS_KNAPSACK_H
