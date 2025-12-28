#include <numeric>
#include <vector>

/**
 * You are given an integer array "nums" and an integer "target".
 *
 * You want to build an expression out of nums by adding one of the symbols '+' and '-' before each
 * integer in "nums" and then concatenate all the integers.
 *
 * - For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before '1' and concatenate
 * them to build the expression "+2-1".
 *
 * Return the number of different expressions that you can build, which evaluates to "target".
 *
 * ! 1 <= nums.length <= 20
 * ! 0 <= nums[i] <= 1000
 * ! 0 <= sum(nums[i]) <= 1000
 * ! -1000 <= target <= 1000
 */

class Solution {
public:
    int findTargetSumWays(std::vector<int>& nums, int target)
    {
        return approach2(nums, target);
    }

private:
    // DP with space optimization
    int approach2(const std::vector<int>& nums, int target)
    {
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total + target < 0 || (total + target) % 2)
            return 0;

        const int A = (total + target) / 2;
        std::vector<int> dp(A + 1, 0);
        dp[0] = 1;
        for (const auto& val : nums) {
            for (int j = A; j >= 0; --j) {
                if (j >= val) {
                    dp[j] += dp[j - val];
                }
            }
        }
        return dp[A];
    }

    // DP, knapsack
    int approach1(const std::vector<int>& nums, int target)
    {
        // A = numbers with '+' symbol
        // B = numbers with '-' symbol
        // A + B = total
        // A - B = target
        // A = (total + target) / 2
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total + target < 0 || (total + target) % 2)
            return 0;

        // dp[i][j] = num of ways to make up j using nums[0:i-1]
        const int A = (total + target) / 2;
        const int n = nums.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(A + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= A; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (j - nums[i - 1] >= 0) {
                    dp[i][j] += dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        return dp[n][A];
    }
};
