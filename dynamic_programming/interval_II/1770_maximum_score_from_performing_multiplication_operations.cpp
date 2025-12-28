#include <functional>
#include <vector>

/**
 * You are given two 0-indexed integer arrays nums and multipliers of size n and m respectively,
 * where n >= m.
 *
 * You begin with a score of 0. You want to perform exactly m operations. On the ith operation
 * (0-indexed) you will:
 *
 * - Choose one integer x from either the start or the end of the array nums.
 *
 * - Add multipliers[i] * x to your score. Note that multipliers[0] corresponds to the first
 * operation, multipliers[1] to the second operation, and so on.
 *
 * - Remove x from nums.
 *
 * Return the maximum score after performing m operations.
 *
 * ! n == nums.length
 * ! m == multipliers.length
 * ! 1 <= m <= 300
 * ! m <= n <= 10^5
 * ! -1000 <= nums[i], multipliers[i] <= 1000
 */

class Solution {
public:
    int maximumScore(std::vector<int>& nums, std::vector<int>& multipliers)
    {
        return approach3(nums, multipliers);
    }

private:
    // DP with space optimization, TC = O(MN), SC = O(M)
    int approach3(const std::vector<int>& nums, const std::vector<int>& multipliers)
    {
        const int n = nums.size();
        const int m = multipliers.size();
        std::vector<int> dp(m + 1, 0);
        for (int i = 1; i <= m; ++i) {
            dp[i] = dp[i - 1] + multipliers[i - 1] * nums[n - i];
        }
        int result = dp[m];
        for (int i = 1; i <= m; ++i) {
            dp[0] += multipliers[i - 1] * nums[i - 1];
            for (int j = 1; i + j <= m; ++j) {
                const int k = i + j;
                const int case1 = multipliers[k - 1] * nums[i - 1] + dp[j];
                const int case2 = multipliers[k - 1] * nums[n - j] + dp[j - 1];
                dp[j] = std::max(case1, case2);
            }
            result = std::max(result, dp[m - i]);
        }
        return result;
    }

    // DP (bottom-up), TC = O(MN), SC = O(MN)
    int approach2(const std::vector<int>& nums, const std::vector<int>& multipliers)
    {
        // dp[i][j] = max score after choosing i integers from the start and j integers from the end
        const int n = nums.size();
        const int m = multipliers.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(m + 1, INT_MIN));
        dp[0][0] = 0;
        for (int i = 1; i <= m; ++i) {
            dp[i][0] = dp[i - 1][0] + multipliers[i - 1] * nums[i - 1];
            dp[0][i] = dp[0][i - 1] + multipliers[i - 1] * nums[n - i];
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; i + j <= m; ++j) {
                const int k = i + j;
                const int case1 = multipliers[k - 1] * nums[i - 1] + dp[i - 1][j];
                const int case2 = multipliers[k - 1] * nums[n - j] + dp[i][j - 1];
                dp[i][j] = std::max(case1, case2);
            }
        }
        int result = INT_MIN;
        for (int i = 0; i <= m; ++i) {
            result = std::max(result, dp[i][m - i]);
        }
        return result;
    }

    // DP (top-down), TC = O(MN), SC = O(MN)
    int approach1(const std::vector<int>& nums, const std::vector<int>& multipliers)
    {
        const int n = nums.size();
        const int m = multipliers.size();
        std::vector<std::vector<int>> memo(n, std::vector<int>(m, INT_MIN));
        return dfs(memo, 0, 0, nums, multipliers);
    }

    // 0 X X X left-1 left X X X X right right+1 X X n-1
    // |<--removed->|                    |<--removed-->|
    int dfs(std::vector<std::vector<int>>& memo,
            int left,
            int i,
            const std::vector<int>& nums,
            const std::vector<int>& multipliers)
    {
        if (i == multipliers.size())
            return 0;

        if (memo[left][i] != INT_MIN)
            return memo[left][i];

        const int right = nums.size() - 1 - i + left;
        const int case1 = nums[left] * multipliers[i] + dfs(memo, left + 1, i + 1, nums, multipliers);
        const int case2 = nums[right] * multipliers[i] + dfs(memo, left, i + 1, nums, multipliers);
        return memo[left][i] = std::max(case1, case2);
    }
};