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

bool Digraph::isCyclicUtil(int currentNode, std::vector<int> &colors) const
{
    // Util function to find if there are cycles in the graph by depth first search

    // Mark the current node as being processed
    colors[currentNode] = gray;

    for (auto node : m_adjacencyList[currentNode])
    {
        // If the color is gray we have found a cycle
        if (colors[node] == gray)
            return true;

        if (colors[node] == white && isCyclicUtil(node, colors))
            return true;
    }

    // No cycle was found. Mark the node as completely processed
    colors[currentNode] = black;
    return false;
}


bool Digraph::isCyclic() const
{
    // Returns true if the graph has a cycle

    // We use the coloring method to determine if there are cycles.
    // Initialize a vector which marks all nodes as unprocessed
    std::vector<int> colors(m_adjacencyList.size(), white);
    for (int node {0}; node < m_adjacencyList.size(); ++node)
    {
        if (isCyclicUtil(node, colors))
            return true;
    }
    return false;
}

