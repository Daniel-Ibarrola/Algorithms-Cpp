//
// Created by daniel on 12/06/22.
//

#ifndef ALGORITHMS_WEIGHTED_DIGRAPH_H
#define ALGORITHMS_WEIGHTED_DIGRAPH_H

#endif //ALGORITHMS_WEIGHTED_DIGRAPH_H

#include <algorithm>
#include <array>
#include <queue> // std::priority_queue
#include <list>
#include <vector>
#include "graph_base.h"


class WeightedDigraph : public WeightedGraphBase
{
    // A directed graph with weighted edges

public:

    WeightedDigraph() = default;

    explicit WeightedDigraph(int numNodes)
     : WeightedGraphBase {numNodes}
    {

    }

    void addEdge(int fromNode, int toNode, int weight);
    void addEdges(const std::vector<std::array<int, 3>>& edges);

    int outDegree(int node) const;
    const std::list<Edge>& getOutNeighbors(int node) const;

    std::vector<int> getDistances(int startNode) const;
    int shortestPathLength(int startNode, int endNode) const;

    std::vector<int> shortestPathsBF(int startNode) const;
    bool hasNegativeCycle() const;

};