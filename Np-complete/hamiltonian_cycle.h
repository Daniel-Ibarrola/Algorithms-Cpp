//
// Created by daniel on 6/09/22.
//

#ifndef ALGORITHMS_HAMILTONIAN_CYCLE_H
#define ALGORITHMS_HAMILTONIAN_CYCLE_H

#include <numeric>
#include <utility>  // std::pair
#include <vector>
#include "Graph/graph.h"

using matrix = std::vector<std::vector<int>>;


class HCGraph
{
    // Graph to obtain a CNF formula for a hamiltonian path
private:
    matrix m_adjacencyList;

public:

    HCGraph(const std::vector<std::pair<int, int>>& edgeList, int numNodes)
    {

    }
};


matrix hamiltonianCycleCNF(int numNodes,
                           const std::vector<std::pair<int, int>>& edgeList);

matrix nodeBelongsToPath(int numNodes);

matrix nodeAppearsOnce(int numNodes);

matrix positionsOccupied(int numNodes);

matrix differentPositions(int numNodes);


#endif //ALGORITHMS_HAMILTONIAN_CYCLE_H
