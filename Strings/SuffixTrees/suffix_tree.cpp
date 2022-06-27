//
// Created by daniel on 20/06/22.
//

#include "suffix_tree.h"


void SuffixTree::validateNode(int nodeIndex) const
{
    if (nodeIndex >= numNodes())
        throw invalid_suffix_tree_node_error();
}

const TreeNode& SuffixTree::getNode(int nodeIndex) const
{
    // Returns a const reference to the node with given index
    return m_adjacencyList[nodeIndex];
}


void SuffixTree::addNode(int textStart, int textEnd)
{
    // Add a new node to the tree
    m_adjacencyList.emplace_back(TreeNode {textStart, textEnd});
    m_numNodes++;
}


void SuffixTree::addChild(int node, int child)
{
    // Add a child to the given node
    validateNode(node);
    m_adjacencyList[node].addChild(child);
    m_numEdges++;
}


void SuffixTree::depthFirstSearch(int currentNode,
                                  int currentStart,
                                  int currentEnd,
                                  const SuffixTrie &trie,
                                  std::vector<bool> &visited)
{
    // Do a depth first search traversal of the trie, while at the same time
    // building the suffix tree
    visited[currentNode] = true;
    for (auto child : trie.getChildren(currentNode))
    {
        // If a node has more than one child we update the current end
        if (trie.getChildren(child).size() > 1)
            currentEnd = trie.getKey(child);

        if (trie.getKey(currentNode) == -1)
            currentStart = trie.getKey(child);

        if (!visited[child])
            depthFirstSearch(child, currentStart, currentEnd, trie, visited);
    }

    if (currentStart != -1)
    {
        // Here we have reached a leave node
        if (!trie.hasChildren(currentNode))
        {
            addNode(currentStart, end);
            addChild(0, m_numNodes - 1);
        }

    }
}


void SuffixTree::build(const std::string &text)
{
    // Builds the suffix tree. Non-linear time algorithm

    // First we construct the suffix trie, and then we compress it
    SuffixTrie trie(text);
    // Depth first search traversal of the trie
    std::vector<bool> visited(trie.m_adjacencyList.size(), false);
    depthFirstSearch(0, -1, end, trie, visited);
}

std::vector<std::string> SuffixTree::traversal() const
{
    // Returns a vector with the edge labels of the tree
    return {};
}