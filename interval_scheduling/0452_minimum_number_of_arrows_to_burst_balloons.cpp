#include <algorithm>
#include <vector>

/**
 * There are some spherical balloons taped onto a flat wall that represents the XY-plane. The
 * balloons are represented as a 2D integer array points where points[i] = [x_start, x_end] denotes
 * a balloon whose horizontal diameter stretches between x_start and x_end. You do not know the
 * exact y-coordinates of the balloons.
 *
 * Arrows can be shot up directly vertically (in the positive y-direction) from different points
 * along the x-axis. A balloon with x_start and x_end is burst by an arrow shot at x if x_start <= x
 * <= x_end. There is no limit to the number of arrows that can be shot. A shot arrow keeps
 * traveling up infinitely, bursting any balloons in its path.
 *
 * Given the array points, return the minimum number of arrows that must be shot to burst all
 * balloons.
 *
 * ! 1 <= points.length <= 10^5
 * ! points[i].length == 2
 * ! -2^31 <= x_start < x_end <= 2^31 - 1
 */

class Solution {
public:
    // time O(NlogN), space O(std::sort)=O(logN)
    int findMinArrowShots(std::vector<std::vector<int>>& points)
    {
        if (points.empty())
            return 0;

        const int n = points.size();
        // min num of arrows = max num of non-overlapping intervals
        std::sort(points.begin(), points.end(), [](const auto& v1, const auto& v2) {
            return v1[1] < v2[1]; // sort by ending points
        });
        // i0<---->i1
        //     j0<---->j1
        int result = 1;
        int endingPoint = points[0][1];
        for (int i = 1; i < n; ++i) {
            if (points[i][0] > endingPoint) {
                endingPoint = points[i][1];
                result++;
            }
        }
        return result;
    }
};
