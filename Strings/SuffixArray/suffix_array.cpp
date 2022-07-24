//
// Created by daniel on 6/07/22.
//

#include "suffix_array.h"


std::vector<int> suffixArrayNaive(const std::string& text)
{
    // Returns the suffix array of the given text.
    // Naive implementation

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


std::vector<int> getCharClasses(const std::string& text, const std::vector<int> order)
{
    // Computes classNumber[i] which is the number of different cyclic shifts
    // of length L that are smaller than C_i. Where C_i is the partial cyclic
    // shift of length L starting at i.

    std::vector<int> classNumber(text.size(), 0);
    for (auto ii {1}; ii < order.size(); ++ii)
    {
        if (text[order[ii]] != text[order[ii - 1]])
            classNumber[order[ii]] = classNumber[order[ii - 1]] + 1;
        else
            classNumber[order[ii]] = classNumber[order[ii - 1]];
    }

    return classNumber;
}