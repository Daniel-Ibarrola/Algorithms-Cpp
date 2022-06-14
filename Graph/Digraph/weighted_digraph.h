//
// Created by daniel on 12/06/22.
//

#ifndef ALGORITHMS_WEIGHTED_DIGRAPH_H
#define ALGORITHMS_WEIGHTED_DIGRAPH_H

#endif //ALGORITHMS_WEIGHTED_DIGRAPH_H

#include <array>
#include <queue> // std::priority_queue
#include <list>
#include <vector>
#include "Digraph/digraph.h" // for invalid_node_error, validate_node

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


class WeightedDigraph
{
    // A directed graph with weighted edges
private:
    std::vector<std::list<Edge>> m_adjacencyList;
    int m_numEdges{0};

public:

    WeightedDigraph() = default;

    explicit WeightedDigraph(int nodes)
     : m_adjacencyList(nodes)
    {

    }

    int numNodes() const {return static_cast<int>(m_adjacencyList.size());}
    int numEdges() const {return m_numEdges;}

    void addEdge(int fromNode, int toNode, int weight);
    void addEdges(const std::vector<std::array<int, 3>>& edges);
    int getWeight(int fromNode, int toNode) const;
    bool isEdge(int fromNode, int toNode) const;

    void addNode();

    int outDegree(int node) const;
    const std::list<Edge>& getOutNeighbors(int node) const;

    std::vector<int> getDistances(int startNode) const;
    int shortestPathLength(int startNode, int endNode) const;

    std::vector<int> shortestPathsBF(int startNode) const;
    bool hasNegativeCycle() const;

};