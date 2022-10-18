//
// Created by daniel on 17/10/22.
//

#include "traveling_salesman.h"


int TSGraph::getWeight(int start, int end) const
{
    // Gets the edge weight between two nodes
    for (const auto& edge : m_adjacencyList[start])
    {
        if (edge.end == end)
            return edge.weight;
    }
    return -1;
}

std::vector<int> TSGraph::travelingSalesmanPath() const
{
    // Returns
    return {};
}


int TSGraph::travelingSalesmanWeight() const
{
    // Returns
    return 0;
}
