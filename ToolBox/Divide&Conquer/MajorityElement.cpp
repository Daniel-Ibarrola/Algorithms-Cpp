//
// Created by daniel on 9/05/22.
//

#include "MajorityElement.h"


int majorityElement(std::vector<int> &elements, int left, int right)
{
    if (left == right)
        return -1;
    if (left + 1 == right)
        return elements[left];

    int midpoint {left + (right - left) / 2};

    int leftElement {majorityElement(elements, left, midpoint)};
    if (leftElement != -1)
    {
        int count {0};
        for (auto ii {left}; ii < right; ++ii)
        {
            if (elements[ii] == leftElement)
                ++count;
        }

        if (2 * count > right - left)
            return leftElement;
    }

    int rightElement {majorityElement(elements, midpoint, right)};
    if (rightElement != -1)
    {
        int count {0};
        for (auto ii {left}; ii < right; ++ii)
        {
            if (elements[ii] == rightElement)
                ++count;
        }

        if (2 * count > right - left)
            return rightElement;
    }

    return -1;
}

int majorityElementNaive(const std::vector<int> &elements)
{
    int numberOfElements {static_cast<int>(elements.size())};
    int count;
    for (auto currentElement : elements)
    {
        count = 0;
        for (auto element : elements)
        {
            if (element == currentElement)
                count += 1;
        }
        if (count > numberOfElements / 2)
            return currentElement;
    }
    return -1;
}