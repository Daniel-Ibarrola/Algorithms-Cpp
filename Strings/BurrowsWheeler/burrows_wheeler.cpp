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


std::array<std::string, 2> BurrowsWheeler::firstAndLastColumn() const
{
    // Returns an array where the first entry is the first column of the
    // BW matrix and the second entry is the last column.
    // The columns contain the indices of the characters in the text

    std::array<std::string, 2> columns {
        std::string (m_text.size(), char(0)),
        std::string (m_text.size(), char(0)),
    };

    std::vector<std::string> matrixBW {matrix()};
    for (auto ii {0}; ii < m_text.size(); ++ii)
        columns[0][ii] = matrixBW[ii][0];

    for (auto ii {0}; ii < m_text.size(); ++ii)
        columns[1][ii] = matrixBW[ii][m_text.size() - 1];

    return columns;
}


std::vector<int> InverseBW::sortedPositions() const
{
    //  Returns an array with the indices that each character
    //  would have in the sorted string

    // Create a vector starting from 0 and ending in m_transform.size() - 1
    std::vector<int> indices(m_transform.size());
    std::iota(indices.begin(), indices.end(), 0);
    // Get the indices of the sorted string
    std::sort(indices.begin(), indices.end(),
              [this] (int left, int right) -> bool {
                  // sort indices according to corresponding string element
                  return m_transform[left] < m_transform[right];

    });
    // Sort them again to get the indices that each character in the
    // original string has in the sorted string
    std::sort(indices.begin(), indices.end(),
              [indices] (int left, int right) -> bool {
                  return indices[left] < indices[right];
              });
    return indices;
}


std::string InverseBW::inverse() const
{
    // Get the inverse of the Burrows-Wheeler transform

    std::string inverse(m_transform.size(), char(0));
    std::vector<int> sortedIndices {sortedPositions()};
    int nextIndex {0};
    // The transform will give us the original string in reverse order
    // so, to avoid reversing the string at the end we start filling from
    // the second to last index. We skip the last index because it corresponds
    // to the $ sign.
    for (int ii {static_cast<int>(inverse.size()) - 2}; ii >= 0; --ii)
    {
        inverse[ii] = m_transform[nextIndex];
        nextIndex = sortedIndices[nextIndex];
    }
    inverse[inverse.size() - 1] = '$';
    return inverse;
}