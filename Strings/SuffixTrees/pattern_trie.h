//
// Created by daniel on 19/06/22.
//

#ifndef ALGORITHMS_PATTERN_TRIE_H
#define ALGORITHMS_PATTERN_TRIE_H

#include <queue>
#include <string>
#include <vector>


class PatternTrie
{
    // Class to store a pattern trie of a collections of patterns in a tree
    // Each node stores a character
private:

    int m_numNodes{1};
    int m_numPatterns{};
    // We start with just the root node
    std::vector<std::vector<int>> m_adjacencyList {1, std::vector<int>()};
    std::vector<char> m_keys {char(0)};

    void constructTrie(const std::vector<std::string>& patterns);
    void addChild(int node, char key);

public:

    explicit PatternTrie(const std::string& pattern)
        // We add 1 to consider the root node
        : m_numPatterns {1}
    {
        constructTrie(std::vector<std::string> {pattern});
    }

    explicit PatternTrie(const std::vector<std::string>& patterns)
        : m_numPatterns {static_cast<int>(patterns.size())}
    {
        constructTrie(patterns);
    }

    int numNodes() const { return m_numNodes; }
    int numPatterns() const { return m_numPatterns; }

    const std::vector<std::vector<int>>& getAdjacencyList() const { return m_adjacencyList; }
    const std::vector<char>& getKeys() const { return m_keys; }
};

#endif //ALGORITHMS_PATTERN_TRIE_H
