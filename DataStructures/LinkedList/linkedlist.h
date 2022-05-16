//
// Created by daniel on 3/05/22.
//

#ifndef ALGORITHMS_LINKEDLIST_H
#define ALGORITHMS_LINKEDLIST_H

#include <iostream>

struct Node
{
    int key {};
    Node* next {nullptr};

    explicit Node(int _key) : key {_key}
    {

    }

    Node(int _key, Node* _next)
        : key {_key}, next {_next}
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

class LinkedList
{
private:
    Node* head {nullptr};
    Node* tail {nullptr};
    int size {0};

public:

    LinkedList() = default;;

    bool isEmpty();

    void pushFront(int key);

    int topFront();

    void popFront();

    void pushBack(int key);

    int topBack();

    void popBack();

    void insertAt(int key, int position);

    void deleteAt(int position);

    void deleteKey(int key);

    int length() const {return size;}

};


#endif //ALGORITHMS_LINKEDLIST_H
