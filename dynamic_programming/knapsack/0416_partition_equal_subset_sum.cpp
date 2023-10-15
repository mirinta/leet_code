#include <numeric>
#include <vector>

/**
 * Given an integer array "nums", return true if you can partition the array into two subsets such
 * that the sum of the elements in both subsets is equal or false otherwise.
 *
 * ! 1 <= nums.length <= 200
 * ! 1 <= nums[i] <= 100
 */

class Solution
{
public:
    bool canPartition(std::vector<int>& nums) { return approach2(nums); }

private:
    // DP with space optimization
    bool approach2(const std::vector<int>& nums)
    {
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total % 2 != 0)
            return false;

        const int n = nums.size();
        const int amount = total / 2;
        std::vector<bool> dp(amount + 1, false);
        dp[0] = true;
        for (int i = 1; i <= n; ++i) {
            // iterate j in reverse order,
            // then we don't need a "prev" array
            for (int j = amount; j >= 1; --j) {
                if (j - nums[i - 1] >= 0) {
                    dp[j] = dp[j] || dp[j - nums[i - 1]];
                }
            }
        }
        return dp[amount];
    }

    // DP
    bool approach1(const std::vector<int>& nums)
    {
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total % 2 != 0)
            return false;

        // 0-1 knapsack
        // dp[i][j] = whether we can make up amount j using nums[0:i)
        // base cases:
        // - dp[0][0] = true
        // - dp[0][j>0] = false, no numbers, no way to make up a positive j
        // - dp[i>0][0] = true
        const int n = nums.size();
        const int amount = total / 2;
        std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(amount + 1, false));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = true;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= amount; ++j) {
                if (j - nums[i - 1] < 0) {
                    // the ith value can't be used, use nums[0:i-1) to make up j
                    dp[i][j] = dp[i - 1][j];
                } else {
                    // option1: the ith value is not used, use nums[0:i-1) to make up j
                    // option2: the ith value is used, use nums[0:i-1) to make up the remaining
                    // amount
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        return dp[n][amount];
    }
};
