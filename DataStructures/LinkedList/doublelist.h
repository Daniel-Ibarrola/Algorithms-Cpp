//
// Created by daniel on 3/05/22.
//

#ifndef ALGORITHMS_DOUBLELIST_H
#define ALGORITHMS_DOUBLELIST_H

#include <iostream>

struct Node
{
    int key {};
    Node* next {nullptr};
    Node* prev {nullptr};

    explicit Node (int _key) : key {_key}
    {

    }

    Node(int _key, Node* _next)
        : key {_key}, next {_next}
    {

    }

    Node(int _key, Node* _next, Node* _prev)
            : key {_key}, next {_next}, prev {_prev}
    {

    }
};

class empty_list_error: public std::exception
{
    const char* what() const noexcept override
    {
        return "The list is empty";
    }
};

class out_of_range_error: public std::exception
{
    const char* what() const noexcept override
    {
        return "The list is empty";
    }
};

class DoublyLinkedList
{
private:
    Node* head {nullptr};
    Node* tail {nullptr};
    int size {0};

public:

    DoublyLinkedList() = default;;

    bool isEmpty();

    void pushFront(int key);

    void pushBack(int key);

    int topFront();

    void popFront();

    int topBack();

    void popBack();

    void insertAt(int key, int position);

    void deleteAt(int position);

    void print();

    int length() const {return size;}
};

#endif //ALGORITHMS_DOUBLELIST_H
