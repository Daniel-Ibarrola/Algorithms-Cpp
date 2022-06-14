//
// Created by daniel on 12/06/22.
//

#include "weighted_digraph.h"

bool operator==(const Edge& edge_1, const Edge& edge_2)
{
    // Returns true if two Edge structs are equal
    return edge_1.toNode == edge_2.toNode && edge_1.weight == edge_2.weight;
}


void WeightedDigraph::addEdge(int fromNode, int toNode, int weight)
{
    // Add an edge from "fromNode" to "toNode" with the given weight
    if (!isEdge(fromNode, toNode))
    {
        m_adjacencyList[fromNode].emplace_back(Edge {toNode, weight});
        ++m_numEdges;
    }
}

void WeightedDigraph::addEdges(const std::vector<std::array<int, 3>>& edgeList)
{
    // Add multiple edges to the graph. A vector of arrays of size 3 is required, where
    // the first element of the array is the "from node", the second element is the
    // "to node" and the third elements is the weight of the edge.
    for (const auto& edge: edgeList)
        addEdge(edge[0], edge[1], edge[2]);
}

int WeightedDigraph::getWeight(int fromNode, int toNode) const
{
    // Returns the weight of the given edge
    validateNode(fromNode, numNodes());
    validateNode(toNode, numNodes());

    for (const auto& edge: m_adjacencyList[fromNode])
    {
        if (edge.toNode == toNode)
            return edge.weight;
    }
}

bool WeightedDigraph::isEdge(int fromNode, int toNode) const
{
    // Returns true if there is and edge from "fromNode" to "toNode"
    validateNode(fromNode, numNodes());
    validateNode(toNode, numNodes());

    return std::any_of(m_adjacencyList[fromNode].begin(),
                    m_adjacencyList[fromNode].end(),
                    [toNode](Edge edge) {return edge.toNode == toNode;}
                    );
}

void WeightedDigraph::addNode()
{
    // Adds a new node to the graph
    m_adjacencyList.emplace_back(std::list<Edge>());
}

int WeightedDigraph::outDegree(int node) const
{
    // Returns the out-degree of the given node
    validateNode(node, numNodes());
    return static_cast<int>(m_adjacencyList[node].size());
}

const std::list<Edge>& WeightedDigraph::getOutNeighbors(int node) const
{
    // Returns a list with the out neighbors of the given node
    validateNode(node, numNodes());
    return m_adjacencyList[node];
}

std::vector<int> WeightedDigraph::getDistances(int startNode) const
{
    // Returns a vector with the minimum weight distances from startNode to all
    // the other nodes in the graph
    validateNode(startNode, numNodes());

    // At first no nodes have been discovered so, we set their distances to max
    std::vector<int> distances(m_adjacencyList.size(), std::numeric_limits<int>::max());
    distances[startNode] = 0;
    // Create a min-heap that stores the nodes by their distance
    auto compare = [](Edge edge_1, Edge edge_2)
        { return edge_1.weight > edge_2.weight; };
    std::priority_queue<Edge, std::vector<Edge>, decltype(compare)> heap(compare);
    heap.push(Edge{startNode, 0});

    while (!heap.empty())
    {
        int node {heap.top().toNode};
        heap.pop();
        for (const auto& neighbor : m_adjacencyList[node])
        {
            // If we find a shorter path we update the distance
            if (distances[neighbor.toNode] > distances[node] + neighbor.weight)
            {
                distances[neighbor.toNode] = distances[node] + neighbor.weight;
                heap.push(Edge{neighbor.toNode, distances[neighbor.toNode]});
            }
        }
    }

    return distances;
}

int WeightedDigraph::shortestPathLength(int startNode, int endNode) const
{
    // Returns the shortest path between startNode and endNode.
    // All weights in the graph must be positive for it to work
    validateNode(startNode, numNodes());
    validateNode(endNode, numNodes());

    int length {getDistances(startNode)[endNode]};
    if (length == std::numeric_limits<int>::max())
        return -1;
    return length;
}

std::vector<int> WeightedDigraph::shortestPathsBF(int startNode) const
{
    // Returns a vector with the length of the shortest path from the given node
    // to every other node. The graph must not contain negative cycles
    return {};
}

bool WeightedDigraph::hasNegativeCycle() const
{
    // Returns true if the graph has a negative cycle.
    return false;
}

