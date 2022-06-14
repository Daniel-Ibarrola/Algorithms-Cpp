//
// Created by daniel on 14/06/22.
//

#ifndef ALGORITHMS_GRAPH_BASE_H
#define ALGORITHMS_GRAPH_BASE_H

#include <algorithm> // std::any_of
#include <list>
#include <vector>
#include "validate_node.h"

class GraphBase
{
    // Base class for unweighted graphs. Graph and Digraph will inherit from this class.
protected:
    std::vector<std::list<int>> m_adjacencyList;
    int m_numEdges {0};

public:

    GraphBase() = default;

    explicit GraphBase(int numNodes)
        : m_adjacencyList(numNodes, std::list<int>())
    {

    }

    int numNodes() const {return static_cast<int>(m_adjacencyList.size());}
    int numEdges() const {return m_numEdges;}

    void addNode();

    bool isEdge(int fromNode, int toNode) const;
};

#endif //ALGORITHMS_GRAPH_BASE_H
