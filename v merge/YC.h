//
// Created by 洋葱落日 on 2024/8/21.
//

#include <iostream>
#include <vector>
#include <cmath>

// 共用结构体
struct Point {
    float x;
    float y;
    float m;
};

// ========== v1.0 经典防重叠算法 ==========
bool matchPoint2D_v1(const std::vector<Point>& points, float x, float y) {
    for (const auto& point : points) {
        if (std::abs(point.x - x) <= 25 && std::abs(point.y - y) <= 12 ) {
            return true;
        }
    }
    return false;
}

void addToEnd2D_v1(std::vector<Point>& points, float x, float y ) {
    if (matchPoint2D_v1(points, x, y )) {
        for (auto& point : points) {
            if (std::abs(point.x - x) <= 25 && std::abs(point.y - y) <= 12) {
                x = point.x;
                y = point.y - 20;
                addToEnd2D_v1(points, x, y );
                return;
            }
        }
    }
    points.push_back({x, y, 0});
}

bool matchPoint3D_v1(const std::vector<Point>& points, float x, float y, float m) {
    for (const auto& point : points) {
        if (std::abs(point.x - x) <= 25 && std::abs(point.y - y) <= 12 && std::abs(point.m - m) <= 5) {
            return true;
        }
    }
    return false;
}

void addToEnd3D_v1(std::vector<Point>& points, float x, float y, float m) {
    if (matchPoint3D_v1(points, x, y, m)) {
        for (auto& point : points) {
            if (std::abs(point.x - x) <= 25 && std::abs(point.y - y) <= 12 && std::abs(point.m - m) <= 5) {
                x = point.x;
                y = point.y - 20;
                addToEnd3D_v1(points, x, y, m);
                return;
            }
        }
    }
    points.push_back({ x, y, m });
}

// ========== v2.1 YC防重叠算法 ==========
bool matchSpace2d_v2(const std::vector<Point>& points, float x, float y, float width, float height) {
    for (const auto& point : points) {
        if (std::abs(point.x - x) < width && std::abs(point.y - y) < height) {
            return true;
        }
    }
    return false;
}

bool matchSpace3d_v2(const std::vector<Point>& points, float x, float y, float m, float width, float height) {
    for (const auto& point : points) {
        if (std::abs(point.x - x) < width && std::abs(point.y - y) < height && std::abs(point.m - m) <= 5) {
            return true;
        }
    }
    return false;
}

void adjustPosition_v2(float& x, float& y, float offset) {
    y -= offset;
}

void addToEnd2D_v2(std::vector<Point>& points, float& x, float& y, float width, float height) {
    if (matchSpace2d_v2(points, x, y, width, height)) {
        for (const auto& point : points) {
            if (std::abs(point.x - x) < width && std::abs(point.y - y) < height) {
                x = point.x;
                adjustPosition_v2(x, y, 5);
                break;
            }
        }
        addToEnd2D_v2(points, x, y, width, height);
        return;
    }
    points.push_back({x, y, 0});
}

void addToEnd3D_v2(std::vector<Point>& points, float& x, float& y, float& m, float width, float height) {
    if (matchSpace3d_v2(points, x, y, m, width, height)) {
        for (const auto& point : points) {
            if (std::abs(point.x - x) < width && std::abs(point.y - y) < height && std::abs(point.m - m) <= 5) {
                x = point.x;
                adjustPosition_v2(x, y, 5);
                break;
            }
        }
        addToEnd3D_v2(points, x, y, m, width, height);
        return;
    }
    points.push_back({x, y, m});
}

// ========== 通用接口：选择版本 ==========
enum YCVersion { YC_V1 = 0, YC_V2 = 1 };

// version: 0=1.0算法，1=2.1算法
inline void addToEnd(std::vector<Point>& points, float x, float y, float m, bool is2D, YCVersion version = YC_V2,
                     float width = 25, float height = 12) {
    if (version == YC_V1) {
        if (is2D)
            addToEnd2D_v1(points, x, y);
        else
            addToEnd3D_v1(points, x, y, m);
    } else {
        if (is2D)
            addToEnd2D_v2(points, x, y, width, height);
        else
            addToEnd3D_v2(points, x, y, m, width, height);
    }
}

// 读取最后一个点
inline void readLastPoint(const std::vector<Point>& points, float& a, float& b) {
    if (!points.empty()) {
        const Point& lastPoint = points.back();
        a = lastPoint.x;
        b = lastPoint.y;
    }
}
