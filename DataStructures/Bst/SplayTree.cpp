//
// Created by daniel on 3/05/22.
//

#include "SplayTree.h"

// Private Methods
Node *SplayTree::rightRotation(Node *node)
{
    // Performs a right rotation

    Node* leftTemp {node->left};
    if (leftTemp == nullptr)
        throw no_left_child_error();

    // Fix parents
    leftTemp->parent = node->parent;
    node->parent = leftTemp;
    if (leftTemp->right != nullptr)
        leftTemp->right->parent = node;

    // Rewire left and right
    node->left = leftTemp->right;
    leftTemp->right = node;

    if (leftTemp->parent != nullptr)
    {
        // Check if the node is a left subtree of another node
        if (leftTemp->parent->left != nullptr
            && leftTemp->parent->left->key == leftTemp->right->key)
            leftTemp->parent->left = leftTemp;
        else {
            // The node is the right subtree of another node
            leftTemp->parent->right = leftTemp;
        }
    }

    return leftTemp;
}

Node *SplayTree::leftRotation(Node *node)
{
    // Performs a left rotation

    Node* rightTemp {node->right};
    if (rightTemp == nullptr)
        throw no_right_child_error();

    // Fix Parents
    rightTemp->parent = node->parent;
    node->parent = rightTemp;
    if (rightTemp->left != nullptr)
        rightTemp->left->parent = node;

    // Rewire left and right
    node->right = rightTemp->left;
    rightTemp->left = node;
    if (rightTemp->parent != nullptr)
    {
        // Check if the node is a left subtree of another node
        if (rightTemp->parent->left != nullptr &&
        rightTemp->parent->left->key == rightTemp->left->key)
            rightTemp->parent->left = rightTemp;
        else
            // The node is the right subtree of another node
            rightTemp->parent->right = rightTemp;
    }

    return rightTemp;
}

Node* SplayTree::zig(Node *node)
{
    // Rotates the given node so it becomes the root. Node parent must be the root
    if (node->parent->parent != nullptr)
        throw parent_not_root_error();

    // If node is to the left of parent perform right rotation
    if (node->parent->left != nullptr &&
    node->parent->left->key == node->key)
        node = rightRotation(node);
    else
        // Node is to the right of parent. Perform left rotation
        node = leftRotation(node);

    return node;
}

Node* SplayTree::zigZig(Node *node)
{
    // Splay operation when a node is to the left of its
    // parent and grandparent

    // Perform two right rotations
    node = rightRotation(node);
    return rightRotation(node);
}

Node* SplayTree::zagZag(Node *node)
{
    // Splay operation when a node is to the right of its
    // parent and grandparent

    // Perform two left rotations
    node = leftRotation(node);
    return leftRotation(node);
}

Node* SplayTree::zagZig(Node *node)
{
    // Splay operation when a node is to the right of its parent and
    // its parent is to the left of its grandparent

    // Perform left rotation followed by right rotation
    node = leftRotation(node);
    return rightRotation(node);
}

Node* SplayTree::zigZag(Node *node)
{
    // Splay operation when a node is to the left of its parent and
    // its parent is to the right of its grandparent

    // Perform right rotation followed by left rotation
    node = rightRotation(node);
    return leftRotation(node);
}

Node* SplayTree::splay(Node *node)
{
    // Makes the given node become the root of the tree

    // Base case: Node is the root of the tree
    if (node->parent == nullptr)
        return node;

    Node* grandparent {node->parent->parent};
    // Case: The node has no grandparent. Perform zig
    if (grandparent == nullptr)
        node = zig(node);
    // Case: The parent and the node are to the right of the grandparent
    else if (grandparent->right == node->parent &&
    node->parent->right == node)
    {
        node = zagZag(node);
    }
    // Case: The parent and the node are to the left of the grandparent
    else if (grandparent->left == node->left &&
             node->parent->left == node)
    {
        node = zigZig(node);
    }
    // Case: The parent is to the right of the grandparent, and the node is to the
    // left of its parent
    else if (grandparent->right == node->parent &&
             node->parent->left == node)
    {
        node = zigZag(node);
    }
    // Case: The parent is to the left of the grandparent, and the node is to the
    // right of its parent
    else if (grandparent->left == node->parent &&
             node->parent->right == node)
    {
        node = zagZig(node);
    }

    return splay(node);
}

