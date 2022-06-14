//
// Created by daniel on 2/06/22.
//

#ifndef ALGORITHMS_DIGRAPH_H
#define ALGORITHMS_DIGRAPH_H

#endif //ALGORITHMS_DIGRAPH_H

#include <algorithm>
#include <cassert>
#include <list>
#include <stack>
#include <vector>
#include "graph_base.h"
#include "validate_node.h"


enum Color
{
    // Colors for labeling the nodes in the isCyclic functions
    white, // Node not processed
    gray, // Node being processed
    black, // Node completely processed
};

class Digraph : public GraphBase
{
private:


    bool isCyclicUtil(int currentNode, std::vector<int>& colors) const;

    void explore(int currentNode,
                          std::vector<bool>& visited) const;
    void exploreAndStack(int currentNode,
                              std::vector<bool>& visited,
                              std::stack<int>& stack
                              ) const;

public:

    Digraph() = default;;

    explicit Digraph(int numNodes)
        : GraphBase {numNodes}
    {

    }

    void addEdge(int outNode, int inNode);
    int numOutEdges(int node) const;
    std::list<int> getOutNeighbors(int node) const;

    bool isCyclic() const;
    std::vector<int> topologicalOrder() const;
    int numStronglyConnectedComponents() const;

    Digraph reverseGraph() const;
};