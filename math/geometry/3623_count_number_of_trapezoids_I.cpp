#include <unordered_map>
#include <vector>

/**
 * You are given a 2D integer array points, where points[i] = [xi, yi] represents the coordinates of
 * the ith point on the Cartesian plane.
 *
 * A horizontal trapezoid is a convex quadrilateral with at least one pair of horizontal sides (i.e.
 * parallel to the x-axis). Two lines are parallel if and only if they have the same slope.
 *
 * Return the number of unique horizontal trapezoids that can be formed by choosing any four
 * distinct points from points.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 4 <= points.length <= 10^5
 * ! –10^8 <= xi, yi <= 10^8
 * ! All points are pairwise distinct.
 */

class Solution {
public:
    int countTrapezoids(std::vector<std::vector<int>>& points)
    {
        static constexpr long long kMod = 1e9 + 7;
        std::unordered_map<int, int> map;
        for (const auto& p : points) {
            map[p[1]]++;
        }
        const int n = points.size();
        std::vector<long long> combOf2(n + 1, 0);
        combOf2[2] = 1;
        for (int i = 3; i <= n; ++i) {
            combOf2[i] = (combOf2[i - 1] + i - 1) % kMod;
        }
        long long sum = 0;
        long long result = 0;
        for (const auto& [h, count] : map) {
            if (count < 2)
                continue;

            result = (result + combOf2[count] * sum % kMod) % kMod;
            sum = (sum + combOf2[count]) % kMod;
        }
        return result;
    }
};