#include <vector>

/**
 * You may recall that an array arr is a mountain array if and only if:
 *
 * - arr.length >= 3
 *
 * - There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
 *
 *   - arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
 *
 *   - arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
 *
 * Given an integer array nums​​​, return the minimum number of elements to remove to make
 * nums​​​ a mountain array.
 *
 * ! 3 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 10^9
 * ! It is guaranteed that you can make a mountain array out of nums.
 */

class Solution {
public:
    int minimumMountainRemovals(std::vector<int>& nums)
    {
        // LIS[i] = length of the LIS of nums[0:i] ending at nums[i]
        // LDS[i] = length of the LDS of nums[0:i] starting at nums[i]
        // if nums[i] is the peak of a mountain subarray
        // then num of elements = LIS[i] + LDS[i] - 1
        // thus, num of removes = n - (LIS[i] + LDS[i] - 1)
        const int n = nums.size();
        const auto LIS = helper(nums, false);
        const auto LDS = helper({nums.rbegin(), nums.rend()}, true);
        int result = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (LIS[i] >= 2 && LDS[i] >= 2) {
                result = std::min(result, n + 1 - LIS[i] - LDS[i]);
            }
        }
        return result;
    }

private:
    std::vector<int> helper(const std::vector<int>& nums, bool reverse)
    {
        // dp[i] = length of the LIS of nums[0:i] ending at nums[i]
        const int n = nums.size();
        std::vector<int> dp(n, 1);
        for (int i = 1; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] > nums[j]) {
                    dp[i] = std::max(dp[i], 1 + dp[j]);
                }
            }
        }
        if (reverse) {
            std::reverse(dp.begin(), dp.end());
        }
        return dp;
    }
};