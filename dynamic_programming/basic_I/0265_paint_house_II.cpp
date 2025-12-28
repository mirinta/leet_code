#include <algorithm>
#include <vector>

/**
 * There are a row of "n" houses, each house can be painted with one of the "k" colors. The cost of
 * painting each house with a certain color is different. You have to paint all the houses such that
 * no two adjacent houses have the same color.
 *
 * The cost of painting each house with a certain color is represented by an "n x k" cost matrix
 * costs.
 *
 * - For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost
 * of painting house 1 with color 2, and so on...
 *
 * Return the minimum cost to paint all houses.
 *
 * ! costs.length == n
 * ! costs[i].length == k
 * ! 1 <= n <= 100
 * ! 2 <= k <= 20
 * ! 1 <= costs[i][j] <= 20
 * ! Could you solve it in O(nk) runtime?
 */

class Solution {
public:
    int minCostII(std::vector<std::vector<int>>& costs)
    {
        return approach2(costs);
    }

private:
    // DP with time and space optimization, time O(NK), time O(K)
    int approach2(const std::vector<std::vector<int>>& costs)
    {
        const int n = costs.size();
        const int k = costs[0].size();
        std::vector<int> dp(1 + k, INT_MAX);
        int prevMin = 0;
        int prevColor = 0; // 1-indexed
        int prevSecondMin = 0;
        for (int i = 1; i <= n; ++i) {
            int min = INT_MAX;
            int minColor = 0; // 1-indexed
            int secondMin = INT_MAX;
            for (int j = 1; j <= k; ++j) {
                dp[j] = costs[i - 1][j - 1] + (prevColor == j ? prevSecondMin : prevMin);
                if (dp[j] < min) {
                    minColor = j;
                    secondMin = min;
                    min = dp[j];
                } else if (dp[j] < secondMin) {
                    secondMin = dp[j];
                }
            }
            prevColor = minColor;
            prevMin = min;
            prevSecondMin = secondMin;
        }
        return *std::min_element(dp.begin(), dp.end());
    }

    // DP, time O(NK^2), time O(NK)
    int approach1(const std::vector<std::vector<int>>& costs)
    {
        const int n = costs.size();
        const int k = costs[0].size();
        // dp[i][j] = min cost to paint house[0:i) with k colors and the last house is painted with
        // color j base cases:
        // - dp[0][j] = 0
        std::vector<std::vector<int>> dp(1 + n, std::vector<int>(k + 1, INT_MAX));
        for (int j = 0; j <= k; ++j) {
            dp[0][j] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                for (int p = 1; p <= k; ++p) {
                    if (p == j)
                        continue;

                    dp[i][j] = std::min(dp[i][j], costs[i - 1][j - 1] + dp[i - 1][p]);
                }
            }
        }
        return *std::min_element(dp[n].begin(), dp[n].end());
    }
};