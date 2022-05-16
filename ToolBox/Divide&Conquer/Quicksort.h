//
// Created by daniel on 9/05/22.
//

#ifndef ALGORITHMS_QUICKSORT_H
#define ALGORITHMS_QUICKSORT_H

#include <array>
#include <vector>

std::array<int, 2> partition3(std::vector<int> &array, int low, int high);

int partition2(std::vector<int> &array, int left, int right);

void randomizedQuickSort(std::vector<int> &array, int left, int right);

#endif //ALGORITHMS_QUICKSORT_H
