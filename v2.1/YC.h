 //
// Created by 洋葱落日 on 2024/8/21.
//

#include <iostream>
#include <vector>
#include <cmath>

// 定义 Point 结构体，用于存储点的坐标
struct Point {
    float x; // 点的 X 坐标
    float y; // 点的 Y 坐标
    float m; // 三维坐标或其他用途，当前代码中主要为0
};

// 函数：读取最后一个点的坐标
void readLastPoint(const std::vector<Point>& points, float& a, float& b) {
    if (!points.empty()) {
        const Point& lastPoint = points.back(); // 获取最后一个点
        a = lastPoint.x; // 将最后一个点的 X 坐标赋值给 a
        b = lastPoint.y; // 将最后一个点的 Y 坐标赋值给 b
    }
}

// 函数：检查二维空间中的重叠
bool matchSpace2d(const std::vector<Point>& points, float x, float y, float width, float height) {
    for (const auto& point : points) {
        // 检查当前点与集合中每个点的重叠情况
        if (std::abs(point.x - x) < width && std::abs(point.y - y) < height) {
            return true; // 若有重叠，返回 true
        }
    }
    return false; // 否则返回 false
}

// 函数：检查三维空间中的重叠
bool matchSpace3d(const std::vector<Point>& points, float x, float y, float m, float width, float height) {
    for (const auto& point : points) {
        // 检查当前点与集合中每个点的重叠情况 
        if (std::abs(point.x - x) < width && std::abs(point.y - y) < height && std::abs(point.m - m) <= 5) {
            return true; // 若有重叠，返回 true
        }
    }
    return false; // 否则返回 false
}

// 函数：调整 Y 坐标位置
void adjustPosition(float& x, float& y, float offset) {
    y -= offset; // 将 Y 坐标偏移一定的值以避免重叠
}

// 函数：在二维空间中添加点
void addToEnd2D(std::vector<Point>& points, float& x, float& y, float width, float height) {
    if (matchSpace2d(points, x, y, width, height)) {
        for (const auto& point : points) {
            // 检查与当前点的重叠情况
            if (std::abs(point.x - x) < width && std::abs(point.y - y) < height) {
                // 将新的 x 坐标调整为与重叠点相同
                x = point.x; 
                adjustPosition(x, y, 5); // 向下移动 y 坐标
                break; // 退出循环以重新检查新位置的重叠情况
            }
        }
        addToEnd2D(points, x, y, width, height); // 递归查找新的位置
        return; // 退出函数
    }
    points.push_back({x, y, 0}); // 添加新的点，m值设置为0
}

// 函数：在三维空间中添加点
void addToEnd3D(std::vector<Point>& points, float& x, float& y, float& m, float width, float height) {
    if (matchSpace3d(points, x, y, m, width, height)) {
        for (const auto& point : points) {
            if (std::abs(point.x - x) < width && std::abs(point.y - y) < height && std::abs(point.m - m) <= 5) {
                // 调整 x 坐标和 y 坐标
                x = point.x; 
                adjustPosition(x, y, 5); // 向下移动 y 坐标
                break; // 退出循环以重新检查新位置的重叠情况
            }
        }
        addToEnd3D(points, x, y, m, width, height); // 递归查找新的位置
        return; // 退出函数
    }
    points.push_back({x, y, m}); // 添加新的点
}

// 函数：根据类型调用不同的添加函数
void addToEnd(std::vector<Point>& points, float x, float y, float m, float textWidth, float textHeight, bool t) {
    if (t) {
        addToEnd2D(points, x, y, textWidth, textHeight); // 添加二维点
    } else {
        addToEnd3D(points, x, y, m, textWidth, textHeight); // 添加三维点
    }
}
