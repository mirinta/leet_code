#include <vector>

/**
 * Given an array of points on the X-Y plane points where points[i] = [xi, yi], return the area of
 * the largest triangle that can be formed by any three different points. Answers within 10-5 of the
 * actual answer will be accepted.
 *
 * ! 3 <= points.length <= 50
 * ! -50 <= xi, yi <= 50
 * ! All the given points are unique.
 */

class Solution {
public:
    double largestTriangleArea(std::vector<std::vector<int>>& points)
    {
        const int n = points.size();
        double result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    result = std::max(result, area(i, j, k, points));
                }
            }
        }
        return result;
    }

private:
    double area(int i, int j, int k, const std::vector<std::vector<int>>& points)
    {
        const auto& x1 = points[i][0];
        const auto& y1 = points[i][1];
        const auto& x2 = points[j][0];
        const auto& y2 = points[j][1];
        const auto& x3 = points[k][0];
        const auto& y3 = points[k][1];
        return 0.5 * std::abs(x1 * y2 - y1 * x2 + x2 * y3 - y2 * x3 + y1 * x3 - x1 * y3);
    }
};