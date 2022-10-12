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
    // Graph is represented by an adjacency matrix
    adjMatrix m_adMatrix;

    void createMatrix(const std::vector<std::pair<int, int>>& edgeList);

public:

    HCGraph(const std::vector<std::pair<int, int>>& edgeList, int numNodes)
        : m_adMatrix(numNodes, std::vector<bool>(numNodes, false))
    {
        createMatrix(edgeList);
    }

    [[nodiscard]] std::size_t numNodes() const { return m_adMatrix.size(); }
    adjMatrix & getAdjacencyMatrix() { return m_adMatrix; }
    void connectivityCNF(matrix& clauses) const;

};


matrix hamiltonianCycleCNF(int numNodes,
                           const std::vector<std::pair<int, int>>& edgeList);

matrix nodeBelongsToPath(int numNodes, matrix& clauses);

matrix nodeAppearsOnce(int numNodes, matrix& clauses);

matrix positionsOccupied(int numNodes, matrix& clauses);

matrix differentPositions(int numNodes, matrix& clauses);


#endif //ALGORITHMS_HAMILTONIAN_CYCLE_H
