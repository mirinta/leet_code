#include <vector>

/**
 * You are given a 2D array points of size n x 2 representing integer coordinates of some points on
 * a 2D plane, where points[i] = [xi, yi].
 *
 * Count the number of pairs of points (A, B), where
 *
 * - A is on the upper left side of B, and
 *
 * - there are no other points in the rectangle (or line) they make (including the border).
 *
 * Return the count.
 *
 * ! 2 <= n <= 50
 * ! points[i].length == 2
 * ! 0 <= points[i][0], points[i][1] <= 50
 * ! All points[i] are distinct.
 */

class Solution {
public:
    int numberOfPairs(std::vector<std::vector<int>>& points)
    {
        const int n = points.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                result += isValid(i, j, points);
            }
        }
        return result;
    }

private:
    bool isValid(int i, int j, const std::vector<std::vector<int>>& points)
    {
        // A = points[i], B = points[j]
        // case 1: A is the top-left point and B is the bottom-right point
        // case 2: B is the top-left point and A is the bottom-right point
        const auto& ax = points[i][0];
        const auto& ay = points[i][1];
        const auto& bx = points[j][0];
        const auto& by = points[j][1];
        const bool case1 = ax <= bx && ay >= by;
        const bool case2 = ax >= bx && ay <= by;
        if (!case1 && !case2)
            return false;

        const int xmin = std::min(ax, bx);
        const int xmax = std::max(ax, bx);
        const int ymin = std::min(ay, by);
        const int ymax = std::max(ay, by);
        for (int k = 0; k < points.size(); ++k) {
            if (k == i || k == j)
                continue;

            const auto& x = points[k][0];
            const auto& y = points[k][1];
            if (x >= xmin && x <= xmax && y >= ymin && y <= ymax)
                return false;
        }
        return true;
    }
};
