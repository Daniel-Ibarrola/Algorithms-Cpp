//
// Created by daniel on 22/07/22.
//

#include "count_sort.h"


std::vector<int> countSort(const std::vector<int>& array)
{
    // Sorts the elements of an array by counting the number of
    // occurrences of each unique element in the array

    // Find the max element of the array and create a count array of size
    // max + 1
    int max {*std::max_element(array.begin(), array.end())};
    std::vector<int> count(max, 0);

    // Find the number of occurrences of each element
    for (auto ii {0}; ii < count.size(); ++ii)
        count[array[ii]]++;
    // Compute the cumulative sum but store it in the count array
    for (auto jj {1}; jj < count.size(); ++jj)
        count[jj] += count[jj - 1];



    return {};
}

std::vector<int> sortCharacters(const std::string& string)
{
    // Sorts the characters of a string by counting the number of
    // occurrences of each unique character in the string
    return {};
}