//
// Created by daniel on 9/05/22.
//

#include "Segments.h"

bool compareEvents(const Event& e1, const Event& e2)
{
    if (e1.coord == e2.coord)
        return e1.type < e2.type;
    return e1.coord < e2.coord;
}

std::vector<int> countSegmentsSort(std::vector<int>& starts, std::vector<int>& ends, std::vector<int>& points)
{
    /* Faster algorithm for counting the number of segments each point is contained
     * in by sorting all points.
     * starts is a vector containing the start point of each segment
     * ends is a vector containing the end point of each segment
     *
     */
    std::vector<int> count(points.size());

    std::vector<Event> events {};
    for (auto ii {0}; ii < starts.size(); ++ii)
    {
        events.push_back( Event {starts[ii], 'l', ii} );
        events.push_back( Event {ends[ii], 'r', ii} );
    }
    for (auto ii {0}; ii < points.size(); ++ii)
        events.push_back( Event {points[ii], 'p', ii} );

    std::sort(events.begin(), events.end(), compareEvents);
    int numSegments {0};

    for (auto e : events)
    {
        if (e.type == 'l')
            numSegments++;
        else if (e.type == 'p')
            count[e.index] = numSegments;
        else
            numSegments--;
    }

    return count;
}