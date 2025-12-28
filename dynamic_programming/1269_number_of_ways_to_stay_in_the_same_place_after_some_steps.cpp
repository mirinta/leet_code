#include <vector>

/**
 * You have a pointer at index 0 in an array of size arrLen. At each step, you can move 1 position
 * to the left, 1 position to the right in the array, or stay in the same place (The pointer should
 * not be placed outside the array at any time).
 *
 * Given two integers steps and arrLen, return the number of ways such that your pointer is still at
 * index 0 after exactly steps steps. Since the answer may be too large, return it modulo 10^9 + 7.
 *
 * ! 1 <= steps <= 500
 * ! 1 <= arrLen <= 10^6
 */

class Solution {
public:
    int numWays(int steps, int arrLen)
    {
        return approach2(steps, arrLen);
    }

private:
    // DP with space optimization, time (NM), space O(M)
    // N = steps, M = min(steps, arrLen)
    int approach2(int steps, int arrLen)
    {
        constexpr int kMod = 1e9 + 7;
        arrLen = std::min(steps, arrLen);
        std::vector<long> dp(arrLen, 0);
        dp[0] = 1;
        std::vector<long> prev(arrLen, 0);
        for (int i = 1; i <= steps; ++i) {
            prev = dp;
            for (int j = 0; j < arrLen; ++j) {
                const auto case1 = prev[j];
                const auto case2 = j - 1 >= 0 ? prev[j - 1] : 0;
                const auto case3 = j + 1 < arrLen ? prev[j + 1] : 0;
                dp[j] = (case1 + case2 + case3) % kMod;
            }
        }
        return dp[0];
    }

    // DP, time (NM), space O(NM)
    // N = steps, M = min(steps, arrLen)
    int approach1(int steps, int arrLen)
    {
        constexpr int kMod = 1e9 + 7;
        arrLen = std::min(steps, arrLen);
        // dp[i][j] = num of ways to reach index 0 from index j with exatcly i steps
        std::vector<std::vector<long>> dp(steps + 1, std::vector<long>(arrLen, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= steps; ++i) {
            for (int j = 0; j < arrLen; ++j) {
                const auto case1 = dp[i - 1][j];                          // stay
                const auto case2 = j - 1 >= 0 ? dp[i - 1][j - 1] : 0;     // reach j from j-1, i.e. move right
                const auto case3 = j + 1 < arrLen ? dp[i - 1][j + 1] : 0; // reach j from j+1, i.e., move left
                dp[i][j] = (case1 + case2 + case3) % kMod;
            }
        }
        return dp[steps][0];
    }
};