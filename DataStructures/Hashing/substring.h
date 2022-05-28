//
// Created by daniel on 27/05/22.
//

#ifndef ALGORITHMS_SUBSTRING_H
#define ALGORITHMS_SUBSTRING_H

#include <string>
#include <vector>

long long polyHash(const std::string& str, long long prime, long long multiplier);

std::vector<long long> precomputeHashes(const std::string& text, int patternSize,
                                                 long long prime, long long multiplier);

std::vector<int> searchSubstring(const std::string& text, const std::string& pattern);

#endif //ALGORITHMS_SUBSTRING_H
