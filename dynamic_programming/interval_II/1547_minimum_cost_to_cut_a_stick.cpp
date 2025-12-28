#include <algorithm>
#include <vector>

/**
 * Given a wooden stick of length n units. The stick is labelled from 0 to n. For example, a stick
 * of length 6 is labelled as follows:
 *
 * 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7
 *
 * Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.
 *
 * You can change the order of the cuts as you wish.
 *
 * The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of
 * all cuts. When you cut a stick, it will be split into two smaller sticks (i.e. the sum of their
 * lengths is the length of the stick before the cut). Please refer to the first example for a
 * better explanation.
 *
 * ! 2 <= n <= 10^6
 * ! 1 <= cuts.length <= min(n - 1, 100)
 * ! 1 <= cuts[i] <= n - 1
 * ! All the integers in cuts array are distinct.
 */

class Solution {
public:
    int minCost(int n, std::vector<int>& cuts)
    {
        return approach2(n, cuts);
    }

private:
    int approach2(int n, std::vector<int>& cuts)
    {
        // dp[i][j] = min cost to achieve cuts[i:j]
        std::sort(cuts.begin(), cuts.end());
        cuts.insert(cuts.begin(), 0);
        cuts.push_back(n);
        const int m = cuts.size();
        std::vector<std::vector<int>> dp(m, std::vector<int>(m, INT_MAX));
        for (int i = 0; i + 1 < m; ++i) {
            dp[i][i + 1] = 0;
        }
        for (int length = 3; length <= m; ++length) {
            for (int i = 0; i + length - 1 < m; ++i) {
                const int j = i + length - 1;
                for (int k = i + 1; k < j; ++k) {
                    dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j] + cuts[j] - cuts[i]);
                }
            }
        }
        return dp[0][m - 1];
    }

    int approach1(int n, std::vector<int>& cuts)
    {
        std::sort(cuts.begin(), cuts.end());
        cuts.insert(cuts.begin(), 0);
        cuts.push_back(n);
        std::vector<std::vector<int>> memo(cuts.size(), std::vector<int>(cuts.size(), -1));
        return dfs(memo, 0, cuts.size() - 1, cuts);
    }

    int dfs(std::vector<std::vector<int>>& memo, int left, int right, const std::vector<int>& cuts)
    {
        if (left + 1 >= right)
            return 0;

        if (memo[left][right] != -1)
            return memo[left][right];

        int result = INT_MAX;
        for (int i = left + 1; i < right; ++i) {
            const int cost = dfs(memo, left, i, cuts) + dfs(memo, i, right, cuts) + cuts[right] - cuts[left];
            result = std::min(result, cost);
        }
        return memo[left][right] = result;
    }
};
