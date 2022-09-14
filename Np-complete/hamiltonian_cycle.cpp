//
// Created by daniel on 6/09/22.
//

#include "hamiltonian_cycle.h"


void HCGraph::createMatrix(const std::vector<std::pair<int, int>> &edgeList)
{
    // Create the adjacency matrix of the graph

    std::size_t numNodes {edgeList.size()};
    // First create a vector of bool for each node
    for (auto ii {0}; ii < numNodes; ++ii)
    {
        std::vector<bool> row(numNodes - ii , false);
        m_adMatrix[ii] = row;
    }

    // Add connectivity information
    for (const auto& edge: edgeList)
    {
        if (edge.first < edge.second)
            m_adMatrix[edge.first - 1][edge.second - edge.first - 1] = true;
        else if (edge.first > edge.second)
            m_adMatrix[edge.second - 1][edge.first - edge.second - 1] = true;
    }
}


void HCGraph::createClauses(int node_1, int node_2,
                            int numNodes,
                            matrix &clauses)
{
    // Creates the clauses for the connectivityCNF method
    int literal_1 {-(numNodes * (node_1 - 1) + 1)};
    int literal_2 {-(numNodes * (node_2 - 1) + 2)};

    for (auto ii {0}; ii < numNodes - 1; ++ii)
    {
        clauses.push_back({literal_1, literal_2});
        literal_1--;
        literal_2--;
    }
}


void HCGraph::connectivityCNF(matrix& clauses) const
{
    // Returns a CNF formula for the nodes that are not connected
    int numNodes {static_cast<int>(m_adMatrix.size() + 1)};

    for (auto ii {0}; ii < m_adMatrix.size(); ++ii)
    {
        for (auto jj {0}; jj < m_adMatrix[ii].size(); ++jj)
        {
            // If there is no edge create a set of clauses
            if (!m_adMatrix[ii][jj])
            {
                createClauses(ii + 1, jj + ii + 2, numNodes, clauses);
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
