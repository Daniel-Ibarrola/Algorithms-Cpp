//
// Created by daniel on 10/05/22.
//

#ifndef ALGORITHMS_LCS_H
#define ALGORITHMS_LCS_H

#include <iostream>
#include <vector>
#include <string>

using sequence = std::vector<int>;

std::string LCS(const std::string& str1, const std::string& str2);

int LCSLength(const sequence &sequence_1, const sequence &sequence_2);

#endif //ALGORITHMS_LCS_H
