//
// Created by daniel on 29/05/22.
//

#include "adjacency_list.h"

void ListGraph::validateNode(int node) const
{
    // Checks if the given node is valid
    if (node < 0 or node >= numNodes())
        throw invalid_node_error();
}

void ListGraph::addNode()
{
    // Adds a new node to the graph
    m_adjacencyList.emplace_back(std::list<int>());
}

bool ListGraph::isEdge(int node_1, int node_2) const
{
    // Check if there is an edge between two nodes
    validateNode(node_1);
    validateNode(node_2);
    if (std::any_of(m_adjacencyList[node_1].begin(),
                    m_adjacencyList[node_1].end(),
                    [node_2](int n) {return n == node_2;}
                    ))
        return true;

    return false;
}

void ListGraph::addEdge(int node_1, int node_2)
{
    // Adds a new edge to the graph
    if (!isEdge(node_1, node_2))
    {
        m_adjacencyList[node_1].push_back(node_2);
        m_adjacencyList[node_2].push_back(node_1);
        m_numEdges++;
    }
}

int ListGraph::numNeighbors(int node) const
{
   // Returns the number of neighbors of a given node
    validateNode(node);
    return static_cast<int>(m_adjacencyList[node].size());
}

std::vector<int> ListGraph::getNeighbors(int node) const
{
    // Returns a vector with the neighbors of a node. It makes a
    // copy of the list of neighbors
    validateNode(node);

    std::vector<int> neighbors(m_adjacencyList[node].size());
    int index {0};
    for (auto neighbor : m_adjacencyList[node])
    {
        neighbors[index] = neighbor;
        index++;
    }
    return neighbors;
}

bool ListGraph::pathBetweenUtil(int currentNode, int endNode,
                                std::vector<bool> &visited) const
{
    // Util function to traverse the graph recursively

    // If the node is reachable then there is a path between them
    if (currentNode == endNode)
        return true;
    bool isReachable {false};

    visited[currentNode] = true;
    for (auto neighbor : m_adjacencyList[currentNode])
    {
        if(!visited[neighbor])
        {
            isReachable = pathBetweenUtil(neighbor, endNode, visited);
            if (isReachable)
                break;
        }
    }
    return isReachable;
}


bool ListGraph::pathBetween(int startNode, int endNode) const
{
    // Returns true if there is a path between the given nodes.
    validateNode(startNode);
    validateNode(endNode);

    std::vector<bool> visited(numNodes(), false);
    return pathBetweenUtil(startNode, endNode, visited);
}

void ListGraph::explore(int currentNode, std::vector<bool> &visited) const
{
    // Explore the nodes reachable from the currenNode
    visited[currentNode] = true;
    for (auto neighbor : m_adjacencyList[currentNode])
    {
        if(!visited[neighbor])
            explore(neighbor, visited);
    }
}

int ListGraph::numConnectedComponents() const
{
    // Returns the number of connected components

    // Do a depth first search while counting the number of connected components
    std::vector<bool> visited(numNodes(), false);
    int connectedComponents {0};

    for (int node {0}; node < numNodes(); ++node)
    {
        if(!visited[node])
        {
            explore(node, visited);
            connectedComponents++;
        }
    }
    return connectedComponents;
}



