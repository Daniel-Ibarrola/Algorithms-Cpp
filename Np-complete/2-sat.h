//
// Created by daniel on 1/10/22.
//

#ifndef ALGORITHMS_2_SAT_H
#define ALGORITHMS_2_SAT_H

#include <algorithm>  // std::find, std::fill
#include <list>
#include <stack>
#include <unordered_map>
#include <vector>


class ImplicationGraph
{
    // Directed graph that represents a 2-CNF expression.
private:
    std::unordered_map<int, std::list<int>> m_adjList;
    std::size_t m_numEdges {0};

    void fromCNF(const std::vector<std::vector<int>>& cnfFormula, int numLiterals);
    void fromEdgeList(const std::vector<std::pair<int, int>>& edgeList, int numLiterals);
    void depthFirstSearch(int currentNode, std::vector<bool>& visited,
                          std::stack<int> &stack);
    void markSCC(int currentNode, int sccNum,
                 std::vector<bool>& visited, std::vector<int>& scc);
    int getIndex(int node) const;

public:

    explicit ImplicationGraph(int numLiterals)
    {
        // Create a graph with no edges

        // Create a node for each literal and it's negation
        for (int ii {1}; ii < numLiterals + 1; ++ii)
        {
            m_adjList[ii] = std::list<int> {};
            m_adjList[-ii] = std::list<int> {};
        }
    }

    ImplicationGraph(const std::vector<std::vector<int>>& cnfFormula, int numLiterals)
    {
        fromCNF(cnfFormula, numLiterals);
    }

    ImplicationGraph(const std::vector<std::pair<int, int>>& edgeList, int numLiterals)
    {
        fromEdgeList(edgeList, numLiterals);
    }

    std::size_t numNodes() const {return m_adjList.size();}
    std::size_t numEdges() const {return m_numEdges;}

    bool isEdge(int node_1, int node_2);

    ImplicationGraph reverse() const;

    std::vector<int> SCC();
    int numSCC();
    int getNodeSCC(int node, const std::vector<int>& scc);
};

std::vector<int> twoSAT(const std::vector<std::vector<int>>& cnfFormula, int numLiterals);

#endif //ALGORITHMS_2_SAT_H
