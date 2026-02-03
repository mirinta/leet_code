#include <vector>

/**
 * You are given an integer array nums of length n.
 *
 * An array is trionic if there exist indices 0 < p < q < n - 1 such that:
 *
 * - nums[0...p] is strictly increasing,
 *
 * - nums[p...q] is strictly decreasing,
 *
 * - nums[q...n-1] is strictly increasing.
 *
 * Return true if nums is trionic, otherwise return false.
 *
 * ! 3 <= n <= 100
 * ! -1000 <= nums[i] <= 1000
 */

class Solution {
public:
    bool isTrionic(std::vector<int>& nums)
    {
        const int n = nums.size();
        auto findIncreasing = [&](int start) {
            while (start + 1 < n && nums[start] < nums[start + 1]) {
                start++;
            }
            return start;
        };
        auto findDecreasing = [&](int start) {
            while (start + 1 < n && nums[start] > nums[start + 1]) {
                start++;
            }
            return start;
        };
        const int p = findIncreasing(0);
        const int q = findDecreasing(p);
        if (p <= 0 || p >= q || q >= n - 1)
            return false;

        return findIncreasing(q) == n - 1;
    }
};