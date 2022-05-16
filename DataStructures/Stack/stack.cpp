//
// Created by daniel on 3/05/22.
//

#include "stack.h"

bool Stack::isEmpty()
{
    if (head== nullptr)
        return true;
    return false;
}

void Stack::push(int key)
{
    head = new Node(key, head);
    size++;
}

int Stack::top()
{
    if (isEmpty())
        throw empty_stack_error();
    return head->key;
}

void Stack::pop()
{
    if (isEmpty())
        throw empty_stack_error();
    Node* tmp {head};
    head = head->next;
    delete tmp;
    size--;
}

// Stack With Max

bool StackWithMax::isEmpty()
{
    if (size == 0)
        return true;
    return false;
}

void StackWithMax::push(int key)
{
    if (size >= maxSize)
        throw stack_full_error();
    items[size] = key;
    size++;
}

int StackWithMax::top()
{
    if (isEmpty())
        throw empty_stack_error();
    return items[size - 1];
}

void StackWithMax::pop()
{
    if (isEmpty())
        throw empty_stack_error();
    size--;
}