//
// Created by daniel on 29/05/22.
//

#include "graph.h"

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
    validateNode(node, numNodes());
    return static_cast<int>(m_adjacencyList[node].size());
}

std::vector<int> Graph::getNeighbors(int node) const
{
    // Returns a vector with the neighbors of a node. It makes a
    // copy of the list of neighbors
    validateNode(node, numNodes());

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
    validateNode(startNode, numNodes());
    validateNode(endNode, numNodes());

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

std::vector<int> Graph::distancesFromNode(int node) const
{
    // Returns a vector with the distances from all nodes to the given node
    // Uses a breadth first search traversal to find the distances.
    validateNode(node, numNodes());

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

int Graph::shortestPath(int startNode, int endNode) const
{
    // Returns the shortest path form startNode to endNode.
    // -1 is returned if there is no path between the given nodes.
    int distance {distancesFromNode(startNode)[endNode]};
    if (distance == std::numeric_limits<int>::max())
        return -1;
    return distance;
}

bool Graph::isBipartiteUtil(int node, std::vector<int>& colors) const
{
    // Util function to color the nodes reachable from the given node

    // The graph is bipartite if its nodes can be colored by two different colors
    // such that any two adjacent nodes have different colors.
    // We use a breadth first search approach for coloring the graph

    // In the following vector -1 will represent a node that has not been visited.
    // 0 will be the first color and 1 the second color.
    std::queue<int> queue;
    queue.push(node);
    colors[node] = 1;

    while (!queue.empty())
    {
        int currentNode {queue.front()};
        queue.pop();
        for (int neighbor : m_adjacencyList[currentNode])
        {
            if (colors[neighbor] == colors[currentNode])
                return false;
            if (colors[neighbor] == -1)
            {
                colors[neighbor] = 1 - colors[currentNode];
                queue.push(neighbor);
            }

        }
    }

    return true;
}

bool Graph::isBipartite() const
{
    // Returns true if the graph is bipartite.
    std::vector<int> colors(m_adjacencyList.size(), -1);
    for (int node {0}; node < numNodes(); ++node)
    {
        if (colors[node] == -1 && !isBipartiteUtil(node, colors))
            return false;
    }
    return true;
}