//
// Created by daniel on 6/07/22.
//

#include "suffix_array.h"


std::vector<int> suffixArray(const std::string& text)
{
    // Returns the suffix array of the given text

    std::vector<int> positions(text.size());
    std::iota(positions.begin(), positions.end(), 0);

    std::vector<std::string> suffixes(text.size());
    for(auto start {0}; start < text.size(); ++start)
        suffixes[start] = text.substr(start, text.size() - start - 1);


    auto compare {
        [suffixes](int left, int right) -> bool
        {
            return suffixes[left] < suffixes[right];
        }
    };
    std::sort(positions.begin(), positions.end(), compare);
    return positions;
}
