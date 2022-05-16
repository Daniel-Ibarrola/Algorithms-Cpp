//
// Created by daniel on 3/05/22.
//

#include "doublelist.h"

bool DoublyLinkedList::isEmpty()
{
    if (head == nullptr)
        return true;
    return false;
}

void DoublyLinkedList::pushFront(int key)
{
    // Push an item to the front
    Node* newNode {new Node(key, head)};
    if (head != nullptr)
        head->prev = newNode;
    head = newNode;
    if (tail == nullptr)
    {
        tail = head;
    }

    size++;
}

void DoublyLinkedList::pushBack(int key)
{
    // Push an item to the back of the list
    if (isEmpty())
        pushFront(key);
    else
    {
        Node* newNode {new Node(key)};
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }

    size++;
}

int DoublyLinkedList::topFront()
{
    // Returns the front item
    if (isEmpty())
        throw empty_list_error();
    return head->key;
}

int DoublyLinkedList::topBack()
{
    // Returns the front item
    if (isEmpty())
        throw empty_list_error();
    return tail->key;
}

void DoublyLinkedList::popFront()
{
    // Remove front item from the list
    if (isEmpty())
        throw empty_list_error();

    // Case when there is only one node
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        Node* tmp {head};
        delete tmp;
        head = head->next;
        head->prev = nullptr;
    }

    size--;
}

void DoublyLinkedList::popBack()
{
    // Removes last item from the list
    if (isEmpty())
        throw empty_list_error();

    // Case when there is only one node
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        Node* tmp {tail};
        delete tmp;
        tail = tail->prev;
        tail->next = nullptr;
    }

    size++;
}

void DoublyLinkedList::insertAt(int key, int position)
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
        Node* current {head};
        int currentPos {0};
        while (currentPos != position)
        {
            currentPos++;
            current = current->next;
        }
        Node* newNode {new Node(key, current, current->prev)};
        current->prev->next = newNode;
        current->prev = newNode;
    }

    size++;
}

void DoublyLinkedList::deleteAt(int position)
{
    // Deletes a node at a given position
    if (position > size)
        throw out_of_range_error();

    if (position == 0)
        popFront();
    else if (position == size)
        popBack();
    else
    {
        Node* current {head};
        int currentPos {0};
        while (currentPos != position)
        {
            currentPos++;
            current = current->next;
        }
        Node* tmp {current};
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete tmp;
    }

    size--;
}

void DoublyLinkedList::print()
{
    // Prints the list
    std::cout << "[";
    if (!isEmpty())
    {
        Node* current {head};
        for (int ii {0}; ii < size - 1; ++ii)
        {
            std::cout << current->key << " ";
            current = current->next;
        }
        // Print the last key without a space in the end
        std::cout << current->key;
    }
    std::cout << "]\n";
}