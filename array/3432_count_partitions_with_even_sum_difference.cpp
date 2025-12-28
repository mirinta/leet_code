#include <numeric>
#include <vector>

/**
 * You are given an integer array nums of length n.
 *
 * A partition is defined as an index i where 0 <= i < n - 1, splitting the array into two non-empty
 * subarrays such that:
 *
 * - Left subarray contains indices [0, i].
 *
 * - Right subarray contains indices [i + 1, n - 1].
 *
 * Return the number of partitions where the difference between the sum of the left and right
 * subarrays is even.
 *
 * ! 2 <= n == nums.length <= 100
 * ! 1 <= nums[i] <= 100
 */

class Solution {
public:
    int countPartitions(std::vector<int>& nums)
    {
        const int n = nums.size();
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        int result = 0;
        for (int i = 0, left = 0; i < n - 1; ++i) {
            left += nums[i];
            result += (total - 2 * left) % 2 == 0;
        }
        return result;
    }
};