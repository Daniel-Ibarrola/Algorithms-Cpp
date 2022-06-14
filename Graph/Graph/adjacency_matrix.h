//
// Created by daniel on 29/05/22.
//

#ifndef ALGORITHMS_ADJACENCY_MATRIX_H
#define ALGORITHMS_ADJACENCY_MATRIX_H

#endif //ALGORITHMS_ADJACENCY_MATRIX_H

#include <vector>
#include <iostream>
#include "validate_node.h"


class MatrixGraph
{
    // Simple unweighted graph representation using an adjacency matrix.
private:
    std::vector<std::vector<bool>> m_adjMatrix;
    int m_numEdges {0};

    void validateNode(int node) const;

public:

    explicit MatrixGraph(int numNodes) :
        m_adjMatrix(numNodes, std::vector<bool>(numNodes, false))
    {
        // Constructor initializes a matrix of shape (numNodes, numNodes) with zeros or false
    }

    int numNodes() const {return static_cast<int>(m_adjMatrix.size());}

    int numEdges() const {return m_numEdges;}

    void addEdge(int node_1, int node_2);

    bool isEdge(int node_1, int node_2) const;

    int numNeighbors(int node) const;

    std::vector<int> getNeighbors(int node) const;

};