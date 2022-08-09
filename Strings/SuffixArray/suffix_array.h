//
// Created by daniel on 6/07/22.
//

#ifndef ALGORITHMS_SUFFIX_ARRAY_H
#define ALGORITHMS_SUFFIX_ARRAY_H


#include <algorithm>
#include <numeric>
#include <utility>  // std::pair
#include <string>
#include <vector>
#include "count_sort.h"


std::vector<int> suffixArrayNaive(const std::string& text);

std::vector<int> getCharClasses(const std::string& text, const std::vector<int>& order);

std::vector<int> sortDoubled(const std::string& text,
                             int shiftSize,
                             const std::vector<int>& order,
                             const std::vector<int>& classNumbers);

std::vector<int> updateClasses(const std::vector<int>& newOrder,
                               const std::vector<int>& classNumbers,
                               int shiftSize);

std::vector<int> suffixArray(const std::string& text);

std::vector<int> invertSuffixArray(const std::vector<int>& suffixArray);

int suffixesLCP(const std::string& text,
                int suffixIndex_1,
                int suffixIndex_2,
                int prevLCP);

std::vector<int> lcpArray(const std::string& text, const std::vector<int>& suffixArray);

bool isPatternGreaterOrEqual(const std::string& text, const std::string& pattern, int suffix);

std::pair<int, int> patternMatchSuffixArray(const std::vector<int>& suffixArray,
                                            const std::string& text,
                                            const std::string& pattern);

#endif //ALGORITHMS_SUFFIX_ARRAY_H
