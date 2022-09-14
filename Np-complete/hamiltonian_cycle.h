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
using adjMatrix = std::vector<std::vector<bool>>;


class HCGraph
{
    // Graph to obtain a CNF formula for a hamiltonian path
private:
    // Graph is represented by a sparse adjacency matrix
    adjMatrix m_adMatrix;

    void createMatrix(const std::vector<std::pair<int, int>>& edgeList);

public:

    HCGraph(const std::vector<std::pair<int, int>>& edgeList, int numNodes)
        : m_adMatrix(numNodes - 1)
    {
        createMatrix(edgeList);
    }

    std::size_t numNodes() const { return m_adMatrix.size() + 1; }
    adjMatrix & getAdjacencyMatrix() { return m_adMatrix; }
    matrix connectivityCNF() const;
};


matrix hamiltonianCycleCNF(int numNodes,
                           const std::vector<std::pair<int, int>>& edgeList);

matrix nodeBelongsToPath(int numNodes);

matrix nodeAppearsOnce(int numNodes);

matrix positionsOccupied(int numNodes);

matrix differentPositions(int numNodes);


#endif //ALGORITHMS_HAMILTONIAN_CYCLE_H
