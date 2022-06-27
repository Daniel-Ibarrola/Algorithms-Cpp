//
// Created by daniel on 20/06/22.
//

#ifndef ALGORITHMS_SUFFIX_TREE_H
#define ALGORITHMS_SUFFIX_TREE_H

#include <string>
#include <vector>
#include "SuffixTrees/suffix_trie.h"

class TreeNode
{
// A node of the suffix tree;
private:
    int m_start;
    int m_end;
    std::vector<int> m_children;

public:

    explicit TreeNode(int start, int end)
        : m_start {start}, m_end {end}
    {

    }

    int start() const { return m_start; }
    int end() const { return m_end; }
    bool hasChildren() const { return !m_children.empty(); }
    void addChild(int child) { m_children.push_back(child); }
    const std::vector<int>& getChildren() const { return m_children; }

    friend class SuffixTree;
};


class invalid_suffix_tree_node_error : public std::exception
{
    const char* what() const noexcept override
    {
        return "Invalid node";
    }
};


class SuffixTree
{
    // Suffix tree data structure
private:
    int m_numNodes {1};
    int m_numEdges {0};
    int end {-1};  // The end of the text
    std::vector<TreeNode> m_adjacencyList {TreeNode(-1, -1)};

    void validateNode(int nodeIndex) const;

    void addNode(int textStart, int textEnd);

    void addChild(int node, int child);

    void build(const std::string& text);

    void buildUtil(int currentNode,
                          int currentStart,
                          int currentRoot,
                          const SuffixTrie& trie,
                          std::vector<bool>& visited);

    void getSuffixesUtil(int currentNode,
                         std::vector<bool>& visited,
                         const std::string& text,
                         std::vector<std::string>& suffixes) const;

public:

    SuffixTree() = default;

    explicit SuffixTree(const std::string& text)
        : end {static_cast<int>(text.size() - 1)}
    {
        build(text);
    }

    std::vector<std::string> getAllSuffixes(const std::string& text) const;

    int numNodes() const {return m_numNodes;}
    int numEdges() const {return m_numEdges;}

    const TreeNode& getNode(int nodeIndex) const;

};

#endif //ALGORITHMS_SUFFIX_TREE_H
