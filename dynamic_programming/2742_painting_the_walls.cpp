#include <vector>

/**
 * You are given two 0-indexed integer arrays, cost and time, of size n representing the costs and
 * the time taken to paint n different walls respectively. There are two painters available:
 *
 * - A paid painter that paints the ith wall in time[i] units of time and takes cost[i] units of
 * money.
 *
 * - A free painter that paints any wall in 1 unit of time at a cost of 0. But the free painter
 * can only be used if the paid painter is already occupied.
 *
 * Return the minimum amount of money required to paint the n walls.
 *
 * ! 1 <= cost.length <= 500
 * ! cost.length == time.length
 * ! 1 <= cost[i] <= 10^6
 * ! 1 <= time[i] <= 500
 */

class Solution {
public:
    int paintWalls(std::vector<int>& cost, std::vector<int>& time)
    {
        // the paid painter paints wall[i] in time[i] time and takes cost[i] money
        // while the paid painter is occupied, the free painter can pain time[i] walls
        // it implies that we can spent cost[i] money to paint 1+time[i] walls
        // dp[i][j] = min cost to paint wall[i:n) with j remaining walls
        const int n = cost.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= n; ++i) {
            dp[n][i] = INT_MAX / 2;
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 1; j <= n; ++j) {
                const int case1 = dp[i + 1][std::max(0, j - 1 - time[i])] + cost[i];
                const int case2 = dp[i + 1][j];
                dp[i][j] = std::min(case1, case2);
            }
        }
        return dp[0][n];
    }
};