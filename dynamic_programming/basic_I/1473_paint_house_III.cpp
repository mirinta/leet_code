#include <vector>

/**
 * There is a row of m houses in a small city, each house must be painted with one of the n colors
 * (labeled from 1 to n), some houses that have been painted last summer should not be painted
 * again.
 *
 * A neighborhood is a maximal group of continuous houses that are painted with the same color.
 *
 * - For example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods [{1}, {2,2}, {3,3}, {2},
 * {1,1}].
 *
 * Given an array houses, an m x n matrix cost and an integer target where:
 *
 * - houses[i]: is the color of the house i, and 0 if the house is not painted yet.
 *
 * - cost[i][j]: is the cost of paint the house i with the color j + 1.
 *
 * Return the minimum cost of painting all the remaining houses in such a way that there are exactly
 * target neighborhoods. If it is not possible, return -1.
 *
 * ! m == houses.length == cost.length
 * ! n == cost[i].length
 * ! 1 <= m <= 100
 * ! 1 <= n <= 20
 * ! 1 <= target <= m
 * ! 0 <= houses[i] <= n
 * ! 1 <= cost[i][j] <= 10^4
 */

class Solution {
public:
    int minCost(std::vector<int>& houses, std::vector<std::vector<int>>& cost, int m, int n, int target)
    {
        // dp[i][j][k] = min cost of painting houses[0:i-1] with exactly j neighborhoods
        // and houses[i-1] is painted in color k
        std::vector<std::vector<std::vector<int>>> dp(
            m + 1, std::vector<std::vector<int>>(target + 1, std::vector<int>(n + 1, INT_MAX / 2)));
        if (houses[0] != 0) {
            dp[1][1][houses[0]] = 0;
        } else {
            for (int k = 1; k <= n; ++k) {
                dp[1][1][k] = cost[0][k - 1];
            }
        }
        for (int i = 1; i <= m; ++i) {
            const auto& curr = houses[i - 1];
            for (int j = 1; j <= target; ++j) {
                if (curr != 0) {
                    dp[i][j][curr] = std::min(dp[i][j][curr], dp[i - 1][j][curr]);
                    for (int k = 1; k <= n; ++k) {
                        if (curr == k)
                            continue;

                        dp[i][j][curr] = std::min(dp[i][j][curr], dp[i - 1][j - 1][k]);
                    }
                } else {
                    for (int k = 1; k <= n; ++k) {
                        dp[i][j][k] = std::min(dp[i][j][k], dp[i - 1][j][k] + cost[i - 1][k - 1]);
                        for (int k0 = 1; k0 <= n; ++k0) {
                            if (k0 == k)
                                continue;

                            dp[i][j][k] = std::min(dp[i][j][k], dp[i - 1][j - 1][k0] + cost[i - 1][k - 1]);
                        }
                    }
                }
            }
        }
        int result = INT_MAX / 2;
        for (int k = 1; k <= n; ++k) {
            result = std::min(result, dp[m][target][k]);
        }
        return result == INT_MAX / 2 ? -1 : result;
    }
};