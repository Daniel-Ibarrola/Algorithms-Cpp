//
// Created by daniel on 14/06/22.
//

#include "graph_base.h"

void GraphBase::addNode()
{
    // Adds a new node to the graph
    m_adjacencyList.emplace_back(std::list<int>());
}

bool GraphBase::isEdge(int fromNode, int toNode) const
{
    validateNode(fromNode, numNodes());
    validateNode(toNode, numNodes());

    return std::any_of(m_adjacencyList[fromNode].begin(),
                    m_adjacencyList[fromNode].end(),
                    [toNode](int node) {return node == toNode;}
    );
}