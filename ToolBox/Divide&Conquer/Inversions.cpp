//
// Created by daniel on 9/05/22.
//

#include "Inversions.h"

int mergeAndCount(std::vector<int>& array, int left, int midpoint, int right)
{
    // Merges the sorted arrays

    int numInversions {0};
    int leftSize {midpoint - left};
    int rightSize {right - midpoint};

    std::vector<int> leftArray (leftSize);
    std::vector<int> rightArray (rightSize);

    for (int ii {0}; ii < leftSize; ++ii)
        leftArray[ii] = array[left + ii];
    for (int ii {0}; ii < rightSize; ++ii)
        rightArray[ii] = array[midpoint + ii];

    int pointerLeft {0};
    int pointerRight {0};
    int index {left};

    while (pointerLeft < leftSize && pointerRight < rightSize)
    {
        if (leftArray[pointerLeft] <= rightArray[pointerRight])
        {
            array[index] = leftArray[pointerLeft];
            ++pointerLeft;
        }
        else
        {
            array[index] = rightArray[pointerRight];
            ++pointerRight;
            numInversions += leftSize - pointerLeft;
        }
        ++index;
    }

    while (pointerLeft < leftSize)
    {
        array[index] = leftArray[pointerLeft];
        ++pointerLeft;
        ++index;
    }

    while (pointerRight < rightSize)
    {
        array[index] = rightArray[pointerRight];
        ++pointerRight;
        ++index;
    }

    return numInversions;
}


long long NumberOfInversions(std::vector<int> &array, int left, int right)
{
    long long leftInversions {0};
    long long rightInversions {0};
    long long splitInversions {0};

    if (right - left <= 1)
        return 0;

    // Split the array into halves
    int midpoint {left + (right - left) / 2};
    leftInversions  = NumberOfInversions(array, left, midpoint);
    rightInversions = NumberOfInversions(array, midpoint, right);
    splitInversions = mergeAndCount(array, left, midpoint, right);

    return leftInversions + rightInversions + splitInversions;
}