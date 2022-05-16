//
// Created by daniel on 3/05/22.
//

#include "AvlTree.h"

// Private Methods

int AvlTree::nodeHeight(Node* node)
{
    // Returns the height of a node
    if (node == nullptr)
        return -1;
    return node->height;
}

int AvlTree::nodeBalance(Node* node)
{
    //Returns the balance of a node
    if (node == nullptr)
        return 0;
    return nodeHeight(node->left) - nodeHeight(node->right);
}

Node* AvlTree::rightRotation(Node* node)
{
    // Performs a right rotation of the nodes
    Node* left_temp {node->left};
    // Fix parents
    left_temp->parent = node->parent;
    node->parent = left_temp;
    // Rewire left and right
    node->left = left_temp->right;
    left_temp->right = node;

    // Update the heights
    node->height = 1 + std::max(nodeHeight(node->left),
                                nodeHeight(node->right));
    left_temp->height = 1 + std::max(nodeHeight(left_temp->left),
                                     nodeHeight(left_temp->right));

    return left_temp;
}

Node* AvlTree::leftRotation(Node* node)
{
    // Performs a left rotation of the nodes
    Node* right_temp {node->right};
    // Fix parents
    right_temp->parent = node->parent;
    node->parent = right_temp;
    // Rewire left and right
    node->right = right_temp->left;
    right_temp->left = node;

    // Update the heights
    node->height = 1 + std::max(nodeHeight(node->left),
                                nodeHeight(node->right));
    right_temp->height = 1 + std::max(nodeHeight(right_temp->left),
                                      nodeHeight(right_temp->right));

    return right_temp;
}

Node* AvlTree::leftRightRotation(Node* node)
{
    // Perform a left rotation followed by a right rotation
    node->left = leftRotation(node->left);
    return rightRotation(node);
}

Node* AvlTree::rightLeftRotation(Node* node)
{
    // Perform a right rotation followed by a left rotation
    node->right = rightRotation(node->right);
    return leftRotation(node);
}

Node* AvlTree::_insert(Node* root, Node* parent, int key)
{
    // Inserts a node in the tree and then rebalances it
    // to keep the avl property
    if (root == nullptr)
    {
        Node* node {new Node(key, 0, parent)};
        root = node;
        return root;
    }
    else if (key < root->key)
        root->left  = _insert(root->left,  root, key);
    else
        root->right = _insert(root->right, root, key);

    root->height = 1 + std::max(nodeHeight(root->left),
                                nodeHeight(root->right));

    int balance {nodeBalance(root)};
    if (balance > 1) // Left imbalance
    {
        // Check if we need to perform right rotation or left-right rotation
        if (nodeBalance(root->left) >= 0)
            root = rightRotation(root);
        else
            root = leftRightRotation(root);
    }
    else if (balance < -1) // right imbalance
    {
        // Check if we need to perform left rotation or right-left rotation
        if (nodeBalance(root->right) <= 0)
            root = leftRotation(root);
        else
            root = rightLeftRotation(root);
    }

    return root;
}

Node* AvlTree::leftDescendant(Node* root)
{
    if (root->left == nullptr)
        return root;
    else
        return leftDescendant(root->left);
}

Node* AvlTree::rightAncestor(Node* root)
{
    if (root == nullptr)
        return root;

    if (root->parent->key > root->key)
        return root->parent;
    else
        return rightAncestor(root->parent);
}

Node* AvlTree::_next(Node* root)
{
    // Returns the node with the next larger key
    if (root->right != nullptr)
        return leftDescendant(root->right);
    else
        return rightAncestor(root);
}

Node* AvlTree::_find(Node* root, int key)
{
    // Find a node with a given key and return it.
    // Returns a nullptr if the node isn't find.
    if (root == nullptr || root->key == key)
        return root;
    else if (key < root->key)
        return _find(root->left, key);
    else
        return _find(root->right, key);
}

Node* AvlTree::findNearest(Node* root, int key)
{
    // Find a node with a given key and return it.
    // If there isn't a node with such key returns
    // the node with the nearest key
    if (root->key == key)
        return root;
    else if (key < root->key && root->left != nullptr)
        return findNearest(root->left, key);
    else if (key > root->key && root->right != nullptr)
        return findNearest(root->right, key);
    else if (root->key > key)
        return root;
    else
        return _next(root);
}

Node* AvlTree::_min(Node* root)
{
    // Returns the node with the minimal key
    if (isEmpty())
        throw empty_tree_error();

    Node* current {root};
    while (current->left != nullptr)
    {
        current = current->left;
    }

    return current;
}

Node* AvlTree::_max(Node* root)
{
    // Returns the node with the maximal key

    if (isEmpty())
        throw empty_tree_error();

    Node* current {root};
    while (current->right != nullptr)
    {
        current = current->right;
    }

    return current;
}


// Public Methods

bool AvlTree::isEmpty()
{
    // Check if the tree is empty
    if (m_root == nullptr)
        return true;
    return false;
}

void AvlTree::insert(int key)
{
    // Inserts a node in the tree
    m_root = _insert(m_root, nullptr, key);
}

bool AvlTree::find(int key)
{
    // Returns whether the specified key is in the tree
    if (_find(m_root, key) == nullptr)
        return false;
    return true;
}

std::vector<int> AvlTree::rangeSearch(int lower, int upper)
{
    // Returns a vector with all node keys within the specified range

    std::vector<int> nodeData {};
    // Find a node with key greater or equal to the lower bound
    Node* startNode {findNearest(m_root, lower)};

    while (startNode->key <= upper)
    {
        if (startNode->key >= lower)
            nodeData.push_back(startNode->key);
        startNode = _next(startNode);
    }

    return nodeData;
}

int AvlTree::min()
{
    // Returns the minimum key in the tree
    return _min(m_root)->key;
}

int AvlTree::max()
{
    // Returns the maximum key in the tree
    return _max(m_root)->key;
}