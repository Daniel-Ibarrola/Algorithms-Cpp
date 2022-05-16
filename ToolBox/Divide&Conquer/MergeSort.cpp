//
// Created by daniel on 9/05/22.
//

#include "MergeSort.h"

template <typename T>
void mergeSort(std::vector<T>& arr, int left, int right)
{
    // Sorts a vector by using the merge sort algorithm

    // Base case
    if (left > right)
        return;
    int midpoint {(left + right) / 2};
    // Split the array into halves and merge
    mergeSort(arr, left, midpoint);
    mergeSort(arr, midpoint + 1, right);
    merge(arr, left, midpoint, right);
}

template <typename T>
void merge(std::vector<T>& arr, int left, int midpoint, int right)
{
    // Merge procedure of the merge sort algorithm.

    // Create copies of the subarrays sub_1 <- arr[left...midpoint] and
    // sub_2 <- arr[midpoint+1...right]
    int size_1 {midpoint - left + 1};
    int size_2 {right -  midpoint};

    std::vector<T> sub_1(size_1);
    std::vector<T> sub_2(size_2);

    for (int ii {0}; ii < size_1; ++ii)
        sub_1[ii] = arr[left + ii];
    for (int jj {0}; jj < size_2; ++jj)
        sub_2[jj] = arr[midpoint + 1 + jj];

    // Maintain index of each of the arrays
    int ii {0};  // index of sub_1
    int jj {0};  // index of sub_2
    int kk {left}; // index of arr

    // Combine the arrays
    // Compare the elements of each subarray and fill the main array
    // until one of the subarrays runs out of elements
    while (ii < size_1 && jj < size_2)
    {
        if (sub_1[ii] <= sub_2[jj])
        {
            arr[kk] = sub_1[ii];
            ++ii;
        }
        else
        {
            arr[kk] = sub_2[jj];
            ++jj;
        }
        ++kk;
    }

    // Fill in with the remaining elements of the subarrays
    while (ii < size_1)
    {
        arr[kk] = sub_1[ii];
        ++ii;
        ++kk;
    }
    while(jj < size_2)
    {
        arr[kk] = sub_2[jj];
        ++jj;
        ++kk;
    }

}