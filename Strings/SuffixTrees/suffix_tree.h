//
// Created by daniel on 20/06/22.
//

#ifndef ALGORITHMS_SUFFIX_TREE_H
#define ALGORITHMS_SUFFIX_TREE_H

#include <string>
#include <vector>

struct Node
{
    // A node of the suffix tree;
    int start;
    int end;
};

class SuffixTree
{
    // Suffix tree data structure
private:
    int m_numNodes {1};
    int m_numEdges {0};

    void build(const std::string& text);

public:

    explicit SuffixTree(const std::string& text)
    {
        build(text);
    }

    std::vector<std::string> traversal() const;

    int numNodes() const {return m_numNodes;}
    int numEdges() const {return m_numEdges;}

};

#endif //ALGORITHMS_SUFFIX_TREE_H
