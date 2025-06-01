//洋葱落日

#include <iostream>
#include <vector>
#include <cmath>
//共用一个结构体
struct Point {
    float x;
    float y;
    float m;
};

bool matchPoint2D(const std::vector<Point>& points, float x, float y) {
    for (const auto& point : points) {
        if (std::abs(point.x - x) <= 25 && std::abs(point.y - y) <= 12 ) {
            return true;
        }
    }
    return false;
}

void addToEnd2D(std::vector<Point>& points, float x, float y ) {
    if (matchPoint2D(points, x, y )) {
        for (auto& point : points) {
            if (std::abs(point.x - x) <= 25 && std::abs(point.y - y) <= 12) {
                x = point.x;
                y = point.y - 20;
                addToEnd2D(points, x, y );
                return;
            }
        }
    }

    points.push_back({x, y });
}


bool matchPoint3D(const std::vector<Point>& points, float x, float y, float m)
{
    for (const auto& point : points)
    {
        if (std::abs(point.x - x) <= 25 && std::abs(point.y - y) <= 12 && std::abs(point.m - m) <= 5)
        {
            return true;
        }
    }
    return false;
}

void addToEnd3D(std::vector<Point>& points, float x, float y, float m)
{
    if (matchPoint3D(points, x, y, m))
    {
        for (auto& point : points)
        {
            if (std::abs(point.x - x) <= 25 && std::abs(point.y - y) <= 12 && std::abs(point.m - m) <= 5)
            {
                x = point.x;
                y = point.y - 20;
                addToEnd3D(points, x, y, m);
                return;
            }
        }
    }

    points.push_back({ x, y, m });
}


void addToEnd(std::vector<Point>& points, float x, float y, float m, bool t)
{
    if(t)
    {
         addToEnd2D(points, x, y);
    }
    else
    {
        addToEnd3D(points, x, y, m);
    }
}


void readLastPoint(const std::vector<Point>& points, float& a, float& b)
{
    if (!points.empty())
    {
        const Point& lastPoint = points.back();
        a = lastPoint.x;
        b = lastPoint.y;
    }
}
