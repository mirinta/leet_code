#include <algorithm>
#include <vector>

/**
 * You want to build some obstacle courses. You are given a 0-indexed integer array "obstacles" of
 * length "n", where obstacles[i] describes the height of the ith obstacle.
 *
 * For every index i between 0 and n - 1 (inclusive), find the length of the longest obstacle course
 * in obstacles such that:
 *
 * - You choose any number of obstacles between 0 and i inclusive.
 *
 * - You must include the ith obstacle in the course.
 *
 * - You must put the chosen obstacles in the same order as they appear in obstacles.
 *
 * - Every obstacle (expect the first) is taller than or the same height as the obstacle immediately
 * before it.
 *
 * Return an array "ans" of length n, where ans[i] is the length of the longest obstacle course for
 * index i as described above.
 *
 * ! n == obstacles.length
 * ! 1 <= n <= 10^5
 * ! 1 <= obstacles[i] <= 10^7
 */

class Solution {
public:
    std::vector<int> longestObstacleCourseAtEachPosition(std::vector<int>& obstacles)
    {
        // it is similar to the LIS problem (No.300)
        // our goal is to find the length of the longest non-decreasing subsequence ending at
        // obstacles[i] traditional DP with O(N^2) time complexity is not accepted (TLE)
        const int n = obstacles.size();
        std::vector<int> vec; // non-decreasing
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            if (vec.empty() || vec.back() <= obstacles[i]) {
                vec.push_back(obstacles[i]);
                result[i] = vec.size();
            } else {
                auto iter = std::upper_bound(vec.begin(), vec.end(), obstacles[i]);
                // iter != vec.end() is guaranteed,
                // if not, it means all elements of vec <= obstacles[i]
                // this case is handled in the above branch
                *iter = obstacles[i];
                result[i] = std::distance(vec.begin(), iter) + 1;
            }
        }
        return result;
    }
};