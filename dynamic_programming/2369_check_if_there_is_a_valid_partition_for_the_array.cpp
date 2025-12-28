#include <vector>

/**
 * You are given a 0-indexed integer array nums. You have to partition the array into one or more
 * contiguous subarrays.
 *
 * We call a partition of the array valid if each of the obtained subarrays satisfies one of the
 * following conditions:
 *
 * - The subarray consists of exactly 2 equal elements. For example, the subarray [2,2] is good.
 *
 * - The subarray consists of exactly 3 equal elements. For example, the subarray [4,4,4] is good.
 *
 * - The subarray consists of exactly 3 consecutive increasing elements, that is, the difference
 * between adjacent elements is 1. For example, the subarray [3,4,5] is good, but the subarray
 * [1,3,5] is not.
 *
 * Return true if the array has at least one valid partition. Otherwise, return false.
 */

class Solution {
public:
    bool validPartition(std::vector<int>& nums)
    {
        if (nums.size() < 2)
            return false;

        // dp[i] = the first i elements can be partitioned
        const int n = nums.size();
        nums.insert(nums.begin(), -1); // align index
        std::vector<bool> dp(n + 1, false);
        dp[0] = true;
        for (int i = 2; i <= n; ++i) {
            // case1: ... X X
            bool case1 = false;
            if (nums[i] == nums[i - 1]) {
                case1 = dp[i - 2];
            }
            // case 2: ... X X X
            bool case2 = false;
            if (i >= 3 && nums[i] == nums[i - 1] && nums[i] == nums[i - 2]) {
                case2 = dp[i - 3];
            }
            // case 3: ... X-2 X-1 X
            bool case3 = false;
            if (i >= 3 && nums[i] - 1 == nums[i - 1] && nums[i] - 2 == nums[i - 2]) {
                case3 = dp[i - 3];
            }
            dp[i] = case1 || case2 || case3;
        }
        return dp[n];
    }
};