//
// Created by daniel on 14/06/22.
//

#ifndef ALGORITHMS_WEIGHTED_GRAPH_H
#define ALGORITHMS_WEIGHTED_GRAPH_H

#include <array>
#include <queue>
#include "DisjointSets/disjoint_sets.h"
#include "graph_base.h"

class WeightedGraph : public WeightedGraphBase
{
public:

    WeightedGraph() = default;

    explicit WeightedGraph(int numNodes)
        : WeightedGraphBase {numNodes}
    {

    }



    void addEdge(int fromNode, int toNode, int weight);
    void addEdges(const std::vector<std::array<int, 3>>& edges);

    WeightedGraph kruskalMST() const;
    WeightedGraph primsMST() const;

};


#endif //ALGORITHMS_WEIGHTED_GRAPH_H
