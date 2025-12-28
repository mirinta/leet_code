#include <vector>

/**
 * You are given an integer array nums. You are initially positioned at the array's first index, and
 * each element in the array represents your maximum jump length at that position.
 *
 * Return true if you can reach the last index, or false otherwise.
 *
 * ! 1 <= nums.length <= 10^4
 * ! 0 <= nums[i] <= 10^5
 */

class Solution {
public:
    bool canJump(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // Greedy, time O(N), space O(1)
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // assume we are at index n-2, then we can reach index n-1 as long as the allowed jump
        // length >= 1, it doesn't matter the reached index > n-1 thus, if we are at index i, we
        // always jump to the furthest index
        int furthest = 0;
        for (int i = 0; i < n; ++i) {
            if (i > furthest)
                return false; // we can't reach index i

            furthest = std::max(furthest, i + nums[i]);
        }
        return furthest >= n - 1;
    }

    // DP, time O(N), space O(N)
    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i] = whether we can reach the last index starting at index i
        std::vector<bool> dp(n, false);
        dp[n - 1] = true;
        for (int i = n - 2; i >= 0; --i) {
            for (int steps = std::min(nums[i], n - i - 1); steps > 0; --steps) {
                if (dp[i + steps]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[0];
    }
};