//
// Created by daniel on 3/05/22.
//

#ifndef ALGORITHMS_SPLAYTREE_H
#define ALGORITHMS_SPLAYTREE_H

#include <deque>
#include <iostream>
#include <vector>
#include <tuple>
#include <cassert>

struct Node
{
    int key;
    Node* parent {nullptr};
    Node* left   {nullptr};
    Node* right  {nullptr};

    Node(int _key, Node* _parent)
        : key {_key}, parent {_parent}
    {

    }
};

class empty_tree_error: public std::exception
{
    const char* what() const throw() override
    {
        return "The tree is empty";
    }
};

class no_left_child_error: public std::exception
{
    const char* what() const throw() override
    {
        return "Node does not have a left child";
    }
};

class no_right_child_error: public std::exception
{
    const char* what() const throw() override
    {
        return "Node does not have a right child";
    }
};

class parent_not_root_error: public std::exception
{
    const char* what() const throw() override
    {
        return "Node parent is not the root of the tree";
    }
};

class merge_error: public std::exception
{
    const char* what() const throw() override
    {
        return "Cannot merge trees. The other tree should be greater.";
    }
};


class SplayTree
{
    // Binary search tree that puts the most frequent queried nodes near the root
    private:
        Node* m_root {nullptr};
        int m_length {0};

        static Node* rightRotation(Node* node);

        static Node* leftRotation(Node* node);

        static Node* zig(Node* node);

        static Node* zigZig(Node* node);

        static Node* zagZag(Node* node);

        static Node* zagZig(Node* node);

        static Node* zigZag(Node* node);

        Node* splay(Node* node);

        Node* _insert(Node* root, Node* parent, int key);

        Node* _find(Node* root, int key);

        Node* _findSplayTree(int key);

        Node* leftDescendant(Node* node) const;

        Node* rightAncestor(Node* node) const;

        Node* _next(Node* node) const;

        Node* _max() const;

        Node* _min() const;

        void _inOrderTraversal(Node* root, std::vector<int>& keys) const;

        void _preOrderTraversal(Node* root, std::vector<int>& keys) const;

        void _postOrderTraversal(Node* root, std::vector<int>& keys) const;

    public:

        SplayTree() = default;;

        Node* getRoot() const {return m_root;}

        void setRoot(Node* node) {m_root = node;}

        void setLength(int len) {m_length = length();}

        int length() const {return m_length;}

        bool isEmpty() const;

        void insert(int key);

        void insertFromVector(const std::vector<int>& keys);

        void insertNoSplay(int key);

        bool find(int key);

        void remove(int key);

        int min() const;

        int max() const;

        int next(int key);

        std::vector<int> rangeSearch(int low, int upper);

        std::vector<int> levelOrderTraversal() const;

        std::vector<int> inOrderTraversal() const;

        std::vector<int> preOrderTraversal() const;

        std::vector<int> postOrderTraversal() const;

        void merge(SplayTree& tree);

};

std::tuple<SplayTree, SplayTree> split(SplayTree& tree, int key);

#endif //ALGORITHMS_SPLAYTREE_H
