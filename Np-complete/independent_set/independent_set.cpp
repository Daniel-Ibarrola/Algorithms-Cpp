//
// Created by daniel on 12/10/22.
//

#include "independent_set.h"


void WeightedTree::build(const std::vector<std::pair<int, int>> &nodes,
                         const std::vector<int> &weights)
{
    // Builds the tree

    for (auto ii {0}; ii < weights.size(); ++ii)
        m_nodes[ii].setWeight(weights[ii]);

    for (auto nodePair : nodes)
        m_nodes[nodePair.first - 1].addChild(nodePair.second - 1);
}


int WeightedTree::maxISWeight()
{
    // Returns the weight of the independent set with maximum
    // weight.
    return 0;
}