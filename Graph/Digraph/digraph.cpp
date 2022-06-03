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

void Digraph::topologicalOrderUtil(int currentNode,
                                   std::vector<bool> &visited,
                                   std::stack<int> &stack) const
{
    // Util function to find the topological ordering of the graph
    // by using DFS

    visited[currentNode] = true;
    for (auto node : m_adjacencyList[currentNode])
    {
        if (!visited[node])
            topologicalOrderUtil(node, visited, stack);
    }

    stack.push(currentNode);
}


std::vector<int> Digraph::topologicalOrder() const
{
    // Returns a vector with the topological order of the graph

    // For cyclic graphs topological ordering is not possible, so we return empty vec
    if (isCyclic())
        return {};

    std::vector<bool> visited(m_adjacencyList.size(), false);
    std::stack<int> stack;
    for(int node {0}; node < numNodes(); ++node)
    {
        if (!visited[node])
            topologicalOrderUtil(node, visited, stack);
    }
    assert(stack.size() == m_adjacencyList.size() && "Stack does not contain all nodes");

    std::vector<int> topOrder(m_adjacencyList.size());
    for (auto ii {0}; ii < topOrder.size(); ++ii)
    {
        topOrder[ii] = stack.top();
        stack.pop();
    }
    assert(stack.empty() && "Stack isn't empty");

    return topOrder;
}

int Digraph::numStronglyConnectedComponents() const
{
    // Returns the number of strongly connected components in the graph
    return 0;
}

Digraph Digraph::reverseGraph() const
{
    // Returns the reverse graph (the graph obtained by reversing all the edges).
    Digraph reverse(numNodes());
    for (int node_1 {0}; node_1 < numNodes(); ++node_1)
    {
        for (auto node_2 : m_adjacencyList[node_1])
            reverse.addEdge(node_2, node_1);
    }
    return reverse;
}
