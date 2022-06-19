//
// Created by daniel on 19/06/22.
//

#include "pattern_trie.h"

void PatternTrie::addChild(int node, char key)
{
    // Add a child to the given node

    // First add an edge from the given node to its new child
    m_adjacencyList[node].push_back(
            m_numNodes);
    // Store the key of the new child and grow the tree adjacency list
    m_keys.push_back(key);
    m_adjacencyList.emplace_back(std::vector<int>());
    m_numNodes++;
}

void PatternTrie::constructTrie(const std::vector<std::string>& patterns)
{
    // Construct the tree from a set of patterns

    for (const auto& pattern : patterns)
    {
        int currentNode {0};
        for (auto currentChar : pattern)
        {
            // Flag to know if there is an outgoing edge with the current character as label
            bool hasEdge {false};
            for (auto children : m_adjacencyList[currentNode])
            {
                if (m_keys[children] == currentChar)
                {
                    hasEdge = true;
                    currentNode = children;
                    break;
                }
            }
            if (!hasEdge)
            {
                addChild(currentNode, currentChar);
                currentNode = m_numNodes - 1;
            }
        }
    }
}