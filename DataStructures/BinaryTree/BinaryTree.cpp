//
// Created by daniel on 3/05/22.
//

#include "BinaryTree.h"

// Public Methods

void BinaryTree::fromString(const std::string& treeStr)
{
    // Create a tree from a string
    if (!isEmpty())
        clear();

    std::string numberStr;
    std::string numNodesStr;

    size_t position {treeStr.find(' ')};
    for (size_t current_pos {0}; current_pos < position; ++current_pos)
        numNodesStr += treeStr[current_pos];

    int numNodes {std::stoi(numNodesStr)};

    int column {0};
    int right; int left; int data;

    for (auto ii {position + 1}; ii < treeStr.size(); ++ii)
    {
        if (treeStr[ii] == ' ')
        {
            if (column == 0)
                data = std::stoi(numberStr);
            else if (column == 1)
                left = std::stoi(numberStr);
            else
            {
                right = std::stoi(numberStr);
                column = -1;
                Node node (data, left, right);
                nodes.push_back(node);
            }
            column++;
            numberStr.clear();
        }
        else
            numberStr += treeStr[ii];
    }

    assert(static_cast<int>(nodes.size()) == numNodes);
}

void BinaryTree::fromFile(std::ifstream& treeFile)
{
    if (!isEmpty())
        clear();

    // Get the first line that contains the number of nodes
    std::string n_nodes_str;
    std::getline(treeFile, n_nodes_str);
    int numNodes {std::stoi(n_nodes_str)};

    int numberIndex {0};

    while (treeFile)
    {
        std::string line;
        std::getline(treeFile, line);

        if (line.empty())
            break;

        std::string strNumber;
        Node node{};

        for (char current: line)
        {
            if (current != ' ')
                strNumber += current;
            else
            {
                if (numberIndex == 0)
                    node.key = std::stoi(strNumber);
                else if (numberIndex == 1)
                    node.left  = std::stoi(strNumber);
                numberIndex++;
                strNumber.clear();
            }
        }
        // Add the right node index
        node.right = std::stoi(strNumber);
        strNumber.clear();

        // printNode(node);
        numberIndex = 0;
        nodes.push_back(node);

    }

    assert(numNodes == static_cast<int>(nodes.size()));
}

bool BinaryTree::isEmpty() const
{
    // Returns whether the tree is empty
    if (nodes.empty())
        return true;
    return false;
}

bool BinaryTree::isBinarySearchTree(char method) const
{
    if (method == 'r')
        return isSearchTreeRecursive(0,
                                     std::numeric_limits<int>::min(),
                                     std::numeric_limits<int>::max());
    else if (method == 'i')
        return isSearchTreeIterative();
    else
        throw;

}

std::vector<int> BinaryTree::preorderTraversal() const
{
    // Returns a vector with the keys of the tree in pre-order
    std::vector<int> data;
    if (!isEmpty())
        preorder(0, data);
    return data;
}

std::vector<int> BinaryTree::postOrderTraversal() const
{
    // Returns a vector with the keys of the tree in post-order
    std::vector<int> data;
    if (!isEmpty())
        postorder(0, data);
    return data;
}

std::vector<int> BinaryTree::inorderTraversal() const
{
    // Returns a vector with the keys of the tree in in-order
    std::vector<int> data;
    if (!isEmpty())
        inorder(0, data);
    return data;
}


// Private Methods

bool BinaryTree::isSearchTreeRecursive(int index, int minValue, int maxValue) const
{

}

bool BinaryTree::isSearchTreeIterative() const
{

}

void BinaryTree::preorder(int index, std::vector<int>& data) const
{
    if (index != -1)
    {
        Node node {nodes[index]};
        data.push_back(node.key);
        preorder(node.left, data);
        preorder(node.right, data);
    }
}

void BinaryTree::postorder(int index, std::vector<int>& data) const
{
    if (index != -1)
    {
        Node node {nodes[index]};
        postorder(node.left, data);
        postorder(node.right, data);
        data.push_back(node.key);
    }
}

void BinaryTree::inorder(int index, std::vector<int>& data) const
{
    if (index != -1)
    {
        Node node {nodes[index]};
        inorder(node.left, data);
        data.push_back(node.key);
        inorder(node.right, data);
    }
}
