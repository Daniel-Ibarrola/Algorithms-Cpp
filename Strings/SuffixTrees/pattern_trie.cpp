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



std::vector<int> PatternTrie::matchText(const std::string &text) const
{
    // Returns the starting positions of the patterns in the text.

    if (numNodes() == 1)
        return {};

    std::vector<int> positions;
    for (auto ii {0}; ii < text.size(); ++ii)
    {
        int currentNode {0};
        int currentPosition {ii};
        while (true)
        {
            bool symbolMatch {false};
            // If we find a leave node we have found a match
            if (m_adjacencyList[currentNode].empty())
            {
                positions.push_back(ii);
                break;
            }
            // Iterate the adjacency list of the node to find a node with the
            // text current char.
            for (auto children : m_adjacencyList[currentNode])
            {
                if (m_keys[children] == text[currentPosition])
                {
                    currentPosition++;
                    currentNode = children;
                    symbolMatch = true;
                    break;
                }
            }

            if (!symbolMatch)
                break;
        }
    }

    return positions;
}