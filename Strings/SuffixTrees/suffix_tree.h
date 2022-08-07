//
// Created by daniel on 6/08/22.
//

#ifndef ALGORITHMS_SUFFIX_TREE_H
#define ALGORITHMS_SUFFIX_TREE_H

#endif //ALGORITHMS_SUFFIX_TREE_H

#include <map>
#include "SuffixArray/suffix_array.h"

struct SuffixTreeNode
{
    // A struct to represent a suffix tree node with its incoming edge.
    SuffixTreeNode* parent;
    std::map<char, SuffixTreeNode*> children;
    int stringDepth;
    int edgeStart;
    int edgeEnd;

    SuffixTreeNode(SuffixTreeNode* parent_, int depth, int start, int end)
        : parent {parent_}, stringDepth {depth},
        edgeStart {start}, edgeEnd {end}
    {

    }
};


class SuffixTree
{
    // Suffix Tree data structure. This tree its constructed from a
    // suffix array in time O(|text|log(|text|))
private:

    SuffixTreeNode* m_root;
    int m_numEdges {0};
    const std::string& m_text;

    void build(const std::vector<int>& suffixArray,
               const std::vector<int>& lcpArray);

public:


    explicit SuffixTree(const std::string& text)
     : m_text {text}
    {
        // Create the root node
        m_root = new SuffixTreeNode(nullptr, 0, -1, -1);
        std::vector<int> order {suffixArray(text)};
        std::vector<int> lcp {lcpArray(text, order)};
        build(order, lcp);
    }

    int numNodes() const {return m_numEdges + 1;}
    int numEdges() const {return m_numEdges;}

    SuffixTreeNode* getRoot() {return m_root;}

    static SuffixTreeNode* createNewLeaf(const std::string& text,
                                         SuffixTreeNode* node, int suffix);

    static SuffixTreeNode* breakEdge(const std::string& text,
                                     SuffixTreeNode* node, int start, int offset);

};