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
        // Traverse the tree until we find a character that doesn't match
        // or, we get to a leave node
        std::queue<int> queue;
        queue.push(0);
        std::size_t currentChar {0};
        int currentNode {0};

        while (!queue.empty())
        {
            int root {queue.front()};
            queue.pop();
            for (auto children : m_adjacencyList[root])
            {
                if (m_keys[children] == pattern[currentChar])
                {
                    currentChar++;
                    currentNode = children;
                    queue.push(children);
                    break;
                }
            }

        }
        // Now create a node for each of the remaining characters of the
        // pattern
        for (; currentChar < pattern.size(); ++currentChar)
        {
            addChild(currentNode, pattern[currentChar]);
            currentNode = m_numNodes - 1;
        }
    }
}