#include <vector>

/**
 * There is a test that has n types of questions. You are given an integer target and a 0-indexed 2D
 * integer array types where types[i] = [counti, marksi] indicates that there are counti questions
 * of the ith type, and each one of them is worth marksi points.
 *
 * Return the number of ways you can earn exactly target points in the exam. Since the answer may be
 * too large, return it modulo 10^9 + 7.
 *
 * Note that questions of the same type are indistinguishable.
 *
 * For example, if there are 3 questions of the same type, then solving the 1st and 2nd questions is
 * the same as solving the 1st and 3rd questions, or the 2nd and 3rd questions.
 *
 * ! 1 <= target <= 1000
 * ! n == types.length
 * ! 1 <= n <= 50
 * ! types[i].length == 2
 * ! 1 <= counti, marksi <= 50
 */

class Solution {
public:
    int waysToReachTarget(int target, std::vector<std::vector<int>>& types)
    {
        constexpr int kMod = 1e9 + 7;
        // dp[i][j] = num of ways to earn j points using types[0:i-1]
        const int n = types.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(target + 1, 0));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            const auto& count = types[i - 1][0];
            const auto& cost = types[i - 1][1];
            for (int j = 1; j <= target; ++j) {
                for (int k = 0; k <= count && j >= k * cost; ++k) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - k * cost]) % kMod;
                }
            }
        }
        return dp[n][target];
    }
};