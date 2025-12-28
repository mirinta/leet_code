#include <numeric>
#include <vector>

/**
 * Given an integer array "nums", return true if you can partition the array into two subsets such
 * that the sum of the elements in both subsets is equal or false otherwise.
 *
 * ! 1 <= nums.length <= 200
 * ! 1 <= nums[i] <= 100
 */

class Solution {
public:
    bool canPartition(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    bool approach2(const std::vector<int>& nums)
    {
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total % 2)
            return false;

        const int target = total / 2;
        std::vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (const auto& val : nums) {
            for (int j = target; j >= 1; --j) {
                if (j - val >= 0) {
                    dp[j] = dp[j] || dp[j - val];
                }
            }
        }
        return dp[target];
    }

    bool approach1(const std::vector<int>& nums)
    {
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total % 2)
            return false;

        const int target = total / 2;
        // dp[i][j] = whether it is possible to make up j using nums[0:i-1]
        const int n = nums.size();
        std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1, false));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = true;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= target; ++j) {
                const int diff = j - nums[i - 1];
                if (diff < 0) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][diff];
                }
            }
        }
        return dp[n][target];
    }
};
