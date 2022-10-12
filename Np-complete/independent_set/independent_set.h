//
// Created by daniel on 12/10/22.
//

#ifndef ALGORITHMS_INDEPENDENT_SET_H
#define ALGORITHMS_INDEPENDENT_SET_H

#include <vector>
#include <utility>  // std::pair


class TreeNode
{
private:
    int m_weight;
    std::vector<int> m_children;  // Indices of its children

public:

    TreeNode() : m_weight {0}
    {

    }

    explicit TreeNode(int weight) : m_weight {weight}
    {

    }

    int getWeight() const { return m_weight; }
    void setWeight(int weight) { m_weight = weight; }

    bool hasChildren() const { return m_children.empty(); }
    void addChild(int child) { m_children.push_back(child); }
    std::vector<int>& getChildren() { return m_children; }
};


class WeightedTree
{
    // Class to store a tree with weights
private:
    std::vector<TreeNode> m_nodes;

    void build(const std::vector<std::pair<int, int>>& nodes,
               const std::vector<int>& weights);

public:

    WeightedTree(int numNodes, const std::vector<std::pair<int, int>>& nodes,
                 const std::vector<int>& weights)
                 : m_nodes(numNodes)
    {
        build(nodes, weights);
    }

    std::size_t size() const { return m_nodes.size(); }

    std::vector<TreeNode>& getNodes() { return m_nodes; }

    int maxISWeight();
};

#endif //ALGORITHMS_INDEPENDENT_SET_H
