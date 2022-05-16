//
// Created by daniel on 10/05/22.
//

#include "MaxValue.h"


long long evaluate(long long val_1, long long val_2, char oper)
{
    // Evaluates an expression

    long long result {0};
    switch (oper)
    {
        case '*': result = val_1 * val_2; break;
        case '+': result = val_1 + val_2; break;
        case '-': result = val_1 - val_2; break;
        default: break;
    }

    return result;
}

long long maxElement(std::array<long long, 5> arr)
{
    // Helper function to find the max value of an array
    long long max {std::numeric_limits<long long>::min()};
    for (auto element : arr)
        max = std::max(max, element);
    return max;
}

long long minElement(std::array<long long, 5> arr)
{
    // Helper function to find the min value of an array
    long long min {std::numeric_limits<long long>::max()};
    for (auto element : arr)
        min = std::min(min, element);
    return min;
}

tuple minAndMax(int ii, int jj, const table& maxVals,
                const table& minVals, const std::vector<char>& operators)
{
    // Returns the minimum and max value of a subexpression

    std::array<long long, 5> results {};
    long long min {std::numeric_limits<long long>::max()};
    long long max {std::numeric_limits<long long>::min()};

    for (int kk {ii}; kk < jj; ++kk)
    {
        results[0] = evaluate(maxVals[ii][kk], maxVals[kk + 1][jj], operators[kk]);
        results[1] = evaluate(maxVals[ii][kk], minVals[kk + 1][jj], operators[kk]);
        results[2] = evaluate(minVals[ii][kk], maxVals[kk + 1][jj], operators[kk]);
        results[3] = evaluate(minVals[ii][kk], minVals[kk + 1][jj], operators[kk]);

        results[4] = max;
        max = maxElement(results);

        results[4] = min;
        min = minElement(results);
    }

    tuple vals {min, max};
    return vals;
}

bool isOperator(char character)
{
    // Check whether a character corresponds to an operator
    if (character == '+' || character == '-'
        || character == '*')
        return true;

    return false;
}

long long maxValue(const std::string& expression)
{
    // Returns the max value of an arithmetic expression.

    // Create a vector to store the numbers and another to store operators
    std::vector<long long> sequence {};
    std::vector<char> operators {};

    for (auto ii {0}; ii < expression.length(); ++ii)
    {
        if (isOperator(expression[ii]))
            operators.push_back(expression[ii]);
        else
            sequence.push_back(static_cast<long long>(expression[ii] - '0'));
    }

    // Create two tables, one to store the max value of each subexpression and
    // another to store the min value
    std::vector<long long> row (sequence.size());
    table minVals (sequence.size(), row);
    table maxVals (sequence.size(), row);

    // Base Case. Subexpression is only a single value
    for (auto ii {0}; ii < minVals.size(); ++ii)
    {
        minVals[ii][ii] = sequence[ii];
        maxVals[ii][ii] = sequence[ii];
    }

    // Fill the table in diagonal order. ii denotes the row index and jj
    // the column index
    int nn {static_cast<int>(maxVals.size())};
    int jj;
    tuple vals;
    for (int ss {1}; ss < nn; ++ss)
    {
        for (int ii {0}; ii < nn - ss; ++ii)
        {
            jj = ii + ss;
            vals = minAndMax(ii, jj, maxVals, minVals, operators);
            maxVals[ii][jj] = vals.max;
            minVals[ii][jj] = vals.min;
        }
    }

    return std::max(maxVals[0][maxVals.size() - 1],
                    minVals[0][minVals.size() - 1]);
}