Node* SplayTree::_insert(Node *root, Node *parent, int key)
{
    // Inserts a new node in the tree recursively.

    // Base case
    if (root == nullptr)
        return new Node(key, parent);
    else if (key < root->key)
        root->left = _insert(root->left, root, key);
    else
        root->right = _insert(root->right, root, key);

    return root;
}

Node* SplayTree::_find(Node *root, int key)
{
    // Finds the node with the given key. If it's not found it returns
    // the node with the closest key

    // Go to the left
    if (key < root->key && root->left != nullptr)
        return _find(root->left, key);
    // Go to the right
    else if (key > root->key && root->right != nullptr)
        return _find(root->right, key);
    else
        return root;

}

Node* SplayTree::_findSplayTree(int key)
{
    // Finds the node with the key closest to the given one
    // and splays that node to the root
    Node* node {_find(m_root, key)};
    m_root = splay(node);
    return node;
}

Node* SplayTree::leftDescendant(Node* node) const
{
    // Returns the left descendant of the node
    if (node->left != nullptr)
        return leftDescendant(node->left);
    else
        return node;
}

Node* SplayTree::rightAncestor(Node *node) const
{
    // Returns the right ancestor of the node

    // Base Case: node is the root node
    if (node->parent != nullptr)
        return node;

    if (node->parent->key > node->key)
        return node;
    else
        return rightAncestor(node->parent);
}

Node* SplayTree::_next(Node *node) const
{
    // Returns the node with the next larger key
    if (node->right != nullptr)
        return leftDescendant(node->right);
    return rightAncestor(node);
}

Node *SplayTree::_max() const
{
    // Returns the maximum node of the tree
    if (isEmpty())
        throw empty_tree_error();

    Node* current {m_root};
    while (current->right != nullptr)
        current = current->right;

    return current;
}

Node *SplayTree::_min() const
{
    // Returns the minimum node of the tree
    if (isEmpty())
        throw empty_tree_error();

    Node* current {m_root};
    while (current->left != nullptr)
        current = current->left;

    return current;
}

void SplayTree::_inOrderTraversal(Node *root, std::vector<int> &keys) const
{
    // Traverse the tree recursively in in-order
    if (root != nullptr)
    {
        _inOrderTraversal(root->left, keys);
        keys.push_back(root->key);
        _inOrderTraversal(root->right, keys);
    }
}

void SplayTree::_preOrderTraversal(Node *root, std::vector<int> &keys) const
{
    // Traverse the tree recursively in pre-order
    if (root != nullptr)
    {
        keys.push_back(root->key);
        _preOrderTraversal(root->left, keys);
        _preOrderTraversal(root->right, keys);
    }
}

void SplayTree::_postOrderTraversal(Node *root, std::vector<int> &keys) const
{
    // Traverse the tree recursively in post-order
    if (root != nullptr)
    {
        _postOrderTraversal(root->left, keys);
        _postOrderTraversal(root->right, keys);
        keys.push_back(root->key);
    }
}


// Public Methods

bool SplayTree::isEmpty() const
{
    // Returns whether the tree is empty
    if (m_root == nullptr)
        return true;
    return false;
}

void SplayTree::insert(int key)
{
    // Inserts a node in the tree and then splays that node
    m_root = _insert(m_root, nullptr, key);
    m_root = _findSplayTree(key);
    m_length++;
}

void SplayTree::insertNoSplay(int key)
{
    // Inserts a node in the tree without splaying the tree
    m_root = _insert(m_root, nullptr, key);
    m_length++;
}

void SplayTree::insertFromVector(const std::vector<int>& keys)
{
    // Inserts new nodes from a vector with the keys
    for (auto k : keys)
        insert(k);
}

