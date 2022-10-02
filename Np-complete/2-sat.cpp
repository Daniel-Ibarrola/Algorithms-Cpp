//
// Created by daniel on 1/10/22.
//

#include "2-sat.h"


void ImplicationGraph::createGraph(const std::vector<std::vector<int>> &cnfFormula, int numLiterals)
{
    // Construct the implication graph

    // Create a node for each literal and it's negation
    for (int ii {1}; ii < numLiterals + 1; ++ii)
    {
        m_adjList[ii] = std::list<int> {};
        m_adjList[-ii] = std::list<int> {};
    }
    // Add edges
    for (const auto& clause : cnfFormula)
    {
        if (clause.size() == 1)
        {
            m_adjList[-clause[0]].push_back(clause[0]);
            m_numEdges++;
        }
        else
        {
            m_adjList[-clause[0]].push_back(clause[1]);
            m_adjList[-clause[1]].push_back(clause[0]);
            m_numEdges += 2;
        }
    }
}


bool ImplicationGraph::isEdge(int node_1, int node_2)
{
    // Find if there is an outgoing edge from node 1 to node 2
    const std::list<int>& neighbors {m_adjList[node_1]};
    if (std::find(neighbors.begin(), neighbors.end(), node_2) != std::end(neighbors))
        return true;
    return false;
}


std::vector<int> twoSAT(const std::vector<std::vector<int>>& cnfFormula,
                        int numLiterals)
{
    // Given a 2-CNF expression returns a vector with the assignments of each
    // literal if the expression is satisfiable. If it's not satisfiable, it
    // returns an empty vector
    return {-1};
}
