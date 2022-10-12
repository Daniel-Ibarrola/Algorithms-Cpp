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
                                        std::vector<int> &stack)
{
    // Traverse the graph by depth first search, and push the nodes into a
    // stack.
    visited[getIndex(currentNode)] = true;
    for (auto node : m_adjList[currentNode])
    {
        if(!visited[getIndex(node)])
            depthFirstSearch(node, visited, stack);
    }

    stack.push_back(currentNode);
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
    m_stack.clear();

    for (const auto& neighbors : m_adjList)
    {
        if (!visited[getIndex(neighbors.first)])
            depthFirstSearch(neighbors.first, visited, m_stack);
    }

    std::fill(visited.begin(), visited.end(), false);

    m_reverse = new ImplicationGraph(reverse());
    int sccNum {1};
    for (int ii {static_cast<int>(m_stack.size() - 1)}; ii >= 0; --ii)
    {
        int node {m_stack[ii]};
        int index {getIndex(node)};
        if (!visited[index])
        {
            m_reverse->markSCC(node, sccNum, visited, scc);
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


void ImplicationGraph::findOrdering(int currentNode, std::vector<bool> &visited)
{
    // Traverse the graph by dfs to find a topological ordering of the SCC
    visited[getIndex(currentNode)] = true;
    for (auto node : m_adjList[currentNode])
    {
        if (!visited[getIndex(node)])
            findOrdering(node, visited);
    }
}


std::vector<std::pair<int, int>> ImplicationGraph::sccOrdering()
{
    // Returns the topological ordering of the scc. It consists of a vector of
    // pairs where the first element is the scc and the second the root node of
    // that scc.
    // Should be called after finding SCC.
    std::vector<std::pair<int, int>> ordering;
    if (m_reverse == nullptr)
        return {};

    std::vector<bool> visited(numNodes(), false);
    int sccNum {1};
    for (int ii {static_cast<int>(m_stack.size() - 1)}; ii >= 0; --ii)
    {
        int root {m_stack[ii]};
        int index {getIndex(root)};
        if (!visited[index])
        {
            m_reverse->findOrdering(root, visited);
            ordering.emplace_back(sccNum, root);
            sccNum++;
        }
    }
    return ordering;
}


void ImplicationGraph::setLiterals(int currentNode, std::vector<bool> &visited, std::vector<int> &assignments)
{
    // Assign the literals of the CNF expression
    visited[getIndex(currentNode)] = true;

    int assignIndex {abs(currentNode) - 1};
    if (assignments[assignIndex] == std::numeric_limits<int>::max())
        assignments[assignIndex] = currentNode;

    for (auto node : m_adjList[currentNode])
    {
        if (!visited[getIndex(node)])
            setLiterals(node, visited, assignments);
    }
}


std::vector<int> twoSAT(const std::vector<std::vector<int>>& cnfFormula,
                        int numLiterals)
{
    // Given a 2-CNF expression returns a vector with the assignments of each
    // literal if the expression is satisfiable. If it's not satisfiable, it
    // returns an empty vector
    ImplicationGraph graph(cnfFormula, numLiterals);
    std::vector<int> scc {graph.SCC()};

    // If literal x and its negation lie in the same scc, the formula is unsatisfiable
    std::size_t negationStart {scc.size() / 2};
    for (auto ii {0}; ii < scc.size() / 2; ++ii)
    {
        if (scc[ii] == scc[negationStart + ii])
            return {};
    }
    // If we get to this point the formula is satisfiable, so we find an
    // assignment of the literals
    std::vector<int> assignments(numLiterals, std::numeric_limits<int>::max());
    std::vector<std::pair<int, int>> ordering {graph.sccOrdering()};
    std::vector<bool> visited(graph.numNodes(), false);

    for (int ii {static_cast<int>(ordering.size()) - 1}; ii >= 0; --ii)
    {
        graph.setLiterals(ordering[ii].second, visited, assignments);
    }

    return assignments;
}
