#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed integer array nums, where nums[i] represents the score of the ith
 * student. You are also given an integer k.
 *
 * Pick the scores of any k students from the array so that the difference between the highest and
 * the lowest of the k scores is minimized.
 *
 * Return the minimum possible difference.
 *
 * ! 1 <= k <= nums.length <= 1000
 * ! 0 <= nums[i] <= 10^5
 */

class Solution {
public:
    int minimumDifference(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int result = INT_MAX;
        for (int i = 0; i <= n - k; ++i) {
            result = std::min(result, nums[i + k - 1] - nums[i]);
        }
        return result;
    }
};