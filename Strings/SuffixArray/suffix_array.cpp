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


std::vector<int> getCharClasses(const std::string& text, const std::vector<int>& order)
{
    // Computes classNumber[i] which is the number of different cyclic shifts
    // of length L that are smaller than C_i. Where C_i is the partial cyclic
    // shift of length L starting at index i.

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


std::vector<int> sortDoubled(const std::string& text,
                             int shiftSize,
                             const std::vector<int>& order,
                             const std::vector<int>& classNumbers)
{
    // Sorts the cyclic shifts of length shiftSize + 2.
    // Returns a vector with the positions of the doubled cyclic shifts

    // We use count sort, but we sort by classes instead of characters
    std::vector<int> count(text.size());
    std::vector<int> newOrder(text.size());

    for (auto ii {0}; ii < classNumbers.size(); ++ii)
        count[classNumbers[ii]]++;
    for (auto jj {1}; jj < count.size(); ++jj)
        count[jj] += count[jj - 1];

    int size {static_cast<int>(text.size())};
    for (int ii {size - 1}; ii >= 0; --ii)
    {
        // Get the start of the doubled cyclic shift. Add the length if the string
        // to avoid negative numbers and take its modulo to get a number in the range of the string size
        int start {(order[ii] - shiftSize + size) % size};
        int classNum {classNumbers[start]};
        count[classNum]--;
        newOrder[count[classNum]] = start;
    }

    return newOrder;
}


std::vector<int> updateClasses(const std::vector<int>& newOrder,
                               const std::vector<int>& classNumbers,
                               int shiftSize)
{
    // Updates the equivalence classes of the doubled cyclic shifts

    int textSize {static_cast<int>(newOrder.size())};
    std::vector<int> newClass(textSize);
    newClass[newOrder[0]] = 0;

    for (int ii {1}; ii < textSize; ++ii)
    {
        // Get the class number of the first element in the pair
        int current {newOrder[ii]};
        int prev {newOrder[ii - 1]};
        // Now the class of the second element
        int mid {(current + shiftSize) % textSize};
        int midPrev {(prev + shiftSize) % textSize};
        // If any of the classes in the pair are different we update the class number
        if (classNumbers[current] != classNumbers[prev] ||
            classNumbers[mid] != classNumbers[midPrev]
        )
            newClass[current] = newClass[prev] + 1;
        else
            newClass[current] = newClass[prev];

    }

    return newClass;
}


std::vector<int> suffixArray(const std::string& text)
{
    // Returns the suffix array of the given text. Works in O(|text|log|text| + |alphabet|)
    std::vector<int> order {sortCharacters(text)};
    std::vector<int> classNumbers {getCharClasses(text, order)};
    int shiftSize {1};

    while (shiftSize < static_cast<int>(text.size()))
    {
        order = sortDoubled(text, shiftSize, order, classNumbers);
        classNumbers = updateClasses(order, classNumbers, shiftSize);
        shiftSize *= 2;
    }

    return order;
}


std::vector<int> invertSuffixArray(const std::vector<int>& suffixArray)
{
    // Returns an array that for each suffix starting in position i of the string
    // indicates its position in the suffix array
    std::vector<int> inverseSuffixArray(suffixArray.size());

    for (auto ii {0}; ii < suffixArray.size(); ++ii)
        inverseSuffixArray[suffixArray[ii]] = ii;

    return inverseSuffixArray;
}


int suffixesLCP(const std::string& text, int suffixIndex_1,
                int suffixIndex_2, int prevLCP)
{
    // Returns the LCP value between two suffixes.

    // Take max with zero to allow negative numbers
    int lcp {std::max(prevLCP, 0)};
    int size {static_cast<int>(text.size())};

    // Compare the suffixes starting from the lcp value
    while (suffixIndex_1  + lcp < size && suffixIndex_2 + lcp < size)
    {
        if (text[suffixIndex_1 + lcp] != text[suffixIndex_2 + lcp])
            break;
        lcp++;
    }

    return lcp;
}


std::vector<int> lcpArray(const std::string& text, const std::vector<int>& suffixArray)
{
    // Returns the longest common prefix (lcp) array of the text.
    // This is an array such that for each i lcp[i] = LCP(A[i], A[i + 1])
    // where A denotes the suffix array and LCP is a function that returns the length
    // of the longest common prefix between two strings.
    std::vector<int> lcpArray(text.size() - 1);
    std::vector<int> positionInSuffixArray {invertSuffixArray(suffixArray)};
    int size {static_cast<int>(text.size())};
    int suffix {suffixArray[0]};
    int lcp {0};

    for (auto ii {0}; ii < size; ++ii)
    {
        int suffixArrayIndex {positionInSuffixArray[suffix]};
        if (suffixArrayIndex == lcpArray.size())
        {
            // Skip the last suffix in the suffix array as it's the last element and
            // cannot be compared with another suffix
            lcp = 0;
            suffix = (suffix + 1) % size;
            continue;
        }
        int nextSuffix {suffixArray[suffixArrayIndex + 1]};
        lcp = suffixesLCP(text, suffix, nextSuffix, lcp - 1);
        lcpArray[suffixArrayIndex] = lcp;

        suffix = (suffix + 1) % size;
    }
    return lcpArray;
}


bool isSuffixGreater(const std::string& text, const std::string& pattern, int suffix)
{
    // Check if a suffix is greater than the pattern

    std::size_t ii {0};
    std::size_t jj {static_cast<std::size_t>(suffix)};
    while (ii < pattern.size() && jj < text.size())
    {
        if (text[jj] != pattern[ii])
        {
            if (text[jj] > pattern[ii])
                return true;
            else
                return false;
        }
        ++ii;
        ++jj;
    }

    if (jj < text.size())
        // The suffix is larger in than the pattern, so it's greater
        return true;
    else
        // The suffix is of the same length of the pattern, so they are equal
        return false;
}


bool patternInSuffix(const std::string& text, const std::string& pattern, int suffix)
{
    // Check if the pattern is at the start of the suffix
    std::size_t suffixIndex {static_cast<std::size_t>(suffix)};

    if (text.size() - suffixIndex < pattern.size())
        return false;

    for (auto ii {0}; ii < pattern.size(); ++ii)
        if (text[suffixIndex + ii] != pattern[ii])
            return false;

    return true;
}


std::pair<int, int> patternMatchSuffixArray(const std::vector<int>& suffixArray,
                                            const std::string& text,
                                            const std::string& pattern)
{
    // Returns a pair where the first element is the starting index in the suffix array
    // where there is a match of the pattern and the second element is the last index where there is
    // a match. If there are no matches it returns a pair of (-1, -1).
    if (suffixArray.empty() || pattern.empty() || (pattern.size() > suffixArray.size()))
        return {-1, -1};

    // The suffixes are ordered in the suffix array. We can perform binary search on it to
    // find if there are any matches
    int left {-1};
    int right {static_cast<int>(suffixArray.size()) - 1};

    // Search for the leftmost suffix which contains the pattern
    while (right - left > 1)
    {
        int middle {left + (right - left) / 2};
        int suffix {suffixArray[middle]};
        if (patternInSuffix(text, pattern, suffix)
            || isSuffixGreater(text, pattern, suffix))
            right = middle;
        else
            left = middle;
    }
    int first {right};

    // Search for the rightmost suffix which contains the pattern
    left = 0;
    right = static_cast<int>(suffixArray.size());
    while (right - left > 1)
    {
        int middle {left + (right - left) / 2};
        int suffix {suffixArray[middle]};
        if (patternInSuffix(text, pattern, suffix)
            || !isSuffixGreater(text, pattern, suffix))
            left = middle;
        else
            right = middle;
    }
    int last {left};

    if (first > last)
        return {-1, -1};

    return {first, last};
}
