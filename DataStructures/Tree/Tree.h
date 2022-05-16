//
// Created by daniel on 9/05/22.
//

#ifndef ALGORITHMS_TREE_H
#define ALGORITHMS_TREE_H

#include <fstream>
#include <string>
#include <vector>

class Node
{
private:
    int key {};
    std::vector<int> children;

public:

    Node() = default;;

    explicit Node(int _key) : key {_key}
    {

    }

    Node(int _key, std::vector<int> _children)
            : key {_key}, children {std::move(_children)}
    {

    }

    void addChild(int key);
    bool hasChildren() const;

    int getKey() const {return key;}
    void setKey(int _key) {key = _key;}

    const std::vector<int>& getChildren() const {return children;}
};

class Tree
{
private:
    std::vector<Node> m_nodes;
    int m_root {0};

    int heightRecursive(int root) const;

public:

    explicit Tree(std::ifstream& treeFile)
    {
        fromFile(treeFile);
    }

    Tree(const std::string& treeStr, int numNodes)
    {
        fromString(treeStr, numNodes);
    }

    void fromFile(std::ifstream& treeFile);

    void fromString(const std::string& treeStr, int numNodes);

    int numNodes() const {return static_cast<int>(m_nodes.size());}

    bool isEmpty() const;

    int height() const;

};

#endif //ALGORITHMS_TREE_H
