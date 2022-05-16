//
// Created by daniel on 3/05/22.
//

#include "linkedlist.h"

bool LinkedList::isEmpty()
{
    // Returns whether the list is empty
    if (head == nullptr)
        return true;
    return false;
}

void LinkedList::pushFront(int key)
{
    // Pushes an item to the front of the list
    Node* newNode {new Node(key, head)};
    head = newNode;
    if (tail == nullptr)
        tail = head;
    size++;
}

int LinkedList::topFront()
{
    // Returns front item
    if (isEmpty())
        throw empty_list_error();
    return head->key;
}

void LinkedList::popFront()
{
    // Removes front item
    if (isEmpty())
        throw empty_list_error();

    Node* tmp {head};
    head = head->next;
    delete tmp;
    size--;
}

void LinkedList::pushBack(int key)
{
    // Push an item to the back of the list
    if (isEmpty())
    {
        pushFront(key);
    }
    else
    {
        Node* newNode {new Node(key)};
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

int LinkedList::topBack()
{
    // Returns last item
    if (isEmpty())
        throw empty_list_error();
    return tail->key;
}

void LinkedList::popBack()
{
    // Removes back item
    if (isEmpty())
        throw empty_list_error();

    // Case when there is a single node
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        // Iterate through the list to find the tail
        Node* current {head};
        while (current->next->next != nullptr)
            current = current->next;
        // Current is now the node before the tail
        delete tail;
        tail = current;
        current->next = nullptr;
    }

    size--;
}

void LinkedList::insertAt(int key, int position)
{
    // Inserts a key at a given position

    if (position > size)
        throw out_of_range_error();

    if (position == 0)
        pushFront(key);
    else if (position == size)
        pushBack(key);
    else
    {
        // Iterate to find the position
        int currentPos {0};
        Node* current {head};
        Node* previous;
        while (currentPos != position)
        {
            previous = current;
            current = current->next;
            currentPos++;
        }
        // Rewire the nodes
        Node* newNode {new Node(key, current)};
        previous->next = newNode;
    }

    size++;
}

void LinkedList::deleteAt(int position)
{
    // Delete key at given position

    if (position > size)
        throw out_of_range_error();

    if (position == 0)
        popFront();
    else if (position == size)
        popBack();
    else
    {
        // Iterate to find the position
        int currentPos {0};
        Node* current {head};
        Node* previous;
        while (currentPos != position)
        {
            previous = current;
            current = current->next;
            currentPos++;
        }
        // Rewire the nodes
        previous->next = current->next;
        delete current;
    }

    size--;
}

void LinkedList::deleteKey(int key)
{
    // Deletes the first node that has the given key. If it's not found
    // the list remains unaltered
    if (!isEmpty())
    {
        Node* current {head};
        Node* previous {current};
        while (current->next != nullptr)
        {
            if (current->key == key)
            {
                // Delete the current node
                previous->next = current->next;
                delete current;
                break;
            }
            previous = current;
            current = current->next;
        }
    }

    size--;
}