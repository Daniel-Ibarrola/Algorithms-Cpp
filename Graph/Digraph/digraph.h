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
#include "validate_node.h"

//void validateNode(int node, int numberOfNodes);
//
//class invalid_node_error : public std::exception
//{
//    const char* what() const noexcept override
//    {
//        return "Invalid node";
//    }
//};

enum Color
{
    // Colors for labeling the nodes in the isCyclic functions
    white, // Node not processed
    gray, // Node being processed
    black, // Node completely processed
};

class Digraph
{
private:
    std::vector<std::list<int>> m_adjacencyList;
    int m_numEdges {0};

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
        : m_adjacencyList(numNodes, std::list<int>())
    {

    }

    int numNodes() const {return static_cast<int>(m_adjacencyList.size());}
    int numEdges() const {return m_numEdges;}

    void addEdge(int outNode, int inNode);
    void addNode();
    bool isEdge(int outNode, int inNode) const;

    int numOutEdges(int node) const;
    std::list<int> getOutNeighbors(int node) const;

    bool isCyclic() const;
    std::vector<int> topologicalOrder() const;
    int numStronglyConnectedComponents() const;

    Digraph reverseGraph() const;
};