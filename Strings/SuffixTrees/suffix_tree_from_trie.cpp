//
// Created by daniel on 20/06/22.
//

#include "suffix_tree_from_trie.h"


void SuffixTreeFromTrie::validateNode(int nodeIndex) const
{
    if (nodeIndex >= numNodes())
        throw invalid_suffix_tree_node_error();
}

const TreeNode& SuffixTreeFromTrie::getNode(int nodeIndex) const
{
    // Returns a const reference to the node with given index
    return m_adjacencyList[nodeIndex];
}


void SuffixTreeFromTrie::addNode(int textStart, int textEnd)
{
    // Add a new node to the tree
    m_adjacencyList.emplace_back(TreeNode {textStart, textEnd});
    m_numNodes++;
}


void SuffixTreeFromTrie::addChild(int node, int child)
{
    // Add a child to the given node
    validateNode(node);
    m_adjacencyList[node].addChild(child);
    m_numEdges++;
}


void SuffixTreeFromTrie::buildUtil(int currentNode,
                                   int currentStart,
                                   int currentRoot,
                                   const SuffixTrie &trie,
                                   std::vector<bool> &visited)
{
    // Do a depth first search traversal of the trie, while at the same time
    // building the suffix tree
    visited[currentNode] = true;

    // Case: The currentNode has two or more children, and it's not the root node,
    // so we need to create a branch in the tree.
    if (trie.numChildren(currentNode) > 1 && trie.getKey(currentNode) != -1)
    {
        addNode(currentStart, trie.getKey(currentNode));
        addChild(currentRoot, m_numNodes -1);
        currentRoot = m_numNodes - 1;
    }
    // Case: The currentNode is a leave node (has no children). We create a new node
    // The end of these nodes will always be the text end.
    if (!trie.hasChildren(currentNode))
    {
        addNode(currentStart, end);
        addChild(currentRoot, m_numNodes - 1);
    }

    // If a node only has one child, we do nothing and just keep exploring the tree.
    for (auto child : trie.getChildren(currentNode))
    {
        // When node has more than one child we update current start, this applies also for
        // the root node
        if (trie.numChildren(currentNode) > 1)
            currentStart = trie.getKey(child);

        if (!visited[child])
            buildUtil(child, currentStart, currentRoot, trie, visited);
    }

}


void SuffixTreeFromTrie::build(const std::string &text)
{
    // Builds the suffix tree. Non-linear time algorithm

    // First we construct the suffix trie, and then we compress it
    SuffixTrie trie(text);
    // Depth first search traversal of the trie
    std::vector<bool> visited(trie.m_adjacencyList.size(), false);
    buildUtil(0, end, 0, trie, visited);
}


void SuffixTreeFromTrie::getSuffixesUtil(int currentNode,
                                         std::vector<bool>& visited,
                                         const std::string& text,
                                         std::vector<std::string>& suffixes) const
{
    // Do a depth first search traversal while recovering all the suffixes
    // present in the nodes of the tree
    visited[currentNode] = true;

    if (currentNode != 0)
    {
        int textStart {m_adjacencyList[currentNode].start()};
        int textEnd {m_adjacencyList[currentNode].end() - textStart + 1};
        suffixes.emplace_back(text.substr(textStart, textEnd));
    }

    for (auto child : m_adjacencyList[currentNode].getChildren())
    {
        if (!visited[child])
            getSuffixesUtil(child, visited, text, suffixes);
    }
}


std::vector<std::string> SuffixTreeFromTrie::getAllSuffixes(const std::string& text) const
{
    // Returns a vector with all the suffixes present int the tree.
    std::vector<std::string> suffixes {};
    std::vector<bool> visited(m_adjacencyList.size(), false);
    getSuffixesUtil(0, visited, text, suffixes);
    return suffixes;
}
