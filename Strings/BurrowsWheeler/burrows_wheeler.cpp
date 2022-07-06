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


int BurrowsWheeler::patternCount(const std::string &pattern) const
{
    // Count the number of occurrences of the given pattern in the text

    if (pattern.empty())
        return 0;

    std::array<std::string, 2> columns {firstAndLastColumn()};
    std::vector<int> lastToFirst {InverseBW::sortedPositions(columns[1])};

    int top {0};
    int bottom {static_cast<int>(m_text.size()) - 1};
    int currentChar {static_cast<int>(pattern.size()) - 1};  // Current character of the pattern

    int topIndex {-1};
    int bottomIndex {-1};
    bool symbolInColumn {false};

    while (top <= bottom)
    {
        if (currentChar >= 0)
        {
            // Check if last column from top to bottom contains current character
            // and find the first and last position where this character occurs
            for (auto ii {top}; ii <= bottom; ++ii)
            {
                // Update top index and bottom index, but continue searching in
                // case there is another character closer to the bottom
                if (columns[1][ii] == pattern[currentChar] && topIndex == -1)
                {
                    topIndex = ii;
                    bottomIndex = ii;
                    symbolInColumn = true;
                }
                else if (columns[1][ii] == pattern[currentChar])
                    bottomIndex = ii;
            }
            if (symbolInColumn)
            {
                top = lastToFirst[topIndex];
                bottom = lastToFirst[bottomIndex];
            }
            else
                return 0;

            symbolInColumn = false;
            topIndex = -1;
            bottomIndex = -1;
            currentChar--;
        }
        else
            return bottom - top + 1;
    }

    return 0;
}


std::map<char, std::vector<int>> BurrowsWheeler::countMap(const std::string &lastColumn)
{
    // Returns the count map of the last column

    std::map<char, std::vector<int>> count;

    // Get all different symbols
    for (auto symbol : lastColumn)
        count.emplace(symbol, std::vector<int>(lastColumn.size() + 1, 0));

    // Now store the count
    for (auto ii {0}; ii < lastColumn.size(); ++ii)
    {
        for (auto & itr : count)
        {
            if (itr.first == lastColumn[ii])
                itr.second[ii + 1] = itr.second[ii] + 1;
            else
                itr.second[ii + 1] = itr.second[ii];
        }
    }

    return count;
}


std::map<char, int> BurrowsWheeler::firstOccurrence(const std::string &firstColumn)
{
    // Returns the first occurrence map of the first column
    std::map<char, int> occurrences;

    for (auto ii {0}; ii < firstColumn.size(); ++ii)
        occurrences.emplace(firstColumn[ii], ii);

    return occurrences;
}


int BurrowsWheeler::betterPatternCount(const std::string &pattern) const
{
    // Count the number of occurrences of the given pattern in the text
    // using a faster algorithm

    if(pattern.empty())
        return 0;

    int top{0};
    int bottom {static_cast<int>(m_text.size() - 1)};
    int currentChar {static_cast<int>(pattern.size() - 1)};

    std::array<std::string, 2> columns {firstAndLastColumn()};
    std::map<char, int> firstOccur {firstOccurrence(columns[0])};
    std::map<char, std::vector<int>> count {countMap(columns[1])};

    while (top <= bottom)
    {
        if (currentChar >= 0)
        {
            char symbol {pattern[currentChar]};
            // Check if the symbol exists in the map
            auto itr {firstOccur.find(symbol)};
            if (itr != firstOccur.end())
            {
                int occurrence {itr->second};
                top = occurrence + count[symbol][top];
                bottom = occurrence + count[symbol][bottom + 1] - 1;
                currentChar--;
            }
            else
                return 0;
        }
        else
            return bottom - top + 1;
    }

    return 0;
}


// Inverse Burrows Wheelers //
// ------------------------- //

std::vector<int> InverseBW::sortedPositions(const std::string& transform)
{
    //  Returns an array with the indices that each character
    //  would have in the sorted string

    // Create a vector starting from 0 and ending in m_transform.size() - 1
    std::vector<int> indices(transform.size());
    std::iota(indices.begin(), indices.end(), 0);
    // Get the indices of the sorted string
    std::sort(indices.begin(), indices.end(),
              [transform] (int left, int right) -> bool {
                  // sort indices according to corresponding string element
                  return transform[left] < transform[right];

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
    std::vector<int> sortedIndices {sortedPositions(m_transform)};
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


