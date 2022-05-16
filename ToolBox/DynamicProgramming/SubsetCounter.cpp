//
// Created by daniel on 10/05/22.
//

#include "SubsetCounter.h"

int SubsetCounter::count(int sum, char method)
{
    // Count the number of subsets in a set such that the sum of their elements
    // equals the given sum.
    // Method can be 'D' for dynamic programing or 'R' for recursive.

    if (m_set.empty())
        return 0;

    if (method == 'D')
        return countDp(sum);
    else if (method == 'R')
        return countRecursive(sum, static_cast<int>(m_set.size()) - 1);
    else
        throw wrong_method_error();

}

int SubsetCounter::countDp(int sum) {
    // Count the number of subsets in a set such that the sum of their elements
    // equals the given sum using a dynamic programming algorithm.

    // Create a dynamic programming table
    int numItems{static_cast<int>(m_set.size())};
    std::vector<int> row(sum + 1, 0);
    std::vector<std::vector<int>> table(numItems + 1, row);

    // if the sum is zero there is always one subset
    for (int item{0}; item < numItems + 1; ++item)
        table[item][0] = 1;

    // Fill the table
    for (int currentItem {1}; currentItem < numItems + 1; ++currentItem)
    {
        for (int currentSum {1}; currentSum < sum + 1; ++currentSum)
        {
            // If it's value is greater than the current sum exclude the item
            if (m_set[currentItem - 1] > currentSum)
                table[currentItem][currentSum] = table[currentItem - 1][currentSum];
            else
                table[currentItem][currentSum] = table[currentItem - 1][currentSum]
                        + table[currentItem - 1][currentSum - m_set[currentItem - 1]];
        }
    }

    return table[numItems][sum];
}

int SubsetCounter::countRecursive(int sum, int item)
{
    // Count the number of subsets in a set such that the sum of their elements
    // equals the given sum using a recursive algorithm.

    // Base cases
    if (sum == 0)
        return 1;
    if (item < 0)
        return 0;

    int counter {0};
    // Skip item if it's value is greater than the current sum
    if (m_set[item] > sum)
        counter += countRecursive(sum, item - 1);
    else
        // Include or exclude the item
        counter += countRecursive(sum, item - 1)
                + countRecursive(sum - m_set[item], item - 1);

    return counter;
}

int SubsetCounter::setsWithDifference(int diff)
{
    // Counts the number of subsets with a given difference
    if (m_set.empty())
        return 0;

    int set_sum {setSum()};
    int targetSum {(diff + set_sum) / 2};

    return countDp(targetSum);
}

int SubsetCounter::setSum()
{
    int sum {0};
    for (auto element : m_set)
        sum += element;
    return sum;
}

