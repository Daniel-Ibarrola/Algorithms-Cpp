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
    std::vector<int> count(max + 1, 0);

    // Find the number of occurrences of each element
    for (auto ii {0}; ii < array.size(); ++ii)
        count[array[ii]]++;
    // Compute the cumulative sum and store it in the count array
    // This will give us the starting position of each item
    for (auto jj {1}; jj < count.size(); ++jj)
        count[jj] += count[jj - 1];

    // Fill a new array with the elements in sorted order
    std::vector<int> sortedArray(array.size());
    int size {static_cast<int>(sortedArray.size())};
    for (int ii {size - 1}; ii >= 0; --ii)
    {
        // Decrease the position of the element by one, because array is 0-based indexing
        count[array[ii]]--;
        sortedArray[count[array[ii]]] = array[ii];
    }

    return sortedArray;
}

std::vector<int> sortCharacters(const std::string& string)
{
    // Sorts the characters of a string by counting the number of
    // occurrences of each unique character in the string.
    // Returns a vector with the indices of the sorted characters

    std::vector<int> count(128, 0);  // 128 for the number of ASCII characters

    // Compute number of occurrences of each char
    for (char jj : string)
        count[jj]++;
    // Get the starting positions of each character in the sorted string
    for (auto jj {1}; jj < count.size(); ++jj)
        count[jj] += count[jj - 1];

    std::vector<int> order(string.size());
    int size {static_cast<int>(order.size())};
    for (int ii {size - 1}; ii >= 0; --ii)
    {
        // Decrease the position of the element by one, because array is 0-based indexing
        count[string[ii]]--;
        order[count[string[ii]]] = ii;
    }

    return order;
}