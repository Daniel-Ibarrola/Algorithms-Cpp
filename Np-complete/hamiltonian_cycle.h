//
// Created by daniel on 6/09/22.
//

#ifndef ALGORITHMS_HAMILTONIAN_CYCLE_H
#define ALGORITHMS_HAMILTONIAN_CYCLE_H

#include <utility>  // std::pair
#include <vector>

using matrix = std::vector<std::vector<int>>;

matrix hamiltonianCycleCNF(int numNodes,
                           const std::vector<std::pair<int, int>>& edgeList);

matrix nodeBelongsToPath(int numNodes);

matrix nodeAppearsOnce(int numNodes);

matrix positionsOccupied(int numNodes);

matrix differentPositions(int numNodes);

matrix connectivity(int numNodes,
                    const std::vector<std::pair<int, int>>& edgeList);

#endif //ALGORITHMS_HAMILTONIAN_CYCLE_H
