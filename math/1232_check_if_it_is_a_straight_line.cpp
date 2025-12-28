#include <vector>

/**
 * You are given an array "coordinates", coordinates[i] = [x, y], where [x, y] represents the
 * coordinate of a point.
 *
 * Check if these points make a straight line in the XY plane.
 *
 * ! coordinates[i].length == 2
 * ! coordinates contains no duplicate point.
 */

class Solution {
public:
    bool checkStraightLine(const std::vector<std::vector<int>>& coordinates)
    {
        // if (x0,y0), (x1,y1) and (x2,y2) are in the same line
        // then (y1-y0)/(x1-x0) = (y2-y0)/(x2-x0) = k
        // to avoid division by zero,
        // we check (y1-y0) * (x2-x0) == (y2-y0) * (x1-x0)
        const auto n = coordinates.size();
        if (n < 2)
            return false;

        // no duplicate points
        if (n == 2)
            return true;

        const auto& x0 = coordinates[0][0];
        const auto& y0 = coordinates[0][1];
        const auto dx = coordinates[1][0] - x0;
        const auto dy = coordinates[1][1] - y0;
        for (size_t i = 2; i < n; ++i) {
            const auto& xi = coordinates[i][0];
            const auto& yi = coordinates[i][1];
            if (dy * (xi - x0) != (yi - y0) * dx)
                return false;
        }
        return true;
    }
};