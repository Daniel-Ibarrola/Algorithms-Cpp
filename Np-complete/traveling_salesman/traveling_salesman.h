//
// Created by daniel on 17/10/22.
//

#ifndef ALGORITHMS_TRAVELING_SALESMAN_H
#define ALGORITHMS_TRAVELING_SALESMAN_H


#include <algorithm>
#include <array>
#include <list>
#include <vector>


struct Edge
{
    int end;
    int weight;

    Edge(int end_, int weight_) : end {end_}, weight {weight_}
    {

    }
};


class TSGraph
{
    // Graph with weighted edges
private:
    std::vector<std::list<Edge>> m_adjacencyList;
    std::size_t m_numEdges {0};

public:

    TSGraph(int numNodes, const std::vector<std::array<int, 3>>& edgeList)
        : m_adjacencyList(numNodes)
    {
        for (const auto& edge : edgeList)
        {
            m_adjacencyList[edge[0] - 1].push_back({edge[1] - 1, edge[2]});
            m_adjacencyList[edge[1] - 1].push_back({edge[0] - 1, edge[2]});
            m_numEdges++;
        }
    }

    std::size_t numNodes() const { return m_adjacencyList.size(); }
    std::size_t numEdges() const { return m_numEdges; }

    int getWeight(int start, int end) const;

    std::vector<int> travelingSalesmanPath() const;
    int travelingSalesmanWeight() const;
};

#endif //ALGORITHMS_TRAVELING_SALESMAN_H
