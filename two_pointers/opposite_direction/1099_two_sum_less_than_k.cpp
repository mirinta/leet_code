#include <algorithm>
#include <vector>

/**
 * Given an array nums of integers and integer k, return the maximum sum such that there exists i <
 * j with nums[i] + nums[j] = sum and sum < k. If no i, j exist satisfying this equation, return -1.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 1000
 * ! 1 <= k <= 2000
 */

class Solution {
public:
    int twoSumLessThanK(std::vector<int>& nums, int k)
    {
        std::sort(nums.begin(), nums.end());
        int lo = 0;
        int hi = nums.size() - 1;
        int result = INT_MIN;
        while (lo < hi) {
            if (nums[lo] + nums[hi] >= k) {
                hi--;
            } else {
                result = std::max(result, nums[lo] + nums[hi]);
                lo++;
            }
        }
        return result == INT_MIN ? -1 : result;
    }
};