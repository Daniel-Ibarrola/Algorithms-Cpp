//
// Created by daniel on 9/05/22.
//

#ifndef ALGORITHMS_MERGESORT_H
#define ALGORITHMS_MERGESORT_H

#include <vector>

template <typename T>
void mergeSort(std::vector<T>& arr, int left, int right);

template <typename T>
void merge(std::vector<T>& arr, int left, int midpoint, int right);

#endif //ALGORITHMS_MERGESORT_H
