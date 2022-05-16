//
// Created by daniel on 3/05/22.
//

#include "BinarySearch.h"

int binarySearch(const std::vector<int>& array, int key)
{
    // Search a key in an array using binary search
    int low {0};
    int high {static_cast<int>(array.size()) - 1};
    int midpoint {0};

    while (low <= high)
    {
        midpoint = low + (high - low) / 2;

        if (array[midpoint] == key)
            return midpoint;
        else if (array[midpoint] > key)
            high = midpoint - 1;
        else
            low = midpoint + 1;
    }

    return -1;
}

int linearSearch(const std::vector<int>& array, int key)
{
    // Search a key in an array using linear search
    for (auto index {0}; index < array.size(); ++index)
    {
        if (array[index] == key) return index;
    }
    return -1;
}

int binarySearchWithDuplicates(const std::vector<int>& array, int key)
{
    // Search a key in an array using binary search
    int low {0};
    int high {static_cast<int>(array.size()) - 1};
    int midpoint {0};

    while (low <= high)
    {
        midpoint = low + (high - low) / 2;
        if (array[midpoint] == key)
        {
            // If the key is found search to the left of it to find the first occurrence
            int indexFirst {midpoint};
            while(true)
            {
                if(array[indexFirst - 1] == key)
                    indexFirst -= 1;
                else
                    break;
            }
            return indexFirst;
        }
        else if (array[midpoint] > key)
            high = midpoint - 1;
        else
            low = midpoint + 1;
    }

    return -1;
}