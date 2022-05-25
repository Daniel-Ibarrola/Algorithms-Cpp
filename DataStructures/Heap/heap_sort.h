//
// Created by daniel on 23/05/22.
//

#ifndef ALGORITHMS_HEAP_SORT_H
#define ALGORITHMS_HEAP_SORT_H

#include <array>
#include <cmath>

int leftChild(int index)
{
    // Returns the index of the left child of the element with given
    // index
    return 2*index + 1;
}

int rightChild(int index)
{
    // Returns the index of the right child of the element with given
    // index
    return 2*index + 2;
}

template <typename T, std::size_t size>
void siftDown(std::array<T, size>& array, int index, int length)
{
    // Move the element with given index down until the heap property
    // is satisfied
    int maxIndex;
    int left;
    int right;

    while(index < length)
    {
        maxIndex = index;
        left = leftChild(index);
        right = rightChild(index);

        if (left <= length && array[left] > array[maxIndex])
            maxIndex = left;
        if (right <= length && array[right] > array[maxIndex])
            maxIndex = right;

        if (index != maxIndex)
            std::swap(array[maxIndex], array[index]);
        else
            break;

        index = maxIndex;
    }
}

template <typename T, std::size_t size>
void buildHeap(std::array<T, size>& array)
{
    // Transforms the array into a heap
    int halfSize {static_cast<int>(std::floor(array.size() / 2.0))};
    int length {static_cast<int>(array.size()) - 1};

    for (int ii {halfSize}; ii >= 0; --ii)
        siftDown(array, ii, length);
}

template <typename T, std::size_t size>
void heapSort(std::array<T, size>& array)
{
    // Sort an array using the heap sort algorithm
    buildHeap(array);
    int length {static_cast<int>(array.size()) - 1};
    int currentLen {length};

    for (auto ii {length}; ii >= 0; --ii)
    {
        std::swap(array[0], array[ii]);
        currentLen--;
        siftDown(array, 0, currentLen);
    }

}

#endif //ALGORITHMS_HEAP_SORT_H
