//
// Created by daniel on 17/10/22.
//

#ifndef ALGORITHMS_TRAVELING_SALESMAN_H
#define ALGORITHMS_TRAVELING_SALESMAN_H


#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <vector>


class TSGraph
{
    // Undirected graph with weighted edges represented by an adjacency
    // matrix
private:
    std::vector<std::vector<int>> m_adjMatrix;
    std::size_t m_numEdges {0};

    int travelingSalesmanRec(int mask, int index,
                             std::vector<std::vector<int>>& cost) const;

public:

    TSGraph(int numNodes, const std::vector<std::array<int, 3>>& edgeList)
        : m_adjMatrix(numNodes, std::vector<int>(numNodes, -1))
    {
        for (const auto& edge : edgeList)
        {
            m_adjMatrix[edge[0] - 1][edge[1] - 1] = edge[2];
            m_adjMatrix[edge[1] - 1][edge[0] - 1] = edge[2];
            m_numEdges++;
        }
    }

    std::size_t numNodes() const { return m_adjMatrix.size(); }
    std::size_t numEdges() const { return m_numEdges; }

    int getWeight(int start, int end) const { return m_adjMatrix[start][end]; }

    std::vector<int> travelingSalesmanPath() const;
    int travelingSalesmanWeight() const;
};

#endif //ALGORITHMS_TRAVELING_SALESMAN_H
