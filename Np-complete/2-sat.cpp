//
// Created by daniel on 1/10/22.
//

#include "2-sat.h"


void ImplicationGraph::fromCNF(const std::vector<std::vector<int>> &cnfFormula, int numLiterals)
{
    // Construct the implication graph starting from a 2-CNF expression

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


void ImplicationGraph::fromEdgeList(const std::vector<std::pair<int, int>> &edgeList, int numLiterals)
{
    // Create the graph from an edgeList

    // Create a node for each literal and it's negation
    for (int ii {1}; ii < numLiterals + 1; ++ii)
    {
        m_adjList[ii] = std::list<int> {};
        m_adjList[-ii] = std::list<int> {};
    }

    for (const auto& edge : edgeList)
    {
        m_adjList[edge.first].push_back(edge.second);
        m_numEdges++;
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


ImplicationGraph ImplicationGraph::reverse() const
{
    // Returns a graph with the reversed edges
    ImplicationGraph reverse (static_cast<int>(numNodes()) / 2);

    for (const auto& neighbors  : m_adjList)
    {
        for (auto nbr : neighbors.second)
        {
            reverse.m_adjList[nbr].push_back(neighbors.first);
            reverse.m_numEdges++;
        }
    }

    return reverse;
}


void ImplicationGraph::depthFirstSearch(int currentNode, std::vector<bool> &visited,
                                        std::stack<int> &stack)
{
    // Traverse the graph by depth first search, and push the nodes into a
    // stack.
    visited[getIndex(currentNode)] = true;
    for (auto node : m_adjList[currentNode])
    {
        if(!visited[getIndex(node)])
            depthFirstSearch(node, visited, stack);
    }

    stack.push(currentNode);
}


void ImplicationGraph::markSCC(int currentNode, int sccNum,
                               std::vector<bool> &visited, std::vector<int> &scc)
{
    // Traverse the graph by depth first search while marking the scc to which the
    // node belongs to
    int index {getIndex(currentNode)};
    visited[index] = true;
    scc[index] = sccNum;
    for (auto node : m_adjList[currentNode])
    {
        if(!visited[getIndex(node)])
            markSCC(node, sccNum, visited, scc);
    }
}


int ImplicationGraph::getIndex(int node) const
{
    // Returns the index of the node in the visited or scc array.
    if (node < 0)
    {
        return -1*node + static_cast<int>(numNodes()) / 2 - 1;
    }
    else
        return node -1;
}


std::vector<int> ImplicationGraph::SCC()
{
    // Returns a vector with the strongly connected component to which each
    // node belongs to

    // In the following arrays index 0 to |V|/2 - 1 represent the literals from 1,2,...,|V|/2
    // while the index |V|/2 to |V|-1 represent the negations of the literals 1,2,..,|V|/2
    std::vector<int> scc(numNodes(), 0);
    std::vector<bool> visited(numNodes(), false);
    std::stack<int> stack;

    for (const auto& neighbors : m_adjList)
    {
        if (!visited[getIndex(neighbors.first)])
            depthFirstSearch(neighbors.first, visited, stack);
    }

    ImplicationGraph reverseGraph {reverse()};
    std::fill(visited.begin(), visited.end(), false);
    std::stack<int> tempStack;
    int sccNum {1};
    while (!stack.empty())
    {
        int node {stack.top()};
        stack.pop();
        int index {getIndex(node)};
        if (!visited[index])
        {
            reverseGraph.markSCC(node, sccNum, visited, scc);
            sccNum++;
        }
    }
    return scc;
}


int ImplicationGraph::numSCC()
{
    // Returns the number of strongly connected components in the graph
    std::vector<int> scc {SCC()};
    return *std::max_element(scc.begin(), scc.end());
}


int ImplicationGraph::getNodeSCC(int node, const std::vector<int> &scc)
{
    // Get the SCC to which the given node belongs to
    return scc[getIndex(node)];
}


std::vector<int> twoSAT(const std::vector<std::vector<int>>& cnfFormula,
                        int numLiterals)
{
    // Given a 2-CNF expression returns a vector with the assignments of each
    // literal if the expression is satisfiable. If it's not satisfiable, it
    // returns an empty vector
    return {-1};
}
