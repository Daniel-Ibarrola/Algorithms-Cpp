//
// Created by daniel on 25/06/22.
//

#include "suffix_trie.h"


void SuffixTrie::validateNode(int node) const
{
    // Check if the given node is part of the trie
    if (node >= numNodes())
        throw invalid_trie_node_error();
}


char SuffixTrie::getKey(int node) const
{
    // Returns the key of the given node
    validateNode(node);
    return m_adjacencyList[node].getKey();
}


const std::vector<int>& SuffixTrie::getChildren(int node) const
{
    // Returns a vector with the children of the given node
    validateNode(node);
    return m_adjacencyList[node].getChildren();
}


bool SuffixTrie::hasChildren(int node) const
{
    // Returns true if the given node has any children
    validateNode(node);
    return m_adjacencyList[node].hasChildren();
}

void SuffixTrie::addChild(int node, int child)
{
    // Add a child to the given node
    validateNode(node);
    m_adjacencyList[node].addChild(child);
    m_numEdges++;
}


void SuffixTrie::createNode(char key)
{
    // Creates a new node
    m_adjacencyList.emplace_back(Node {key});
    m_numNodes++;
}


void SuffixTrie::build(const std::string &text)
{
    // Builds the suffix trie of the text

    int textEnd {static_cast<int>(text.size()) - 1};
    bool hasEdge;

    // We construct the trie by traversing the text string in reverse order
    for (auto ii {textEnd}; ii >= 0; --ii)
    {
        int currentNode {0};
        // Iterate from the ii-th character to the end of the string
        for (auto jj {ii}; jj <= textEnd; ++jj)
        {
            hasEdge = false;
            char currentChar {text[jj]};
            for (const auto& child : m_adjacencyList[currentNode].getChildren())
            {
                // Check if there is an edge that starts with the current character
                if (getKey(child) == currentChar)
                {
                    hasEdge = true;
                    currentNode = child;
                    break;
                }
            }
            if (!hasEdge)
            {
                // We create a new node that is the numNodes - 1 node and create
                // an edge between it and the current node.
                createNode(currentChar);
                addChild(currentNode, numNodes() - 1);
                currentNode = numNodes() - 1;
            }

        }
    }

}
