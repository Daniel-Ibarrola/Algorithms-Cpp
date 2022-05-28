//
// Created by daniel on 27/05/22.
//

#include "substring.h"

long long polyHash(const std::string& str, long long prime, long long multiplier)
{
    // Polynomial hash function to compute the hash of a string
    long long hash {0};
    int size {static_cast<int>(str.size())};
    for (int ii {size}; ii >= 0; --ii)
        hash = (hash * multiplier + str[ii]) % prime;
    return hash;
}

std::vector<long long> precomputeHashes(const std::string& text, int patternSize,
                                                 long long prime, long long multiplier)
{
    // Precompute the hashes of the substrings in the string 'text'
    int textSize {static_cast<int>(text.size())};
    std::vector<long long> hashes(textSize - patternSize + 1);
    std::string substr {text.substr(textSize - patternSize, patternSize)};
    hashes[textSize - patternSize] = polyHash(substr, prime, multiplier);

    long long y {1};
    for (int ii {1}; ii < patternSize + 1; ++ii)
        y = (y * multiplier) % prime;

    for (int ii{textSize - patternSize - 1}; ii >= 0; --ii)
    {
        long long result {multiplier * hashes[ii + 1] + text[ii] - y * text[ii + patternSize]};
        hashes[ii] = ((result % prime) + prime) % prime;
    }

    return hashes;
}

bool areEqual(const std::string& pattern, const std::string& testStr,
              std::size_t startPos, std::size_t endPos)
{
    // Checks whether the pattern is equal to another string

    // If strings are of different size they are not equal
    if (pattern.size() !=  endPos - startPos)
        return false;

    for (auto ii {0}; ii < pattern.size(); ++ii)
    {
        if (pattern[ii] != testStr[startPos + ii])
            return false;
    }
    return true;
}

std::vector<int> searchSubstring(const std::string& text, const std::string& pattern)
{
    // Returns a vector with all positions where the substring 'pattern' is found in
    // the string 'text'. If there are no matches it returns an empty vector
    std::vector<int> positions;
    if (text.empty() || pattern.empty())
        return positions;
    if (pattern.size() > text.size())
        return positions;

    long long prime {1000000007};
    long long multiplier {263};
    long long patternHash {polyHash(pattern, prime, multiplier)};
    std::vector<long long> hashes {precomputeHashes(text, static_cast<int>(pattern.size()), prime, multiplier)};

    for (auto ii {0}; ii < text.size() - pattern.size() + 1; ++ii)
    {
        if (patternHash != hashes[ii])
            continue;
        if (areEqual(pattern, text, ii, ii + pattern.size()))
            positions.push_back(ii);
    }

    return positions;
}
