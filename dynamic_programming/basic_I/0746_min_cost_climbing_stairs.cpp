#include <vector>

/**
 * You are given an integer array "cost" where cost[i] is the cost of ith step on a staircase. Once
 * you pay the cost, you can either climb one for two steps.
 *
 * You can either start from the step with index 0, or the step with index 1.
 *
 * Return the minimum cost to reach the top of the floor.
 *
 * ! 2 <= cost.length <= 1000
 * ! 0 <= cost[i] <= 999
 */

class Solution {
public:
    int minCostClimbingStairs(std::vector<int>& cost)
    {
        return approach2(cost);
    }

private:
    // DP with space optimization, time O(N), space O(1)
    int approach2(const std::vector<int>& cost)
    {
        if (cost.empty())
            return -1;

        const int n = cost.size();
        int iPlus2 = cost[n - 1];
        int iPlus1 = cost[n - 2];
        for (int i = n - 3; i >= 0; --i) {
            const int dp = std::min(iPlus1, iPlus2) + cost[i];
            iPlus2 = iPlus1;
            iPlus1 = dp;
        }
        return std::min(iPlus1, iPlus2);
    }

    // DP, time O(N), space O(N)
    int approach1(const std::vector<int>& cost)
    {
        if (cost.empty())
            return -1;

        // stairs are [0,n-1], n is the target to reach
        // dp[i] = min cost of climbing from i to n
        const int n = cost.size();
        std::vector<int> dp(n, INT_MAX);
        dp[n - 1] = cost[n - 1];
        dp[n - 2] = cost[n - 2];
        for (int i = n - 3; i >= 0; --i) {
            dp[i] = std::min(dp[i + 1], dp[i + 2]) + cost[i];
        }
        return std::min(dp[0], dp[1]);
    }
};
