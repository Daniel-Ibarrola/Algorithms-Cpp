//
// Created by daniel on 29/05/22.
//

#include "graph.h"

void Graph::validateNode(int node) const
{
    // Checks if the given node is valid
    if (node < 0 or node >= numNodes())
        throw invalid_node_error();
}

void Graph::addNode()
{
    // Adds a new node to the graph
    m_adjacencyList.emplace_back(std::list<int>());
}

bool Graph::isEdge(int node_1, int node_2) const
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

void Graph::addEdge(int node_1, int node_2)
{
    // Adds a new edge to the graph
    if (!isEdge(node_1, node_2))
    {
        m_adjacencyList[node_1].push_back(node_2);
        m_adjacencyList[node_2].push_back(node_1);
        m_numEdges++;
    }
}

void Graph::addEdges(const std::vector<std::tuple<int, int>> &edges)
{
    // Add multiple edges to the graph
    for(const auto& nodes : edges)
        addEdge(std::get<0>(nodes), std::get<1>(nodes));
}

void Graph::addEdgesToNode(int node, const std::vector<int> &toNodes)
{
    // Add multiple edges to the given node
    for (auto n: toNodes)
        addEdge(node, n);
}

int Graph::numNeighbors(int node) const
{
   // Returns the number of neighbors of a given node
    validateNode(node);
    return static_cast<int>(m_adjacencyList[node].size());
}

std::vector<int> Graph::getNeighbors(int node) const
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

bool Graph::pathBetweenUtil(int currentNode, int endNode,
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


bool Graph::pathBetween(int startNode, int endNode) const
{
    // Returns true if there is a path between the given nodes.
    validateNode(startNode);
    validateNode(endNode);

    std::vector<bool> visited(numNodes(), false);
    return pathBetweenUtil(startNode, endNode, visited);
}

void Graph::explore(int currentNode, std::vector<bool> &visited) const
{
    // Explore the nodes reachable from the currenNode
    visited[currentNode] = true;
    for (auto neighbor : m_adjacencyList[currentNode])
    {
        if(!visited[neighbor])
            explore(neighbor, visited);
    }
}

int Graph::numConnectedComponents() const
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

std::vector<int> Graph::distancesFromNode(int node)
{
    // Returns a vector with the distances from all nodes to the given node
    // Uses a breadth first search traversal to find the distances.
    validateNode(node);

    std::vector<int> distances(m_adjacencyList.size(),
                               std::numeric_limits<int>::max());
    distances[node] = 0;
    std::queue<int> queue;
    queue.push(node);

    while (!queue.empty())
    {
        int currentNode {queue.front()};
        queue.pop();
        for (int neighbor : m_adjacencyList[currentNode])
        {
            // Traverse the adjacency list of the node but only consider
            // nodes that have not been visited (their distance is max)
            if (distances[neighbor] == std::numeric_limits<int>::max())
            {
                queue.push(neighbor);
                distances[neighbor] = distances[currentNode] + 1;
            }
        }
    }

    return distances;
}

int Graph::shortestPath(int startNode, int endNode)
{
    // Returns the shortest path form startNode to endNode.
    // -1 is returned if there is no path between the given nodes.
    int distance {distancesFromNode(startNode)[endNode]};
    if (distance == std::numeric_limits<int>::max())
        return -1;
    return distance;
}

