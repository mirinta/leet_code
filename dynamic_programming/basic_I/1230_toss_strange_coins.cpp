#include <vector>

/**
 * You have some coins. The i-th coin has a probability prob[i] of facing heads when tossed.
 *
 * Return the probability that the number of coins facing heads equals "target" if you toss every
 * coin exactly once.
 *
 * ! 1 <= prob.length <= 1000
 * ! 0 <= prob[i] <= 1
 * ! 0 <= target <= prob.length
 * ! Answers will be accepted as correct if they are within 10^-5 of the correct answer.
 */

class Solution {
public:
    double probabilityOfHeads(std::vector<double>& prob, int target)
    {
        return approach2(prob, target);
    }

private:
    // DP with space optimization, TC = O(N*T), SC = O(T)
    double approach2(const std::vector<double>& prob, int target)
    {
        const int n = prob.size();
        std::vector<double> dp(target + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = std::min(i, target); j >= 1; --j) {
                dp[j] = dp[j - 1] * prob[i - 1] + dp[j] * (1 - prob[i - 1]);
            }
            dp[0] *= 1 - prob[i - 1];
        }
        return dp[target];
    }

    // DP, TC = O(N*T), SC = O(N*T)
    double approach1(const std::vector<double>& prob, int target)
    {
        // dp[i][j] = prob that there are j coins facing heads after tossing coins[0:i)
        const int n = prob.size();
        std::vector<std::vector<double>> dp(n + 1, std::vector<double>(target + 1));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = dp[i - 1][0] * (1 - prob[i - 1]);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= std::min(i, target); ++j) {
                dp[i][j] = dp[i - 1][j] * (1 - prob[i - 1]) + dp[i - 1][j - 1] * prob[i - 1];
            }
        }
        return dp[n][target];
    }
};
