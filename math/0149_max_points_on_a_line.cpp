#include <unordered_map>
#include <vector>

/**
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, return
 * the maximum number of points that lie on the same straight line.
 *
 * ! 1 <= points.length <= 300
 * ! points[i].length == 2
 * ! -10^4 <= xi, yi <= 10^4
 * ! All the points are unique.
 */

class Solution {
public:
    int maxPoints(std::vector<std::vector<int>>& points)
    {
        if (points.size() < 2)
            return points.size();

        int result = 0;
        for (int i = 0; i < points.size(); ++i) {
            std::unordered_map<double, int> map;
            for (int j = i + 1; j < points.size(); ++j) {
                double slope = 0;
                if (points[i][0] == points[j][0]) {
                    slope = INFINITY;
                } else {
                    slope = (points[i][1] - points[j][1]) * 1.0 / (points[i][0] - points[j][0]);
                }
                map[slope]++;
            }
            for (const auto& [slope, numOfPairs] : map) {
                result = std::max(result, numOfPairs + 1);
            }
        }
        return result;
    }
};