bool SplayTree::find(int key)
{
    // Returns whether there is a node with the given key in the tree
    if (isEmpty())
        return false;

    if (_findSplayTree(key)->key == key)
        return true;
    return false;
}


void SplayTree::remove(int key)
{
    // Deletes a node from the tree
    Node* node  {_find(m_root, key)};
    if (node->key != key)
        return;

    // Splay the successor of the node
    Node* successor {splay(_next(node))};
    // Splay the node, so it becomes the root, and it's successor is to
    // the right
    node = splay(node);

    Node* left {node->left};
    // Case when the node is the largest and has no successor
    if (successor->key == node->key)
    {
        left->parent = nullptr;
        m_root = left;
    }
    else
    {
        if (left != nullptr)
            left->parent = successor;
        successor->left = left;
        successor->parent = nullptr;
        m_root = successor;
    }
    delete node;
    m_length--;
}

int SplayTree::min() const
{
    // Returns the minimum key of the tree
    return _min()->key;
}

int SplayTree::max() const
{
    // Returns the maximum key of the tree
    return _max()->key;
}

int  SplayTree::next(int key)
{
    // Returns the next key
    Node* node {_findSplayTree(key)};
    return _next(node)->key;
}

std::vector<int> SplayTree::rangeSearch(int low, int upper)
{
    // Returns all keys in the given range
    assert(low <= upper);

    std::vector<int> keys;
    Node* current {_findSplayTree(low)};
    while (current->key <= upper)
    {
        keys.push_back(current->key);
        current = _next(current);
    }

    return keys;
}

std::vector<int> SplayTree::levelOrderTraversal() const
{
    // Traverse the tree in level order

    std::vector<int> keys;
    if (isEmpty())
        return keys;

    Node* current;
    std::deque<Node*> nodes;
    nodes.push_front(m_root);

    while (!nodes.empty())
    {
        current = nodes.front();
        nodes.pop_front();

        if (current->left != nullptr)
            nodes.push_back(current->left);
        if (current->right != nullptr)
            nodes.push_back(current->left);

        keys.push_back(current->key);

    }

    return keys;
}

std::vector<int> SplayTree::inOrderTraversal() const
{
    // Returns a vector with the keys in in-order
    std::vector<int> keys;
    _inOrderTraversal(m_root, keys);
    return keys;
}

std::vector<int> SplayTree::preOrderTraversal() const
{
    // Returns a vector with the keys in pre-order
    std::vector<int> keys;
    _preOrderTraversal(m_root, keys);
    return keys;
}

std::vector<int> SplayTree::postOrderTraversal() const
{
    // Returns a vector with the keys in post-order
    std::vector<int> keys;
    _postOrderTraversal(m_root, keys);
    return keys;
}

void SplayTree::merge(SplayTree &tree)
{
    // Merge two trees into a single one. The elements of the other tree should
    // be greater than those of the current tree

    // Find max of this tree and splay it
    m_root = splay(_max());
    if (m_root->key < tree.min())
        throw merge_error();
    // Now root has no right child
    assert(m_root->right == nullptr);

    Node* rightRoot {tree.m_root};
    m_root->right = rightRoot;
    rightRoot->parent = m_root;
    m_length += tree.m_length;
}

std::tuple<SplayTree, SplayTree> split(SplayTree& tree, int key)
{
    // Splits the tree into two trees based on a key

    Node* rootLeft {tree.getRoot()};
    Node* rootRight {rootLeft->right};
    rootLeft->right = nullptr;

    if (rootRight != nullptr)
        rootRight->parent = nullptr;

    SplayTree leftTree;
    SplayTree rightTree;

    leftTree.setRoot(rootLeft);
    rightTree.setRoot(rootRight);

    // Recompute the number of nodes
    int nodesLeft {static_cast<int>(leftTree.levelOrderTraversal().size())};
    leftTree.setLength(nodesLeft);
    rightTree.setLength(tree.length() - nodesLeft );

    return {leftTree, rightTree};
}


