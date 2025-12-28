#include <algorithm>
#include <vector>

/**
 * Given n points on a 2D plane where points[i] = [xi, yi], Return the widest vertical area between
 * two points such that no points are inside the area.
 *
 * A vertical area is an area of fixed-width extending infinitely along the y-axis (i.e., infinite
 * height). The widest vertical area is the one with the maximum width.
 *
 * Note that points on the edge of a vertical area are not considered included in the area.
 *
 * ! n == points.length
 * ! 2 <= n <= 10^5
 * ! points[i].length == 2
 * ! 0 <= xi, yi <= 10^9
 */

class Solution {
public:
    int maxWidthOfVerticalArea(std::vector<std::vector<int>>& points)
    {
        std::sort(points.begin(), points.end(), [](const auto& p1, const auto& p2) { return p1[0] < p2[0]; });
        int result = 0;
        for (int i = 1; i < points.size(); ++i) {
            result = std::max(result, points[i][0] - points[i - 1][0]);
        }
        return result;
    }
};