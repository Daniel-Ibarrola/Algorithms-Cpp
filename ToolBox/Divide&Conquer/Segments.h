//
// Created by daniel on 9/05/22.
//

#ifndef ALGORITHMS_SEGMENTS_H
#define ALGORITHMS_SEGMENTS_H

#include <algorithm>
#include <vector>

struct Event
{
    int coord {};
    char type {};
    int index {};
};

bool compareEvents(const Event& e1, const Event& e2);

std::vector<int> countSegmentsSort(std::vector<int>& starts, std::vector<int>& ends, std::vector<int>& points);


#endif //ALGORITHMS_SEGMENTS_H
