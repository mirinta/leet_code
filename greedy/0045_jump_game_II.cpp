#include <vector>

/**
 * You are given a 0-indexed array of integers nums of length n. You are initially positioned at
 * nums[0].
 *
 * Each element nums[i] represents the maximum length of a forward jump from index i. In other
 * words, if you are at nums[i], you can jump to any nums[i + j] where:
 *
 * - 0 <= j <= nums[i] and
 *
 * - i + j < n
 *
 * Return the minimum number of jumps to reach nums[n - 1]. The test cases are generated such that
 * you can reach nums[n - 1].
 *
 * ! 1 <= nums.length <= 10^4
 * ! 0 <= nums[i] <= 1000
 * ! It's guaranteed that you can reach nums[n - 1].
 */

class Solution {
public:
    int jump(std::vector<int>& nums)
    {
        return approach3(nums);
    }

private:
    // time O(N), space O(1)
    int approach3(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int jumpTo = 0;
        int furthest = 0;
        int jumps = 0;
        for (int i = 0; i < n - 1; ++i) {
            furthest = std::max(furthest, i + nums[i]);
            if (i == jumpTo) {
                jumpTo = furthest;
                jumps++;
            }
        }
        return jumps;
    }

    // time O(N), space O(1)
    int approach2(const std::vector<int>& nums)
    {
        // assume we're at index i, the reachable range is [start, end]
        // - where start=i+1, end=i+nums[i]
        // for each j in the range [start, end], we can update the reachable range to [start', end']
        // - where start'=j+1, end'=max(j+nums[j]...)
        if (nums.size() == 1)
            return 0;

        const int n = nums.size();
        int start = 0;
        int end = 0;
        int jumps = 0;
        while (start <= end) {
            int furthest = end;
            for (int i = start; i <= end; ++i) {
                furthest = std::max(furthest, i + nums[i]);
                if (furthest >= n - 1)
                    return jumps + 1;
            }
            jumps++;
            start = end + 1;
            end = furthest;
        }
        return jumps;
    }

    // DP, time O(N^2), space O(N)
    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i] = starting from index 0, the min num of jumps to reach index i
        std::vector<int> dp(n, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            if (i + nums[i] >= n - 1)
                return std::min(dp[n - 1], 1 + dp[i]);

            for (int steps = 1; steps <= std::min(nums[i], n - i - 1); ++steps) {
                dp[i + steps] = std::min(dp[i + steps], 1 + dp[i]);
            }
        }
        return dp[n - 1] == INT_MAX ? -1 : dp[n - 1];
    }
};