#include <array>
#include <vector>

/**
 * There is a row of "n" houses, where each house can be painted one of three colors: red, blue, or
 * green. The cost of painting each house with a certain color is different. You have to paint all
 * the houses such that no two adjacent houses have the same color.
 *
 * The cost of painting each house with a certain color is represented by an n x 3 cost matrix
 * costs.
 *
 * - for example, cost[0][0] is the cost of painting house[0] with the color red; cost[1][2] is the
 * cost of painting house 1 with color green, and so on...
 *
 * Return the minimum cost to paint all houses.
 *
 * ! costs.length == n
 * ! costs[i].length == 3
 * ! 1 <= n <= 100
 * ! 1 <= costs[i][j] <= 20
 */

class Solution {
public:
    int minCost(std::vector<std::vector<int>>& costs)
    {
        return approach2(costs);
    }

private:
    // DP with space optimization, TC = O(N), SC = O(1)
    int approach2(const std::vector<std::vector<int>>& costs)
    {
        const int n = costs.size();
        int red = 0;
        int blue = 0;
        int green = 0;
        for (int i = 1; i <= n; ++i) {
            const int prevRed = red;
            const int prevBlue = blue;
            const int prevGreen = green;
            red = costs[i - 1][0] + std::min(prevBlue, prevGreen);
            blue = costs[i - 1][1] + std::min(prevRed, prevGreen);
            green = costs[i - 1][2] + std::min(prevRed, prevBlue);
        }
        return std::min({red, blue, green});
    }

    // DP, TC = O(N), SC = O(N)
    int approach1(const std::vector<std::vector<int>>& costs)
    {
        // dp[i][0] = min cost to paint houses[0:i-1] and house[i-1] is painted with red
        // dp[i][1] = min cost to paint houses[0:i-1] and house[i-1] is painted with blue
        // dp[i][2] = min cost to paint houses[0:i-1] and house[i-1] is painted with green
        const int n = costs.size();
        std::vector<std::array<int, 3>> dp(n + 1, {0, 0, 0});
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = costs[i - 1][0] + std::min(dp[i - 1][1], dp[i - 1][2]);
            dp[i][1] = costs[i - 1][1] + std::min(dp[i - 1][0], dp[i - 1][2]);
            dp[i][2] = costs[i - 1][2] + std::min(dp[i - 1][0], dp[i - 1][1]);
        }
        return std::min({dp[n][0], dp[n][1], dp[n][2]});
    }
};