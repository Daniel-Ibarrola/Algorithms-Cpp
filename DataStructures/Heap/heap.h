//
// Created by daniel on 21/05/22.
//

#ifndef ALGORITHMS_HEAP_H
#define ALGORITHMS_HEAP_H

#include <iostream>
#include <cmath>
#include <limits>

class index_out_of_range_error: public std::exception
{
    const char* what() const noexcept override
    {
        return "Index out of range";
    }
};

class full_heap_error: public std::exception
{
    const char* what() const noexcept override
    {
        return "Heap is full";
    }
};

class empty_heap_error: public std::exception
{
    const char* what() const noexcept override
    {
        return "Heap is empty";
    }
};


class Heap
{
    // Binary Heap data structure class
private:
    int* m_array;
    int m_maxSize;
    int m_size;

    void validateIndex(int index) const;

public:

    explicit Heap(int maxSize)
    {
        m_array = new int[maxSize];
        m_maxSize = maxSize;
        m_size = 0;
    }

    Heap(int* array, int maxSize, int size)
     : m_array(array), m_maxSize(maxSize), m_size(size)
    {

    }

    ~Heap()
    {
        delete[] m_array;
    }

    int maxSize() const {return m_maxSize;}

    int size() const {return m_size;}

    bool isEmpty() const;

    bool isFull() const;

    int getPriority(int index) const;

    int parent(int index) const;

    int leftChild(int index) const;

    int rightChild(int index) const;

    void siftUp(int index);

    void siftDown(int index);

    void insert(int priority);

    int extractMax();

    void remove(int index);
};

#endif //ALGORITHMS_HEAP_H
