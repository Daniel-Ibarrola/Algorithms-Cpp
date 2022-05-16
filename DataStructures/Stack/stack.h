//
// Created by daniel on 3/05/22.
//

#ifndef ALGORITHMS_STACK_H
#define ALGORITHMS_STACK_H

#include <iostream>

struct Node
{
    int key {};
    Node* next{nullptr};

    explicit Node(int _key) : key {_key}
    {

    }

    Node(int _key, Node* _next)
        : key {_key}, next {_next}
    {

    }

};

class empty_stack_error: public std::exception
{
    const char* what() const noexcept override
    {
        return "The list is empty";
    }
};

class Stack
{
    // Stack class. Linked List implementation
private:
    Node* head {nullptr};
    int size {0};
public:
    Stack() = default;;

    bool isEmpty();

    void push(int key);

    int top();

    void pop();

    int length() const {return size;}
};

#endif //ALGORITHMS_STACK_H

class stack_full_error: public std::exception
{
    const char* what() const noexcept override
    {
        return "The list is empty";
    }
};


class StackWithMax
{
    // Array implementation of stack. This stack has a max size
private:

    int* items;
    int size {0};
    int maxSize;

public:

    StackWithMax(int capacity)
    {
        items = new int[capacity];
        maxSize = capacity;
    }

    bool isEmpty();

    void push(int key);

    int top();

    void pop();

    int length() const {return size;}

};