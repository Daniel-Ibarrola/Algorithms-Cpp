//
// Created by daniel on 9/05/22.
//

#include "ClosestPoints.h"
#include <algorithm>
#include <cmath>


// Point2D Methods

bool operator==(const Point2D& p1, const Point2D& p2)
{
    return p1.m_x == p2.m_x && p1.m_y == p2.m_y;
}

bool operator!=(const Point2D& p1, const Point2D& p2)
{
   return !(operator==(p1, p2));
}

bool operator<(const Point2D& p1, const Point2D& p2)
{
    return p1.m_x < p2.m_x;
}

bool operator>(const Point2D& p1, const Point2D& p2)
{
    return !(operator<(p1, p2));
}

bool operator<=(const Point2D& p1, const Point2D& p2)
{
    return !(operator>(p1, p2));
}

bool operator>=(const Point2D& p1, const Point2D& p2)
{
    return !(operator<(p1, p2));
}

double distanceBetween(const Point2D& p1, const Point2D& p2)
{
    return std::sqrt(static_cast<double>(std::pow(p1.x() - p2.x(), 2) +
                    std::pow(p1.y() - p2.y(), 2)));
}

// Minimal Distance Algorithms

double minDistanceRecursive(const std::vector<Point2D>& points, int left, int right)
{
    // Find the minimal distance in a set of points by recursively splitting the
    // set into halves.

    // Base case: There are four points or fewer.
    if (right - left <= 4)
    {
        double minDis {std::numeric_limits<double>::infinity()};
        for (int ii {left}; ii < right; ++ii)
        {
            for (int jj {ii + 1}; jj < right; ++jj)
                minDis = std::min(minDis, distanceBetween(points[ii], points[jj]));
        }
        return minDis;
    }

    // Split into halves and find the minimum distance in each half
    int midline {left + (right - left) / 2};
    int mid_x {points[midline].x()};
    double distanceLeft {minDistanceRecursive(points, left, midline)};
    double distanceRight {minDistanceRecursive(points, midline, right)};
    double minDis {std::min(distanceLeft, distanceRight)};

    // Now we need to check it there is a smaller distance between points of the right and left halves
    // We check if there is a smaller distance in the strip that goes from the midline
    // to midline + minDistance and midline - minDistance
    std::vector<Point2D> strip {};
    for (int ii {left}; ii < right; ++ii)
    {
        if (abs(points[ii].x() - mid_x) < minDis)
            strip.push_back(points[ii]);
    }

    if (strip.size() > 1)
    {
        for (auto ii {0}; ii < strip.size() - 1; ++ii)
        {
            for (auto jj {ii + 1}; strip.size(); ++ jj)
                minDis = std::min(minDis, distanceBetween(strip[ii], strip[jj]));
        }
    }

    return minDis;
}

double minDistance(std::vector<Point2D>& points)
{
    // Returns the minimal distance in a set of points
    std::sort(points.begin(), points.end());
    return minDistanceRecursive(points, 0, static_cast<int>(points.size()));
}


