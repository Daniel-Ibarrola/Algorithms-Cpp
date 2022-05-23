//
// Created by daniel on 21/05/22.
//

#include "heap.h"

bool Heap::isEmpty() const
{
    if (m_size == 0)
        return true;
    return false;
}

bool Heap::isFull() const
{
    if (m_size == m_maxSize)
        return true;
    return false;
}

int Heap::parent(int index) const
{
    // Returns the index of the parent of the element with given
    // index
    validateIndex(index);
    if (index == 0)
        return 0;
    return std::floor(static_cast<double>(index - 1)/ 2 );
}

int Heap::leftChild(int index) const
{
    // Returns the index of the left child of the element with given
    // index
    validateIndex(index);
    return 2*index + 1;
}

int Heap::rightChild(int index) const
{
    // Returns the index of the right child of the element with given
    // index
    validateIndex(index);
    return 2*index + 2;
}

void Heap::siftUp(int index)
{
    // Moves an element up until the heap property is satisfied
    validateIndex(index);
    while (index > 0 && m_array[index] > m_array[parent(index)])
    {
        std::swap(m_array[index], m_array[parent(index)]);
        index = parent(index);
    }
}

void Heap::siftDown(int index)
{
    // Moves an element down until the heap property is satisfied
    int maxIndex;
    int left;
    int right;

    while(index < m_size)
    {
        maxIndex = index;
        left = leftChild(index);
        right = rightChild(index);

        if (left <= m_size && m_array[left] > m_array[maxIndex])
            maxIndex = left;
        if (right <= m_size && m_array[right] > m_array[maxIndex])
            maxIndex = right;

        if (index != maxIndex)
            std::swap(m_array[maxIndex], m_array[index]);
        else if (index == maxIndex)
            break;

        index = maxIndex;
    }

}

void Heap::insert(int priority)
{
    // Insert an element with given priority into the heap
    if (isFull())
        throw full_heap_error();

    m_size++;
    m_array[m_size - 1] = priority;
    siftUp(m_size - 1);
}

void Heap::remove(int index)
{
    // Removes an element from the heap
    if (isEmpty())
        throw empty_heap_error();

    m_array[index] = std::numeric_limits<int>::max();
    siftUp(index);
    extractMax();
}

int Heap::extractMax()
{
    // Extract element with max priority from the heap
    if (m_size == 0)
        throw empty_heap_error();

    int max {m_array[0]};
    m_array[0] = m_array[m_size - 1];
    m_size--;
    siftDown(0);

    return max;
}

int Heap::getPriority(int index) const
{
    validateIndex(index);
    return m_array[index];
}

void Heap::validateIndex(int index) const
{
    // Check if the given index is valid
    if (index < 0 or index >= m_size)
        throw index_out_of_range_error();
}
