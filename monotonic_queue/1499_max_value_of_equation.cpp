#include <deque>
#include <vector>

/**
 * You are given an array points containing the coordinates of points on a 2D plane, sorted by the
 * x-values, where points[i] = [xi, yi] such that xi < xj for all 1 <= i < j <= points.length. You
 * are also given an integer k.
 *
 * Return the maximum value of the equation yi + yj + |xi - xj| where |xi - xj| <= k and 1 <= i < j
 * <= points.length.
 *
 * It is guaranteed that there exists at least one pair of points that satisfy the constraint |xi -
 * xj| <= k.
 *
 * ! 2 <= points.length <= 10^5
 * ! points[i].length == 2
 * ! -10^8 <= xi, yi <= 10^8
 * ! 0 <= k <= 2 * 10^8
 * ! xi < xj for all 1 <= i < j <= points.length
 * ! xi form a strictly increasing sequence.
 */

class Solution {
public:
    int findMaxValueOfEquation(std::vector<std::vector<int>>& points, int k)
    {
        // i < j and |xi - xj| <= k
        // the input array is already sorted by the x-values,
        // yi + yj + |xi - xj| = yi + yj + xj - xi = (xj + yj) + (yi - xi)
        // given j, we need to find the max value of (yi - xi)
        const int n = points.size();
        std::deque<int> deque; // stores i
        int result = INT_MIN;
        for (int j = 0; j < n; ++j) {
            const int xj = points[j][0];
            const int yj = points[j][1];
            // [FRONT X X i X X BACK] j
            while (!deque.empty() && xj - points[deque.front()][0] > k) {
                deque.pop_front();
            }
            if (!deque.empty()) {
                result = std::max(result, xj + yj + points[deque.front()][1] - points[deque.front()][0]);
            }
            while (!deque.empty() && yj - xj >= points[deque.back()][1] - points[deque.back()][0]) {
                deque.pop_back();
            }
            deque.push_back(j);
        }
        return result;
    }
};