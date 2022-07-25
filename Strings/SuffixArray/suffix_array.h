//
// Created by daniel on 6/07/22.
//

#ifndef ALGORITHMS_SUFFIX_ARRAY_H
#define ALGORITHMS_SUFFIX_ARRAY_H


#include <algorithm>
#include <numeric>
#include <string>
#include <vector>


std::vector<int> suffixArrayNaive(const std::string& text);

std::vector<int> getCharClasses(const std::string& text, const std::vector<int>& order);

std::vector<int> sortDoubled(const std::string& text,
                             int shiftSize,
                             const std::vector<int>& order,
                             const std::vector<int>& classNumbers);

#endif //ALGORITHMS_SUFFIX_ARRAY_H
