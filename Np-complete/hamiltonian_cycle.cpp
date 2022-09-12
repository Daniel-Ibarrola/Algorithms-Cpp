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
    for (auto ii {0}; ii < clauses.size(); ++ii)
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

    // Create a vector to store all the literals corresponding to a node
    std::vector<int> nodeLiterals (numNodes);
    int start {1};

    for (auto kk {0}; kk < nodeLiterals.size(); ++kk)
    {
        std::iota(nodeLiterals.begin(), nodeLiterals.end(), start);
        // Now we get all pair combinations fot this vector and repeat for each node
        for (auto ii {0}; ii < nodeLiterals.size(); ++ii)
        {
            for (auto jj {ii + 1}; jj < nodeLiterals.size(); ++jj)
                clauses.push_back({-nodeLiterals[ii], -nodeLiterals[jj]});
        }
        start += numNodes;
    }

    return clauses;
}

matrix positionsOccupied(int numNodes)
{
    // Constrain each position in a path to be occupied by some vertex
    matrix clauses (numNodes);
    int start {1};
    for (auto ii {0}; ii < clauses.size(); ++ii)
    {
        for (int jj {0}; jj <  numNodes; ++jj)
            clauses[ii].push_back(start + jj * numNodes);
        start++;
    }
    return clauses;
}

matrix differentPositions(int numNodes)
{
    // Constrain that does not allow two vertices to occupy the same
    // position of a path
    matrix clauses {};

    // Create a vector to store all the literals corresponding to a position
    std::vector<int> pathLiterals (numNodes);
    int start {1};

    for (auto kk {0}; kk < pathLiterals.size(); ++kk)
    {
        for (auto ll {0}; ll < pathLiterals.size(); ++ll)
        {
            pathLiterals[ll] = start + (static_cast<int>(ll) * numNodes);
        }
        // Now we get all pair combinations fot this vector and repeat for each node
        for (auto ii {0}; ii < pathLiterals.size(); ++ii)
        {
            for (auto jj {ii + 1}; jj < pathLiterals.size(); ++jj)
                clauses.push_back({-pathLiterals[ii], -pathLiterals[jj]});
        }
        start++;
    }

    return clauses;
}
