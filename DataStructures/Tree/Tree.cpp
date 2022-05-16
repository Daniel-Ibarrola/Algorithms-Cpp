//
// Created by daniel on 9/05/22.
//

#include "Tree.h"

// Node class methods

void Node::addChild(int _key)
{
    // Add a child to the node
    children.push_back(_key);
}

bool Node::hasChildren() const
{
    // Check if the node has children
    if (children.empty())
        return false;
    return true;
}

// Tree class methods

void Tree::fromFile(std::ifstream &treeFile)
{
    // Creates a tree from a file.

    // The first line of the file contains the number of nodes.
    // The second line contains the nodes
    if (!isEmpty())
        m_nodes.clear();

    std::string numNodesStr;
    std::getline(treeFile, numNodesStr);
    int numNodes {std::stoi(numNodesStr)};

    std::string treeStr;
    std::getline(treeFile, treeStr);

    fromString(treeStr, numNodes);
}

void Tree::fromString(const std::string &treeStr, int numNodes)
{
    // Creates a tree from a string

    std::vector<Node> nodes (numNodes);

    std::string numberStr;
    int childIndex;
    int ii {0};


    for (char current : treeStr)
    {
        if (current == ' ')
        {
            childIndex = std::stoi(numberStr);
            if (childIndex == -1)
                m_root = ii;
            else
                nodes[childIndex].addChild(ii);
            nodes[ii].setKey(ii);
            ii++;

            numberStr.clear();
        }
        else
            numberStr += current;
    }

}

bool Tree::isEmpty() const
{
    // Checks if the tree is empty
    if (m_nodes.empty())
        return true;
    return false;
}


int Tree::height() const
{
    // Returns the height of the tree
    if (isEmpty())
        return 0;
    return heightRecursive(m_root);
}

int Tree::heightRecursive(int root) const
{
    // Computes the height of the tree recursively

    // Base Case: Node has no children
    if (!m_nodes[root].hasChildren())
        return 1;
    else
    {
        int height {1};
        for (auto child : m_nodes[root].getChildren())
            height = std::max(height, heightRecursive(child));
        return height + 1;
    }
}