//
// Created by daniel on 6/09/22.
//

#include "hamiltonian_cycle.h"


void HCGraph::createMatrix(const std::vector<std::pair<int, int>> &edgeList)
{
    // Create the adjacency matrix of the graph

    // Add connectivity information
    for (const auto& edge: edgeList)
    {
        m_adMatrix[edge.first - 1][edge.second - 1] = true;
        m_adMatrix[edge.second - 1][edge.first - 1] = true;
    }
}


void HCGraph::connectivityCNF(matrix& clauses) const
{
    // Returns a CNF formula for the nodes that are not connected
    std::size_t nodes {m_adMatrix.size()};
    for (auto ii {0}; ii < nodes; ++ii)
    {
        for (auto jj {0}; jj < nodes; ++jj)
        {
            if (ii != jj && !m_adMatrix[ii][jj])
            {
                for (auto kk {0}; kk < nodes - 1; ++kk)
                {
                    int lit_1 {-(1 + static_cast<int>(nodes*ii + kk))};
                    int lit_2 {-(2 + static_cast<int>(nodes*jj + kk))};
                    clauses.push_back({lit_1, lit_2});
                }
            }
        }
    }
}


matrix hamiltonianCycleCNF(int numNodes,
                           const std::vector<std::pair<int, int>>& edgeList)
{
    // Returns a CNF formula for the hamiltonian cycle for the given graph
    matrix expression;

    nodeBelongsToPath(numNodes, expression);
    nodeAppearsOnce(numNodes, expression);
    positionsOccupied(numNodes, expression);
    differentPositions(numNodes, expression);

    HCGraph graph(edgeList, numNodes);
    graph.connectivityCNF(expression);

    return expression;
}


matrix nodeBelongsToPath(int numNodes, matrix& clauses)
{
    // Constrain each vertex to belong to a path
    int literal {1};
    for (auto ii {0}; ii < numNodes; ++ii)
    {
        clauses.push_back({});
        for (auto jj {0}; jj < numNodes; ++jj)
        {
            clauses[ii].push_back(literal);
            literal++;
        }
    }
    return clauses;
}


matrix nodeAppearsOnce(int numNodes, matrix& clauses)
{
    // Constrain each vertex to appear only once in the path

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


matrix positionsOccupied(int numNodes, matrix& clauses)
{
    // Constrain each position in a path to be occupied by some vertex
    int start {1};
    std::size_t iterEnd {clauses.size() + numNodes};
    for (auto ii {clauses.size()}; ii < iterEnd; ++ii)
    {
        clauses.push_back({});
        for (int jj {0}; jj <  numNodes; ++jj)
            clauses[ii].push_back(start + jj * numNodes);
        start++;
    }
    return clauses;
}


matrix differentPositions(int numNodes, matrix& clauses)
{
    // Constrain that does not allow two vertices to occupy the same
    // position of a path

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
