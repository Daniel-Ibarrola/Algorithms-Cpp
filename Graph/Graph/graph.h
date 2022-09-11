//
// Created by daniel on 29/05/22.
//

#ifndef ALGORITHMS_ADJACENCY_LIST_H
#define ALGORITHMS_ADJACENCY_LIST_H

#endif //ALGORITHMS_ADJACENCY_LIST_H

#include <algorithm>
#include <iostream>
#include <list>
#include <limits>
#include <queue>
#include <tuple>
#include <stack>
#include <vector>
#include "graph_base.h"
#include "validate_node.h"


class Graph : public GraphBase
{
    // Graph class that uses an adjacency list. Nodes are integers starting from 0
private:

    bool pathBetweenUtil(int currentNode, int endNode,
                         std::vector<bool>& visited) const;

    void explore(int currentNode, std::vector<bool>& visited) const;

    bool isBipartiteUtil(int node, std::vector<int>& colors) const;

public:

    Graph() = default;

    explicit Graph(int numNodes)
        : GraphBase {numNodes}
    {

    }

    void addEdge(int node_1, int node_2);
    void addEdges(const std::vector<std::tuple<int, int>>& edges);
    void addEdgesToNode(int node, const std::vector<int>& toNodes);

    int numNeighbors(int node) const;
    std::vector<int> getNeighbors(int node) const;

    bool pathBetween(int startNode, int endNode) const;
    int numConnectedComponents() const;

    std::vector<int> distancesFromNode(int node) const;
    int shortestPath(int startNode, int endNode) const;

    bool isBipartite() const;
};