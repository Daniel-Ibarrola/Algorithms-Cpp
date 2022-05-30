//
// Created by daniel on 29/05/22.
//

#include "adjacency_matrix.h"


void MatrixGraph::validateNode(int node) const
{
    // Check if the given node is a valid node of the graph
    if (node < 0 || node >= m_adjMatrix.size())
        throw invalid_node_error();
}

void MatrixGraph::addEdge(int node_1, int node_2)
{
    // Add an edge to the graph
    validateNode(node_1);
    validateNode(node_2);

    m_adjMatrix[node_1][node_2] = true;
    m_adjMatrix[node_2][node_1] = true;
    m_numEdges++;
}

bool MatrixGraph::isEdge(int node_1, int node_2) const
{
    // Returns true if there is an edge between the given nodes.
    // false otherwise
    validateNode(node_1);
    validateNode(node_2);

    return m_adjMatrix[node_1][node_2];
}

int MatrixGraph::numNeighbors(int node) const
{
    // Returns the number of neighbors of the given node
    validateNode(node);

    int neighbors {0};
    for (auto node_ : m_adjMatrix[node])
    {
        if (node_)
            neighbors++;
    }
    return neighbors;
}

std::vector<int> MatrixGraph::getNeighbors(int node) const
{
    // Returns a vector with the neighbors of the given node
    validateNode(node);

    std::vector<int> neighbors;
    for (int ii {0}; ii < numNodes(); ++ii)
    {
        if (m_adjMatrix[node][ii])
            neighbors.push_back(ii);
    }

    return neighbors;
}