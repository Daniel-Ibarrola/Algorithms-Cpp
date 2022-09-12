//
// Created by daniel on 6/09/22.
//

#include "hamiltonian_cycle.h"


matrix hamiltonianCycleCNF(int numNodes,
                           const std::vector<std::pair<int, int>>& edgeList)
{
    // Returns a CNF for the hamiltonian cycle for the given graph
    return {};
}

matrix nodeBelongsToPath(int numNodes)
{
    // Constrain each vertex to belong to a path
    matrix clauses (numNodes);
    int literal {1};
    for (int ii {0}; ii < clauses.size(); ++ii)
    {
        for (auto jj {0}; jj < numNodes; ++jj)
        {
            clauses[ii].push_back(literal);
            literal++;
        }
    }
    return clauses;
}

matrix nodeAppearsOnce(int numNodes)
{
    // Constrain each vertex to appear only once in the path
    matrix clauses {};
    int numLiterals {numNodes * numNodes};

    int literal {-1};
    for (int ii {0}; ii < numNodes; ++ii)
    {
        for (int jj {0}; jj < numNodes; ++jj)
        {
            for (int kk {0}; kk < numNodes; ++kk)
            {
                clauses.push_back({literal, literal - jj});
            }
        }
    }
    return clauses;
}

matrix positionsOccupied(int numNodes)
{
    // Constrain each position in a path to be occupied by some vertex
    return {};
}

matrix differentPositions(int numNodes)
{
    // Constrain that does not allow two vertices to occupy the same
    // position of a path
    return {};
}

matrix connectivity(int numNodes,
                    const std::vector<std::pair<int, int>>& edgeList)
{
    // Constrain to successive vertices on a path to be connected by an edge
    return {};
}