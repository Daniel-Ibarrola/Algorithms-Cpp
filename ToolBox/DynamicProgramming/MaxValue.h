//
// Created by daniel on 10/05/22.
//

#ifndef ALGORITHMS_MAXVALUE_H
#define ALGORITHMS_MAXVALUE_H

#endif //ALGORITHMS_MAXVALUE_H


#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using table = std::vector<std::vector<long long>>;

struct tuple
{
    long long min {};
    long long max {};
};

long long evaluate(long long val_1, long long val_2, char oper);

long long maxElement(std::array<long long, 5> arr);

long long minElement(std::array<long long, 5> arr);

tuple minAndMax(int ii, int jj, const table& maxVals,
                const table& minVals, const std::vector<char>& operators);

bool isOperator(char character);

long long maxValue(const std::string& expression);