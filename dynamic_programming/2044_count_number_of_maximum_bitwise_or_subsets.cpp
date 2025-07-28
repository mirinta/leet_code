#include <functional>
#include <vector>

/**
 * Given an integer array nums, find the maximum possible bitwise OR of a subset of nums and return
 * the number of different non-empty subsets with the maximum bitwise OR.
 *
 * An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero)
 * elements of b. Two subsets are considered different if the indices of the elements chosen are
 * different.
 *
 * The bitwise OR of an array a is equal to a[0] OR a[1] OR ... OR a[a.length - 1] (0-indexed).
 *
 * ! 1 <= nums.length <= 16
 * ! 1 <= nums[i] <= 10^5
 */

class Solution
{
public:
    int countMaxOrSubsets(std::vector<int>& nums) { return approach3(nums); }

private:
    int approach3(const std::vector<int>& nums)
    {
        int max = 0;
        for (const auto& v : nums) {
            max |= v;
        }
        const int n = nums.size();
        // dp[i][j] = num of subsets of nums[0:i-1] that the OR value of each subset is j
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(max + 1, 0));
        dp[0][0] = 1;
        for (int i = 1, prevMax = 0; i <= n; ++i) {
            dp[i] = dp[i - 1];
            for (int j = 0; j <= prevMax; ++j) {
                if ((j | nums[i - 1]) > max)
                    continue;

                dp[i][j | nums[i - 1]] += dp[i - 1][j];
            }
            prevMax |= nums[i - 1];
        }
        return dp[n][max];
    }

    int approach2(const std::vector<int>& nums)
    {
        int max = 0;
        for (const auto& v : nums) {
            max |= v;
        }
        const int n = nums.size();
        std::vector<std::vector<int>> memo(n, std::vector<int>(max + 1, -1));
        std::function<int(int, int)> dfs = [&](int i, int OR) {
            if (i >= n)
                return OR == max ? 1 : 0;

            if (memo[i][OR] != -1)
                return memo[i][OR];

            memo[i][OR] = dfs(i + 1, OR) + dfs(i + 1, OR | nums[i]);
            return memo[i][OR];
        };
        return dfs(0, 0);
    }

    int approach1(const std::vector<int>& nums)
    {
        int max = 0;
        for (const auto& v : nums) {
            max |= v;
        }
        const int n = nums.size();
        int result = 0;
        for (int mask = 1; mask < (1 << n); ++mask) {
            int OR = 0;
            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) {
                    OR |= nums[i];
                }
            }
            result += OR == max;
        }
        return result;
    }
};
