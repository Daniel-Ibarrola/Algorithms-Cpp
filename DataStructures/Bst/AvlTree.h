//
// Created by daniel on 3/05/22.
//

#ifndef ALGORITHMS_AVLTREE_H
#define ALGORITHMS_AVLTREE_H

#include <iostream>
#include <vector>

struct Node
{
    int key;
    int height {0};
    Node* parent {nullptr};
    Node* left   {nullptr};
    Node* right  {nullptr};

    Node(int _key, int _height, Node* _parent)
            : key {_key}, height {_height}, parent {_parent}
    {

    }
};

class empty_tree_error: public std::exception
{
    const char* what() const noexcept override
    {
        return "The tree is empty";
    }
};

class AvlTree
{
    // Binary search tree that has the property that for each of its nodes
    // |node.left.height - node.right.height| <= 1

private:
    Node* m_root {nullptr};

    static int nodeHeight(Node* node);

    static int nodeBalance(Node* node);

    static Node* rightRotation(Node* node);

    static Node* leftRotation(Node* node);

    static Node* leftRightRotation(Node* node);

    static Node* rightLeftRotation(Node* node);

    Node* _insert(Node* root, Node* parent, int key);

    Node* leftDescendant(Node* root);

    Node* rightAncestor(Node* root);

    Node* _next(Node* root);

    Node* _find(Node* root, int key);

    Node* findNearest(Node* root, int key);

    Node* _min(Node* root);

    Node* _max(Node* root);

public:

    AvlTree() = default;;

    bool isEmpty();

    void insert(int key);

    bool find(int key);

    std::vector<int> rangeSearch(int lower, int upper);

    int min();

    int max();

};


#endif //ALGORITHMS_AVLTREE_H
