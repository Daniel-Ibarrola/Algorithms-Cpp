//
// Created by daniel on 29/06/22.
//

#ifndef ALGORITHMS_BURROWS_WHEELER_H
#define ALGORITHMS_BURROWS_WHEELER_H

#include <algorithm>
#include <cassert>
#include <numeric>
#include <string>
#include <utility>
#include <vector>


class BurrowsWheeler
{
    // Class to construct the Burrows-Wheeler transform of a string

private:
    std::string m_text;

public:

    explicit BurrowsWheeler(std::string text)
        : m_text {std::move(text)}
    {

    }

    std::vector<std::string> matrix() const;
    std::string getTransform() const;
};

#endif //ALGORITHMS_BURROWS_WHEELER_H

class InverseBW
{
    // Class to obtain the inverse of the Burrows-Wheeler transform
private:
    std::string m_transform;

public:

    explicit InverseBW(std::string transform)
        : m_transform {std::move(transform)}
    {

    }

    std::string inverse() const;

    std::vector<int> sortedPositions() const;
};