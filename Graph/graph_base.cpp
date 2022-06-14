//
// Created by daniel on 14/06/22.
//

#include "graph_base.h"

// Unweighted graph

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

// Edge struct

bool operator==(const Edge& edge_1, const Edge& edge_2)
{
    // Returns true if two Edge structs are equal
    return edge_1.toNode == edge_2.toNode && edge_1.weight == edge_2.weight;
}


// Weighted Graph

bool WeightedGraphBase::isEdge(int fromNode, int toNode) const
{
    // Returns true if there is and edge from "fromNode" to "toNode"
    validateNode(fromNode, numNodes());
    validateNode(toNode, numNodes());

    return std::any_of(m_adjacencyList[fromNode].begin(),
                       m_adjacencyList[fromNode].end(),
                       [toNode](Edge edge) {return edge.toNode == toNode;}
    );
    return false;
}

void WeightedGraphBase::addNode()
{
    // Adds a new node to the graph
    m_adjacencyList.emplace_back(std::list<Edge>());
}


int WeightedGraphBase::getWeight(int fromNode, int toNode) const
{
    // Returns the weight of the given edge
    validateNode(fromNode, numNodes());
    validateNode(toNode, numNodes());

    for (const auto& edge: m_adjacencyList[fromNode])
    {
        if (edge.toNode == toNode)
            return edge.weight;
    }

    assert(false && "Edge was not found");
    return -1;
}