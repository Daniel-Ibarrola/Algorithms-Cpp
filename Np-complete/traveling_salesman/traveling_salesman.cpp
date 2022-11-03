//
// Created by daniel on 17/10/22.
//

#include "traveling_salesman.h"


std::vector<int> TSGraph::travelingSalesmanPath() const
{
    // Returns
    return {};
}


int TSGraph::travelingSalesmanRec(int mask, int index,
                                  std::vector<std::vector<int>>& cost) const
{
    // Find the optimal weight of the tsp using recursion with memoization
    //  mask: represents the subset of visited node by using a bitmask
    //  index: is the current node index

    // Base case: all nodes are visited. The bitmask consists of only 1's
    if (mask == (1 << numNodes()) - 1)
        return m_adjMatrix[index][0];

    if (cost[mask][index] != -1)
        return cost[mask][index];

    int optDist {std::numeric_limits<int>::max()};
    for (auto node {0}; node < numNodes(); ++node)
    {
        // Check if node has not been visited
        if ((mask & (1 << node)) == 0)
        {
            int newDist {m_adjMatrix[index][node] + travelingSalesmanRec(
                    mask | (1 << node), // mark the node as visited
                    node, cost
                    )};
            optDist = std::min(newDist, optDist);
        }
    }

    cost[mask][index] = optDist;
    return cost[mask][index];
}


int TSGraph::travelingSalesmanWeight() const
{
    // Returns the optimal weight of the traveling salesman problem.

    // 1 is the mask where only the initial city has been visited
    std::vector<std::vector<int>> cost(1 << numNodes(),
                                       std::vector<int>(numNodes(), -1));
    return travelingSalesmanRec(1, 0, cost);
}
