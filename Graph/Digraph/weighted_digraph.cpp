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