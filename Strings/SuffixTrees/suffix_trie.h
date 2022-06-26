//
// Created by daniel on 25/06/22.
//

#ifndef ALGORITHMS_SUFFIX_TRIE_H
#define ALGORITHMS_SUFFIX_TRIE_H

#include <string>
#include <vector>


class TrieNode
{
private:
    std::vector<int> m_children;
    int m_key; // Holds the index of the character in text

public:

    explicit TrieNode(int key)
        : m_key {key}
    {

    }

    int getKey() const { return m_key; }
    const std::vector<int>& getChildren() const { return m_children; }

    bool hasChildren() const { return !m_children.empty(); }

    void addChild(int node) { m_children.push_back(node); }
};


class invalid_trie_node_error : public std::exception
{
    const char* what() const noexcept override
    {
        return "Invalid node";
    }
};


class SuffixTrie
{
private:
    int m_numNodes {1};
    int m_numEdges {0};
    std::vector<TrieNode> m_adjacencyList {TrieNode(-1)};

    void validateNode(int node) const;

    void build(const std::string& text);

    void addChild(int node, int child);

    void createNode(int key);

public:

    SuffixTrie() = default;

    explicit SuffixTrie(const std::string& text)
    {
        build(text);
    }

    int numNodes() const { return m_numNodes; }
    int numEdges() const { return m_numEdges; }

    int getKey(int node) const;
    const std::vector<int>& getChildren(int node) const;
    bool hasChildren(int node) const;
};

#endif //ALGORITHMS_SUFFIX_TRIE_H
