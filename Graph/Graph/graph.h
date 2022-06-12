//
// Created by daniel on 29/05/22.
//

#ifndef ALGORITHMS_ADJACENCY_LIST_H
#define ALGORITHMS_ADJACENCY_LIST_H

#endif //ALGORITHMS_ADJACENCY_LIST_H

#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <tuple>
#include <stack>
#include <vector>

class invalid_node_error : public std::exception
{
    const char* what() const noexcept override
    {
        return "Invalid node";
    }
};

class Graph
{
    // ListGraph class that uses an adjacency list. Nodes are integers starting from 0
private:
    std::vector<std::list<int>> m_adjacencyList;
    int m_numEdges {0};

    void validateNode(int node) const;

    bool pathBetweenUtil(int currentNode, int endNode,
                         std::vector<bool>& visited) const;

    void explore(int currentNode, std::vector<bool>& visited) const;

    bool isBipartiteUtil(int node, std::vector<int>& colors) const;

public:

    Graph() = default;;

    explicit Graph(int numNodes)
        : m_adjacencyList(numNodes, std::list<int>())
    {

    }

    int numNodes() const {return static_cast<int>(m_adjacencyList.size());}
    int numEdges() const {return m_numEdges;}

    void addNode();
    void addEdge(int node_1, int node_2);
    void addEdges(const std::vector<std::tuple<int, int>>& edges);
    void addEdgesToNode(int node, const std::vector<int>& toNodes);

    bool isEdge(int node_1, int node_2) const;
    int numNeighbors(int node) const;
    std::vector<int> getNeighbors(int node) const;

    bool pathBetween(int startNode, int endNode) const;
    int numConnectedComponents() const;

    std::vector<int> distancesFromNode(int node) const;
    int shortestPath(int startNode, int endNode) const;

    bool isBipartite() const;
};