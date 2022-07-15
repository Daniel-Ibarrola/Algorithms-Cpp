//
// Created by daniel on 15/07/22.
//

#include "pattern_matching.h"

std::vector<int> findAllOccurrences(const std::string& pattern, const std::string& text)
{
    // Returns a vector with all occurrences of the pattern in the text

    if (pattern.empty() || text.empty())
        return {};

    std::vector<int> occurrences;
    std::string concatenation = pattern + '$' + text;
    std::vector<int> borders {prefixFunction(concatenation)};

    for (auto ii {pattern.size() + 1}; ii < concatenation.size(); ++ii)
    {
        if (borders[ii] == pattern.size())
            occurrences.push_back(static_cast<int>(ii - 2 * pattern.size()));
    }

    return occurrences;
}