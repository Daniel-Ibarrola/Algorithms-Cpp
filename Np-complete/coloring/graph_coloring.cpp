#include "graph_coloring.h"


std::vector<int> Graph3C::edgeToLit(int numLiterals)
{
    // Returns a vector whose elements range from 1 to numLiterals
    // with a step of three
    std::vector<int> edgeToLiteral((numLiterals) / 3);
    int lit {1};
    for (auto ii {0}; ii < edgeToLiteral.size(); ++ii)
    {
        edgeToLiteral[ii] = lit;
        lit += 3;
    }
    return edgeToLiteral;
}

std::vector<std::vector<int>> Graph3C::threeColorCNF() const
{
    // Returns an expression in CNF that must be satisfied if
    // the graph can be colored with three colors.

    int numLiterals {3 * numNodes()};
    int numClauses {4 * numNodes() + 3 * numEdges()};
    std::vector<std::vector<int>> clauses(numClauses);
    // Clause type 1. At least one color. We have one of these clauses
    // for each node
    int literal {1};
    for (auto ii {0}; ii < numNodes(); ++ii)
    {
        clauses[ii] = {literal, literal + 1, literal + 2, 0};
        literal += 3;
    }
    // Clause type 2. At most one color. We have 3 * numNodes clauses
    // We start were the previous loop ended
    literal = 1;
    while (literal + numNodes() - 1 <= numNodes() * 3)
    {
        clauses[literal + numNodes() - 1] = {-literal, -(literal + 1), 0};
        clauses[literal + numNodes()] = {-literal, -(literal + 2), 0};
        clauses[literal + numNodes() + 1] = {-(literal + 1), -(literal + 2), 0};
        literal += 3;
    }
    // Clause type 3. Two nodes connected by an edge have different colors
    std::vector<int> edgeToLiteral {edgeToLit(numLiterals)};
    int ii {4 * numNodes()};
    for (const auto& edge : m_edgeList)
    {
        int lit_1 {edgeToLiteral[edge.first - 1]};
        int lit_2 {edgeToLiteral[edge.second - 1]};
        clauses[ii] = {-lit_1, -lit_2, 0};
        clauses[ii + 1] = {-(lit_1 + 1), -(lit_2 + 1), 0};
        clauses[ii + 2] = {-(lit_1 + 2), -(lit_2 + 2), 0};
        ii += 3;
    }

    return clauses;
}


