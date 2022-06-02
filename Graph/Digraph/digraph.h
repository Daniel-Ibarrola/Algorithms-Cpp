//
// Created by daniel on 2/06/22.
//

#ifndef ALGORITHMS_DIGRAPH_H
#define ALGORITHMS_DIGRAPH_H

#endif //ALGORITHMS_DIGRAPH_H

#include <algorithm>
#include <list>
#include <vector>

class invalid_node_error : public std::exception
{
    const char* what() const noexcept override
    {
        return "Invalid node";
    }
};

enum Color
{
    // Colors for labeling the nodes in the hasCycle functions
    white, // Node not processed
    gray, // Node being processed
    black, // Node completely processed
};

class Digraph
{
private:
    std::vector<std::list<int>> m_adjacencyList;
    int m_numEdges {0};

    void validateNode(int node) const;

    bool isCyclicUtil(int currentNode, std::vector<int>& colors) const;

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
};