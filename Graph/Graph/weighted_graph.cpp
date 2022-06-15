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


WeightedGraph WeightedGraph::kruskalMST() const
{
    // Returns the minimum spanning tree of the graph.
    // Uses kruskal algorithm
    DisjointSets sets(numNodes(), true);
    for (int ii {0}; ii < numNodes(); ++ii)
        sets.makeSet(ii);

    struct WeightedEdge
    {
        int fromNode;
        int toNode;
        int weight;
    };
    // We store all the edges in a vector and
    // sort them by their weight in non-decreasing order
    std::vector<WeightedEdge> edges;
    for (int node {0}; node < numNodes(); ++node)
    {
        for (auto edge: m_adjacencyList[node])
            edges.push_back({node, edge.toNode, edge.weight});
    }
    auto compare = [](WeightedEdge edge_1, WeightedEdge edge_2)
        { return edge_1.weight < edge_2.weight; };
    std::sort(edges.begin(), edges.end(), compare);

    // Now we can construct the minimum spanning tree
    WeightedGraph minimumSpanningTree(numNodes());
    for (const auto& edge : edges)
    {
        if (sets.find(edge.fromNode) != sets.find(edge.toNode))
        {
            minimumSpanningTree.addEdge(edge.fromNode,
                                        edge.toNode,
                                        edge.weight);
            sets.setUnion(edge.fromNode, edge.toNode);
        }
    }

    return minimumSpanningTree;
}

WeightedGraph WeightedGraph::primsMST() const
{
    // Returns the minimum spanning tree of the graph.
    // Uses Prim's algorithm
    WeightedGraph minimumSpanningTree(numNodes());
    if (numNodes() <= 1)
        return minimumSpanningTree;

    std::vector<int> parent(m_adjacencyList.size(), -1);
    std::vector<bool> inMST(m_adjacencyList.size(), false);
    std::vector<int> cost(m_adjacencyList.size(), std::numeric_limits<int>::max());
    cost[0] = 0;
    struct Node
    {
        int nodeIndex;
        int cost;
    };
    // We create a min-heap that stores nodes by their cost
    auto compare = [](Node node_1, Node node_2)
            { return node_1.cost > node_2.cost; };
    std::priority_queue<Node, std::vector<Node>, decltype(compare)> queue(compare);
    queue.push({0, cost[0]});

    while(!queue.empty())
    {
        int node {queue.top().nodeIndex};
        queue.pop();

        if (inMST[node])
            continue;

        inMST[node] = true;
        for (const auto& neighbor : m_adjacencyList[node])
        {
            if (!inMST[neighbor.toNode] && cost[neighbor.toNode] > neighbor.weight)
            {
                cost[neighbor.toNode] = neighbor.weight;
                parent[neighbor.toNode] = node;
                queue.push(Node {neighbor.toNode, cost[neighbor.toNode]});
            }
        }
    }

    // Now we construct the graph from the parent array
    for (int node{1}; node < numNodes(); ++node)
        minimumSpanningTree.addEdge(node, parent[node], cost[node]);

    return minimumSpanningTree;
}