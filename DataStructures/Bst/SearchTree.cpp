//
// Created by daniel on 3/05/22.
//

#include "SearchTree.h"

// Private Methods of Binary Search Tree

bool BinarySearchTree::findNode(Node* root, int data)
{
    // Returns whether a node with given data is present in the tree
    if (root == nullptr)
        return false;
    else if (root->data == data)
        return true;
    else if (data < root->data)
        return findNode(root->left, data);
    else
        return findNode(root->right, data);
}

int BinarySearchTree::findHeight(Node* root)
{
    // Returns height of the tree.
    if (root == nullptr)
        return -1;

    return std::max(findHeight(root->left), findHeight(root->right)) + 1;
}

Node* BinarySearchTree::minSubtree(Node* root)
{
    // Find the minimum element in a subtree
    if (isEmpty())
        throw empty_tree_error();

    Node* current {root};
    while (current->left != nullptr)
        current = current->left;

    return current;
}

Node* BinarySearchTree::maxSubtree(Node* root)
{
    // Find the maximum element ina subtree
    if (isEmpty())
        throw empty_tree_error();

    Node* current {root};
    while (current->right != nullptr)
        current = current->right;

    return current;

}

Node* BinarySearchTree::removeNode(Node*root, int data)
{
    // Removes a node recursively in the tree

    // First find the node
    if (root == nullptr)
        return root;
    else if (root->data < data)
        root->left = removeNode(root->left, data);
    else if (root->data > data)
        root->right = removeNode(root->right, data);
    else
    {
        // The node was found

        // Case 1: node has no children
        if (root->left==nullptr && root->right==nullptr)
        {   delete root;
            root = nullptr;
        }
            // Case 2: node has one child
        else if (root->left==nullptr)
        {
            Node* tmp {root};
            root = root->right;
            delete tmp;
        }
        else if (root->right==nullptr)
        {
            Node* tmp {root};
            root = root->left;
            delete tmp;
        }
            // Case 3: node has two children
        else
        {
            Node* min {minSubtree(root->right)};
            root->data = min->data;
            root->right = removeNode(root->right, min->data);
        }
    }

    return root;
}

void BinarySearchTree::preorderTraversal(Node* root)
{
    // Print the nodes in preorder
    if (root == nullptr)
        return;
    std::cout << root->data << ' ';
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void BinarySearchTree::inorderTraversal(Node* root)
{
    // Print the nodes in inorder
    if (root == nullptr)
        return;
    inorderTraversal(root->left);
    std::cout << root->data << ' ';
    inorderTraversal(root->right);
}

void BinarySearchTree::postOrderTraversal(Node* root)
{
    // Print the nodes in postorder
    if (root == nullptr)
        return;
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    std::cout << root->data << ' ';
}

// Public Methods of Binary Search Tree

bool BinarySearchTree::isEmpty()
{
    if (m_root == nullptr)
        return true;
    return false;
}

Node* BinarySearchTree::createNode(int data)
{
    Node* node {new Node};
    node->data = data;
    return node;
}

Node* BinarySearchTree::insertNode(Node* root, Node* new_node)
{
    // Inserts a new node with given data in the tree using recursion
    if (root == nullptr)
        root = new_node;
    else if (new_node->data <= root->data)
        root->left  = insertNode(root->left, new_node);
    else
        root->right = insertNode(root->right, new_node);

    return root;
}

void  BinarySearchTree::insert(int data)
{
    // Inserts a new node with given data in the tree
    // Wrapper for insertNode function
    Node* new_node {createNode(data)};
    m_root = insertNode(m_root, new_node);
}

void BinarySearchTree::remove(int data)
{
    // Deletes node with given data in the tree
    m_root = removeNode(m_root, data);
}

bool BinarySearchTree::find(int data)
{
    // Finds a node with given data in the tree
    // Wrapper for findNode function
    return findNode(m_root, data);
}

int BinarySearchTree::min()
{
    // Find the minimum element in the tree
    return minSubtree(m_root)->data;
}

int BinarySearchTree::max()
{
    // Find the maximum element in the tree
    return maxSubtree(m_root)->data;
}

int BinarySearchTree::height()
{
    // Returns height of the tree.
    // Wrapper method for findHeight.
    return findHeight(m_root);
}

void BinarySearchTree::levelOrder()
{
    // Print the nodes in level order traversal

    if (isEmpty())
        throw empty_tree_error();

    std::queue<Node*> nodes_queue;
    Node* current{m_root};
    nodes_queue.push(current);

    while(!nodes_queue.empty())
    {
        current = nodes_queue.front();
        nodes_queue.pop();
        std::cout << current->data << ' ';

        if (current->left != nullptr)
            nodes_queue.push(current->left);
        if (current->right != nullptr)
            nodes_queue.push(current->right);
    }

    std::cout << '\n';
}

void BinarySearchTree::preorder()
{
    // Print the nodes in preorder. Wrapper method for preorderTraversal
    preorderTraversal(m_root);
    std::cout << '\n';
}

void BinarySearchTree::inorder()
{
    // Print the nodes in inorder. Wrapper method for inorderTraversal
    inorderTraversal(m_root);
    std::cout << "\n";
}

void BinarySearchTree::postorder()
{
    // Print the nodes in postorder. Wrapper method for postorderTraversal
    postOrderTraversal(m_root);
    std::cout << '\n';
}