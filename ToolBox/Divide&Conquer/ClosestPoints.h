//
// Created by daniel on 9/05/22.
//

#ifndef ALGORITHMS_CLOSESTPOINTS_H
#define ALGORITHMS_CLOSESTPOINTS_H

#include <vector>

class Point2D
{
    // A class to represent 2D points
private:
    int m_x;
    int m_y;

public:

    Point2D()
    {
        m_x = 0;
        m_y = 0;
    }

    Point2D(int x, int y)
        : m_x {x}, m_y {y}
    {

    }

    int x() const {return m_x;}
    int y() const {return m_y;}

    friend bool operator==(const Point2D& p1, const Point2D& p2);
    friend bool operator!=(const Point2D& p1, const Point2D& p2);

    // A point is considered less than another point if its x value is lesser.

    friend bool operator<(const Point2D& p1, const Point2D& p2);
    friend bool operator>(const Point2D& p1, const Point2D& p2);

    friend bool operator<=(const Point2D& p1, const Point2D& p2);
    friend bool operator>=(const Point2D& p1, const Point2D& p2);

    friend double distanceBetween(const Point2D& p1, const Point2D& p2);

};

// Min Distance Algorithms

double minDistanceRecursive(const std::vector<Point2D>& points, int left, int right);
double minDistance(std::vector<Point2D>& points);

#endif //ALGORITHMS_CLOSESTPOINTS_H
