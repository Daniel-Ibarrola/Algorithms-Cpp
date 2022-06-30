//
// Created by daniel on 29/06/22.
//

#include "burrows_wheeler.h"

std::vector<std::string> BurrowsWheeler::matrix() const
{
    // Returns the Burrows-Wheeler matrix of the text

    std::size_t size {m_text.size()};
    std::vector<std::string> bwMatrix(size);
    // The matrix consists of oll the cyclic rotations of the text
    // sorted in ascending order. The '$' count as the lowest char

    bwMatrix[0] = m_text;
    for (auto ii {1}; ii < size; ++ii)
    {
        // The next row of the matrix always starts with the
        // last character of the previous row, followed by the
        // string of the previous row from start to end - 1
        std::string rotation {bwMatrix[ii - 1][size - 1]};
        for (auto jj {0}; jj < size - 1; ++jj)
            rotation += bwMatrix[ii - 1][jj];

        assert(rotation.size() == size && "rotation doesn't have the size of the text");
        bwMatrix[ii] = rotation;
    }

    // Now we sort the matrix
    std::sort(bwMatrix.begin(), bwMatrix.end());
    return bwMatrix;
}


std::string BurrowsWheeler::getTransform() const
{
    // Returns the Burrows-Wheeler transform of the text
    std::vector<std::string> bwMatrix {matrix()};
    std::size_t size {bwMatrix.size()};
    std::string transform;
    for (auto ii {0}; ii < size; ++ii)
        transform += bwMatrix[ii][size - 1];

    return transform;
}


std::string InverseBW::inverse() const
{
    // Get the inverse of the Burrows-Wheeler transform

    std::string sortedTransform;
}