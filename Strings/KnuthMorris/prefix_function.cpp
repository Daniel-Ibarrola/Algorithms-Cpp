//
// Created by daniel on 15/07/22.
//

#include "prefix_function.h"

std::vector<int> prefixFunction(const std::string& text)
{
    // Returns a vector with the length of the longest border of
    // the prefix text[0..i]
    std::vector<int> longestBorders(text.size(), 0);
    int border {0};

    for (auto ii {1}; ii < text.size(); ++ii)
    {
        while (border > 0 && text[ii] != text[border])
            border = longestBorders[border - 1];
        if (text[ii] == text[border])
            ++border;
        else
            border = 0;
        longestBorders[ii] = border;
    }

    return longestBorders;
}