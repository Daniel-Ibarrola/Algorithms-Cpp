//
// Created by daniel on 14/06/22.
//

#ifndef ALGORITHMS_GRAPH_BASE_H
#define ALGORITHMS_GRAPH_BASE_H

#include <algorithm> // std::any_of
#include <cassert>
#include <list>
#include <vector>
#include "validate_node.h"

class GraphBase
{
    // Base class for unweighted graphs. Graph and Digraph will inherit from this class.
protected:
    std::vector<std::list<int>> m_adjacencyList;
    int m_numEdges {0};

public:

    GraphBase() = default;

    explicit GraphBase(int numNodes)
        : m_adjacencyList(numNodes, std::list<int>())
    {

    }

    int numNodes() const {return static_cast<int>(m_adjacencyList.size());}
    int numEdges() const {return m_numEdges;}

    void addNode();

    bool isEdge(int fromNode, int toNode) const;
};

#endif //ALGORITHMS_GRAPH_BASE_H


struct Edge
{
    // Struct to save weighted directed edges in an adjacency
    // list. We only store toNode because the in the adjacency list
    // we already know fromNode
    int toNode;
    int weight;

    Edge(int toNode_, int weight_)
            : toNode {toNode_}, weight {weight_}
    {

    }

    friend bool operator==(const Edge& edge_1, const Edge& edge_2);
};


class WeightedGraphBase
{
    // Base class for weighted graphs.
protected:
    std::vector<std::list<Edge>> m_adjacencyList;
    int m_numEdges{0};

public:

    WeightedGraphBase() = default;

    explicit WeightedGraphBase(int numNodes)
        : m_adjacencyList(numNodes)
    {

    }

    int numNodes() const {return static_cast<int>(m_adjacencyList.size());}
    int numEdges() const {return m_numEdges;}

    int getWeight(int fromNode, int toNode) const;
    bool isEdge(int fromNode, int toNode) const;

    void addNode();
};