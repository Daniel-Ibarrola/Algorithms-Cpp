//
// Created by daniel on 9/05/22.
//

#include "Quicksort.h"


std::array<int, 2> partition3(std::vector<int> &array, int low, int high)
{
    int pivot {array[low]};
    int left {low};
    int right {low};
    int upper {high};

    while (right <= upper)
    {
        if (array[right] < pivot)
        {
            std::swap(array[left], array[right]);
            left++;
            right++;
        }
        else if (array[right] > pivot)
        {
            std::swap(array[right], array[upper]);
            upper--;
        }
        else
            right++;
    }
    return std::array<int, 2> {left, right};
}

int partition2(std::vector<int> &array, int left, int right)
{
    int pivot {array[left]};
    int jj {left};
    for (int ii {left + 1}; ii <= right; ++ii)
    {
        if (array[ii] <= pivot)
        {
            jj++;
            std::swap(array[ii], array[jj]);
        }
    }
    std::swap(array[left], array[jj]);
    return jj;
}

void randomizedQuickSort(std::vector<int> &array, int left, int right)
{
    if (left >= right)
        return;

    int randomIndex {left + rand() % (right - left + 1)};
    std::swap(array[left], array[randomIndex]);

    // int endpoint {partition2(array, left, right)};
    // randomizedQuickSort(array, left, endpoint - 1);
    // randomizedQuickSort(array, endpoint + 1, right);

    std::array<int, 2> endpoints {partition3(array, left, right)};
    randomizedQuickSort(array, left, endpoints[0] - 1);
    randomizedQuickSort(array, endpoints[1], right);
}