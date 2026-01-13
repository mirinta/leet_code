#include <vector>

/**
 * You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the
 * bottom-left point and the side length of a square parallel to the x-axis.
 *
 * Find the minimum y-coordinate value of a horizontal line such that the total area of the squares above the line
 * equals the total area of the squares below the line.
 *
 * Answers within 10^-5 of the actual answer will be accepted.
 *
 * Note: Squares may overlap. Overlapping areas should be counted multiple times.
 *
 * ! 1 <= squares.length <= 5 * 10^4
 * ! squares[i] = [xi, yi, li]
 * ! squares[i].length == 3
 * ! 0 <= xi, yi <= 10^9
 * ! 1 <= li <= 10^9
 * ! The total area of all the squares will not exceed 10^12.
 */

class Solution {
public:
    double separateSquares(std::vector<std::vector<int>>& squares)
    {
        static constexpr double kEpsilon = 1e-5;
        double total = 0;
        double maxY = DBL_MIN;
        double minY = DBL_MAX;
        for (const auto& s : squares) {
            total += 1.0 * s[2] * s[2];
            maxY = std::max<double>(maxY, s[1] + s[2]);
            minY = std::min<double>(minY, s[1]);
        }
        double hi = maxY;
        double lo = minY;
        while (hi - lo > kEpsilon) {
            const double y = lo + (hi - lo) / 2;
            if (isValid(y, total, squares)) {
                hi = y;
            } else {
                lo = y;
            }
        }
        return lo;
    }

private:
    bool isValid(double y, double total, const std::vector<std::vector<int>>& squares)
    {
        double area = 0;
        for (const auto& s : squares) {
            if (y > s[1]) {
                area += s[2] * std::min<double>(y - s[1], s[2]);
            }
        }
        return area * 2 >= total;
    }
};