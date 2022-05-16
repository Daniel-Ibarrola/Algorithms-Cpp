//
// Created by daniel on 10/05/22.
//

#include "editDistance.h"

int min(int num1, int num2, int num3)
{
    // Returns the minimum of three numbers
    int min_num {std::min(num1, num2)};
    return std::min(min_num, num3);
}

int minEditDistance(const std::string &str1, const std::string &str2)
{
    // Returns minimum edit distance. This is the number of operations
    // (deletion, insertion, replacement) to transform one string into
    // another
    int lenStr_1 {static_cast<int>(str1.length())};
    int lenStr_2 {static_cast<int>(str2.length())};

    // Construct a table named distances to store the edit distances
    std::vector<int> row(lenStr_2 + 1, 0);
    std::vector<std::vector<int>> distances(lenStr_1 + 1, row);

    // When str2 has length 0, distance is equal to length of str2
    for (int ii {0}; ii < lenStr_1 + 1; ++ii)
        distances[ii][0] = ii;

    // When str1 has length 0, distance is equal to length of str1
    for (int jj {0}; jj < lenStr_2 + 1; ++jj)
        distances[0][jj] = jj;

    // Fill the table
    for (int ii {1}; ii < lenStr_1 + 1; ++ii)
    {
        for (int jj {1}; jj < lenStr_2 + 1; ++jj)
        {
            // Last characters match
            if (str1[ii - 1] == str2[jj - 1])
                distances[ii][jj] = distances[ii - 1][jj - 1];
                // Take the minimum of inserting, deleting and replacing
            else
                distances[ii][jj] =  1 + min(distances[ii - 1][ jj - 1], // replace
                                             distances[ii - 1][jj], // delete
                                             distances[ii][jj - 1]); // insert

        }
    }
    return distances[lenStr_1][lenStr_2];
}