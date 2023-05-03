//
// Created by daniel on 3/05/22.
//

#ifndef ALGORITHMS_BINARYTREE_H
#define ALGORITHMS_BINARYTREE_H

#include <cassert>
#include <limits>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Node
{
    int key;
    int left;
    int right;

    Node() = default;;

    explicit Node(int _key)
        : key {_key}, left {-1}, right {-1}
    {

    }

    Node(int _key, int _left, int _right)
        : key {_key}, left {_left}, right {_right}
    {

    }
};

class BinaryTree
{
private:
    std::vector<Node> nodes;

    void preorder(int index, std::vector<int>& data) const;

    void postorder(int index, std::vector<int>& data) const;

    void inorder(int index, std::vector<int>& data) const;

public:

    BinaryTree() = default;;

    explicit BinaryTree(std::vector<Node>  _nodes)
        : nodes {std::move(_nodes)}
    {

    }

    explicit BinaryTree(const std::string& treeStr)
    {
        fromString(treeStr);
    }

    explicit BinaryTree(std::ifstream& treeFile)
    {
        fromFile(treeFile);
    }

    void fromString(const std::string& treeStr);

    void fromFile(std::ifstream& treeFile);

    void clear() {nodes.clear();}

    std::size_t size() const {return nodes.size();}

    bool isEmpty() const;


    std::vector<int> preorderTraversal() const;
    std::vector<int> postOrderTraversal() const;
    std::vector<int> inorderTraversal() const;

};


#endif //ALGORITHMS_BINARYTREE_H
