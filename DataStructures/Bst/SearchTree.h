//
// Created by daniel on 3/05/22.
//

#ifndef ALGORITHMS_SEARCHTREE_H
#define ALGORITHMS_SEARCHTREE_H

#include <queue>
#include <vector>
#include <iostream>

struct Node
{
    int data {};
    Node* left {nullptr};
    Node* right {nullptr};
};

class empty_tree_error: public std::exception
{
    const char* what() const throw() override
    {
        return "The tree is empty";
    }
};

class BinarySearchTree
{
    // Binary Search tree class
private:
    Node* m_root {nullptr};

    bool findNode(Node* root, int data);

    int findHeight(Node* root);

    Node* minSubtree(Node* root);

    Node* maxSubtree(Node* root);

    Node* removeNode(Node*root, int data);

    void preorderTraversal(Node* root);

    void inorderTraversal(Node* root);

    void postOrderTraversal(Node* root);

public:

    BinarySearchTree() = default;;

    bool isEmpty();

    static Node* createNode(int data);

    Node* insertNode(Node* root, Node* new_node);

    void insert(int data);

    void remove(int data);

    bool find(int data);

    int min();

    int max();

    int height();

    void levelOrder();

    void preorder();

    void inorder();

    void postorder();
};
#endif //ALGORITHMS_SEARCHTREE_H
