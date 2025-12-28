#include <vector>

/**
 * A train line going through a city has two routes, the regular route and the express route. Both
 * routes go through the same n + 1 stops labeled from 0 to n. Initially, you start on the regular
 * route at stop 0.
 *
 * You are given two 1-indexed integer arrays regular and express, both of length n. regular[i]
 * describes the cost it takes to go from stop i - 1 to stop i using the regular route, and
 * express[i] describes the cost it takes to go from stop i - 1 to stop i using the express route.
 *
 * You are also given an integer expressCost which represents the cost to transfer from the regular
 * route to the express route.
 *
 * Note that:
 *
 * - There is no cost to transfer from the express route back to the regular route.
 *
 * - You pay expressCost every time you transfer from the regular route to the express route.
 *
 * - There is no extra cost to stay on the express route.
 *
 * Return a 1-indexed array costs of length n, where costs[i] is the minimum cost to reach stop i
 * from stop 0.
 *
 * Note that a stop can be counted as reached from either route.
 *
 * ! n == regular.length == express.length
 * ! 1 <= n <= 10^5
 * ! 1 <= regular[i], express[i], expressCost <= 10^5
 */

class Solution {
public:
    std::vector<long long> minimumCosts(std::vector<int>& regular, std::vector<int>& express, int expressCost)
    {
        return approach2(regular, express, expressCost);
    }

private:
    // DP with space optimization, time O(N), space O(1)
    std::vector<long long> approach2(std::vector<int>& regular, std::vector<int>& express, int expressCost)
    {
        const int n = regular.size();
        long long onRegular = 0;
        long long onExpress = expressCost;
        std::vector<long long> result(n, 0);
        for (int i = 1; i <= n; ++i) {
            const long long backup = onRegular;
            onRegular = std::min(onRegular + regular[i - 1], onExpress + express[i - 1]);
            onExpress = std::min(backup + regular[i - 1] + expressCost, onExpress + express[i - 1]);
            result[i - 1] = std::min(onRegular, onExpress);
        }
        return result;
    }

    // DP, time O(N), space O(N)
    std::vector<long long> approach1(std::vector<int>& regular, std::vector<int>& express, int expressCost)
    {
        const int n = regular.size();
        // dp[i][0] = min cost from stop 0 to stop i, and the train stays on regular route at stop i
        // dp[i][1] = min cost from stop 0 to stop i, and the train stays on express route at stop i
        std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(2, INT_MAX));
        // at the beginning, the train stays on the regular route at stop 0
        dp[0][0] = 0;
        dp[0][1] = expressCost;
        // no cost to transfer from the express route back to the regular route.
        std::vector<long long> result(n, 0);
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::min(dp[i - 1][0] + regular[i - 1], dp[i - 1][1] + express[i - 1]);
            dp[i][1] = std::min(dp[i - 1][0] + regular[i - 1] + expressCost, dp[i - 1][1] + express[i - 1]);
            result[i - 1] = std::min(dp[i][0], dp[i][1]);
        }
        return result;
    }
};