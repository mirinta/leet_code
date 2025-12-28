#include <array>
#include <vector>

/**
 * You are a professional robber planning to rob houses along a street. Each house has a certain
 * amount of money stashed, the only constraint stopping you from robbing each of them is that
 * adjacent houses have security systems connected and it will automatically contact the police if
 * two adjacent houses were broken into on the same night.
 *
 * Given an integer array "nums" representing the amount of money of each house, return the maximum
 * amount of money you can rob tonight without alerting the police.
 *
 * ! 1 <= nums.length <= 100
 * ! 0 <= nums[i] <= 400
 */

class Solution {
public:
    int rob(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // DP with space optimization, TC = O(N), SC = O(1)
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int robbed = INT_MIN;
        int notRobbed = 0;
        for (int i = 1; i <= n; ++i) {
            const int backup = notRobbed;
            notRobbed = std::max(notRobbed, robbed);
            robbed = backup + nums[i - 1];
        }
        return std::max(notRobbed, robbed);
    }

    // DP, TC = O(N), SC = O(N)
    int approach1(const std::vector<int>& nums)
    {
        // dp[i][0] = max amount of money to rob the first i houses and the ith house is not robbed
        // dp[i][1] = max amount of money to rob the first i houses and the ith house is robbed
        // i is 1-indexed
        const int n = nums.size();
        std::vector<std::array<int, 2>> dp(n + 1, {0, 0});
        dp[0][1] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1]); // case 1: ith house is not robbed
            dp[i][1] = dp[i - 1][0] + nums[i - 1];           // case 2: ith house is robbed
        }
        return std::max(dp[n][0], dp[n][1]);
    }
};