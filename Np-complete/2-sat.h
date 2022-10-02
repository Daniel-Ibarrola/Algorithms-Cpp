//
// Created by daniel on 1/10/22.
//

#ifndef ALGORITHMS_2_SAT_H
#define ALGORITHMS_2_SAT_H

#include <algorithm>  // std::find
#include <list>
#include <unordered_map>
#include <vector>


class ImplicationGraph
{
    // Directed graph that represents a 2-CNF expression.
private:
    std::unordered_map<int, std::list<int>> m_adjList;
    std::size_t m_numEdges {0};

    void createGraph(const std::vector<std::vector<int>>& cnfFormula, int numLiterals);

public:

    explicit ImplicationGraph(const std::vector<std::vector<int>>& cnfFormula, int numLiterals)
    {
        createGraph(cnfFormula, numLiterals);
    }

    std::size_t numNodes() const {return m_adjList.size();}
    std::size_t numEdges() const {return m_numEdges;}

    bool isEdge(int node_1, int node_2);

};

std::vector<int> twoSAT(const std::vector<std::vector<int>>& cnfFormula, int numLiterals);

#endif //ALGORITHMS_2_SAT_H
