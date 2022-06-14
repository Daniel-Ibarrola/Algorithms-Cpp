//
// Created by daniel on 14/06/22.
//

#include "weighted_graph.h"

void WeightedGraph::addEdge(int fromNode, int toNode, int weight)
{
    // Adds a new edge to the graph
    if (!isEdge(fromNode, toNode))
    {
        m_adjacencyList[fromNode].push_back(Edge {toNode, weight});
        m_adjacencyList[toNode].push_back(Edge {fromNode, weight});
        ++m_numEdges;
    }
}

void WeightedGraph::addEdges(const std::vector<std::array<int, 3>>& edgeList)
{
    // Add multiple edges to the graph. A vector of arrays of size 3 is required, where
    // the first element of the array is the "from node", the second element is the
    // "to node" and the third elements is the weight of the edge.
    for (const auto& edge: edgeList)
        addEdge(edge[0], edge[1], edge[2]);
}
