//
// Created by daniel on 24/08/22.
//

#ifndef ALGORITHMS_GRAPH_COLORING_H
#define ALGORITHMS_GRAPH_COLORING_H

#include <vector>


class Graph3C
{
private:

    std::vector<std::pair<int, int>> m_edgeList;
    int m_numNodes;

public:

    explicit Graph3C(int numNodes, std::vector<std::pair<int, int>> edgeList)
        : m_edgeList {std::move(edgeList)}, m_numNodes {numNodes}
    {

    }

    int numNodes() const { return m_numNodes; }
    int numEdges() const { return static_cast<int>(m_edgeList.size()); }

    std::vector<std::vector<int>> threeColorCNF() const;

    static std::vector<int> edgeToLit(int numLiterals);
};

#endif //ALGORITHMS_GRAPH_COLORING_H
