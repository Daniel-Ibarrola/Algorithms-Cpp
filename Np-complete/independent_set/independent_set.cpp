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


int WeightedTree::maxWeightRec(int currentNode, std::vector<int> &dp)
{
    // Helper function for maxISWeight

    if (dp[currentNode] == std::numeric_limits<int>::max())
    {
        // Base Case: if it's a leave node, include it
        if (!m_nodes[currentNode].hasChildren())
            dp[currentNode] = m_nodes[currentNode].getWeight();
        else
        {
            // If we include the node, we can take its grandchildren but not it's children.
            int include {m_nodes[currentNode].getWeight()};
            for (auto child : m_nodes[currentNode].getChildren())
            {
                for (auto grandchild : m_nodes[child].getChildren())
                    include += maxWeightRec(grandchild, dp);
            }

            // If we do not include the node, we can only take its children.
            int exclude {0};
            for (auto child : m_nodes[currentNode].getChildren())
                exclude += maxWeightRec(child, dp);
            dp[currentNode] = std::max(include, exclude);
        }
    }
    return dp[currentNode];
}


int WeightedTree::maxISWeight()
{
    // Returns the weight of the independent set with maximum
    // weight.

    // We use dynamic programming with memoization. Initialize the dp
    // array which will contain the optimal value for each tree roted
    // at the ith node
    std::vector<int> dp(size(), std::numeric_limits<int>::max());
    return maxWeightRec(0, dp);
}