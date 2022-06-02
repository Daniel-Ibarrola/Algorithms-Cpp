//
// Created by daniel on 2/06/22.
//

#include "digraph.h"

void Digraph::validateNode(int node) const
{
    // Check if a node is part of the graph
    if (node < 0 || node >= m_adjacencyList.size())
        throw invalid_node_error();
}

void Digraph::addEdge(int outNode, int inNode)
{
    // Adds an edge that goes from the outNode to the inNode
    if (!isEdge(outNode, inNode))
    {
        m_adjacencyList[outNode].push_back(inNode);
        m_numEdges++;
    }
}

void Digraph::addNode()
{
    // Adds a new node to the graph
    m_adjacencyList.emplace_back(std::list<int>());
}

bool Digraph::isEdge(int outNode, int inNode) const
{
    // Check if there is an edge that goes from the outNode to the inNode
    validateNode(outNode);
    validateNode(inNode);

    if (std::any_of(m_adjacencyList[outNode].begin(),
                    m_adjacencyList[outNode].end(),
                    [inNode](int node) {return node == inNode;}
                    ))
        return true;

    return false;
}

int Digraph::numOutEdges(int node) const
{
    // Returns the number of outgoing edges from the given node
    validateNode(node);
    return static_cast<int>(m_adjacencyList[node].size());
}

std::list<int> Digraph::getOutNeighbors(int node) const
{
    // Returns a list with the outNeighbors of a node. Makes a copy of the list
    return m_adjacencyList[node];
}