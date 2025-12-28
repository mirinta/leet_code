#include <algorithm>
#include <vector>

/**
 * You are given an array of n pairs "pairs" where pairs[i] = [left_i, right_i] and left_i <
 * right_i.
 *
 * A pair p2 = [c, d] follows a pair p1 = [a, b] if b < c. A chain of pairs can be formed in this
 * fashion.
 *
 * Return the length longest which can be formed.
 *
 * You do not need to use up all the given intervals. You can select pairs in any order.
 *
 * Example:
 * Input: pairs = [[1, 2], [2, 3], [3, 4]]
 * Output: 2
 * Explanation: The longest chain is [1, 2] -> [3, 4].
 *
 * ! n == pairs.length
 * ! 1 <= n <= 1000
 * ! -1000 <= left_i < right_i <= 1000
 */

class Solution {
public:
    int findLongestChain(std::vector<std::vector<int>>& pairs)
    {
        return approach2(pairs);
    }

private:
    // DP (LIS), time O(N^2), space O(N)
    int approach2(std::vector<std::vector<int>>& pairs)
    {
        const int n = pairs.size();
        std::sort(pairs.begin(), pairs.end(), [](const auto& v1, const auto& v2) { return v1[1] < v2[1]; });
        // dp[i] = max length of pair chain that ends with pairs[i]
        std::vector<int> dp(n, 1);
        int result = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (pairs[i][0] > pairs[j][1]) {
                    dp[i] = std::max(1 + dp[j], dp[i]);
                }
            }
            result = std::max(result, dp[i]);
        }
        return result;
    }

    // interval-scheduling, time O(NlogN), space O(logN)
    int approach1(std::vector<std::vector<int>>& pairs)
    {
        std::sort(pairs.begin(), pairs.end(), [](const auto& v1, const auto& v2) { return v1[1] < v2[1]; });
        int result = 1;
        int endingPoint = pairs[0][1];
        for (int i = 1; i < pairs.size(); ++i) {
            if (pairs[i][0] > endingPoint) {
                result++;
                endingPoint = pairs[i][1];
            }
        }
        return result;
    }
};