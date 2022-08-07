//
// Created by daniel on 6/08/22.
//

#include "suffix_tree.h"


SuffixTreeNode* SuffixTree::createNewLeaf(const std::string& text,
                                     SuffixTreeNode* node, int suffix)
{
    // Creates a new leaf node and adds it to the tree. Returns the newly created node

    int depth {static_cast<int>(text.size()) - suffix}; // depth is just the length of the suffix
    int end {static_cast<int>(text.size()) - 1}; // Each leaf always ends at the last character of the text
    auto* leaf {new SuffixTreeNode(node, depth,
                                   suffix + node->stringDepth, end)};

    node->children[text[leaf->edgeStart]] = leaf;

    return leaf;
}

SuffixTreeNode* SuffixTree::breakEdge(const std::string& text,
                                 SuffixTreeNode* node, int start, int offset)
{
    // Breaks a node edge and splits it in two. It creates and returns the new
    // middle node. The original leaf node is updated with its new label, depth and parent.

    char startChar {text[start]};
    char midChar {text[start + offset]};
    auto midNode {new SuffixTreeNode(node, node->stringDepth + offset,
                                     start, start + offset - 1)};

    // The former leaf node now becomes a child of midNode
    midNode->children[midChar] = node->children[startChar];

    node->children[startChar]->parent = midNode;
    node->children[startChar]->edgeStart += offset;
    // midNode becomes a child of node
    node->children[startChar] = midNode;

    return midNode;
}

void SuffixTree::build(const std::vector<int> &suffixArray, const std::vector<int> &lcpArray)
{
    // Builds the suffix tree starting from the suffix array and the lcp array
    int lcpPrev {0};
    SuffixTreeNode* currentNode {m_root};

    // Iterate over the suffixes in the suffix array
    for (auto ii {0}; ii < m_text.size(); ++ii)
    {
        int suffix {suffixArray[ii]};
        // When the depth is greater than the lcp we must go up in the tree to find out of
        // the suffixes have a common prefix
        while(currentNode->stringDepth > lcpPrev)
            currentNode = currentNode->parent;
        // We check if the depth is equal to the lcp value of the suffixes, meaning that there
        // is no overlap between the suffixes, and we just create a new node
        if (currentNode->stringDepth == lcpPrev)
        {
            currentNode = createNewLeaf(m_text, currentNode, suffix);
            m_numEdges++;
        }
        else
        {
            // In this case the suffixes overlap, and we must split the edge before
            // adding a new node
            int edgeStart {suffixArray[ii - 1] + currentNode->stringDepth};
            int offset {lcpPrev - currentNode->stringDepth};
            SuffixTreeNode* midNode {breakEdge(m_text, currentNode, edgeStart, offset)};
            currentNode = createNewLeaf(m_text, midNode, suffix);
            m_numEdges += 2;
        }
        if (ii < m_text.size() - 1)
            lcpPrev = lcpArray[ii];
    }
}