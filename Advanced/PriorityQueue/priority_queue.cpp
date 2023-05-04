//
// Created by daniel on 2/05/23.
//

#include "priority_queue.h"


bool operator== (const Task& t1, const Task& t2)
{
    return t1.element == t2.element && t1.priority == t2.priority;
}


std::size_t PQHeap::getParentIndex(std::size_t index)
{
    // Get the index of the parent of the node with the given index
    return (index - 1) / 2;
}

void PQHeap::bubbleUp(std::size_t index)
{
    // Move the element with the given index up in the heap
    // until its priority is lower than its children's, or it reaches the root
    Task current {m_tasks[index]};
    while (index > 0)
    {
        std::size_t parentIndex {getParentIndex(index)};
        if (m_tasks[parentIndex].priority < current.priority)
        {
            m_tasks[index] = m_tasks[parentIndex];
            index = parentIndex;
        }
        else
            break;
    }
    m_tasks[index] = current;
}

std::size_t PQHeap::getFirstLeafIndex() const
{
    // Returns the index of the first leaf
    return ((m_tasks.size() - 2) / 2) + 1;
}

std::size_t PQHeap::highestPriorityChild(std::size_t parentIndex) const
{
    // Returns the index of the given parent node's child with the highest priority
    std::size_t child1 {(2 * parentIndex )+ 1};
    std::size_t child2 {2 * (parentIndex + 1)};
    if (m_tasks[child1].priority > m_tasks[child2].priority)
        return child1;
    return child2;
}

void PQHeap::pushDown(std::size_t index)
{
    // Move an element down the heap
    Task current {m_tasks[index]};
    std::size_t firstLeaf {getFirstLeafIndex()};
    while (index < firstLeaf)
    {
        std::size_t childIndex {highestPriorityChild(index)};
        if (m_tasks[childIndex].priority > current.priority )
        {
            m_tasks[index] = m_tasks[childIndex];
            index = childIndex;
        }
        else
            break;
    }
    m_tasks[index] = current;
}


void PQHeap::insert(const std::string& task, int priority)
{
    // Inserts an element into the heap
    Task newTask {task, priority};
    m_tasks.push_back(newTask);
    bubbleUp(m_tasks.size() - 1);
}

std::string PQHeap::peek() const
{
    // Returns the top element
    if (empty()) throw EmptyHeapError();
    return m_tasks[0].element;
}

std::string PQHeap::top()
{
    // Returns the top element and removes it from the queue
    if (empty())
        throw EmptyHeapError();

    Task lastTask {m_tasks[m_tasks.size() - 1]};
    m_tasks.pop_back();

    if (empty())
        return lastTask.element;

    Task topTask {m_tasks[0]};
    m_tasks[0] = lastTask;
    pushDown(0);
    return topTask.element;
}

void PQHeap::remove(const std::string &task)
{
    // Remove an element from the queue

}

void PQHeap::update(const std::string &task, int priority)
{
    // Update the priority of an element

}
