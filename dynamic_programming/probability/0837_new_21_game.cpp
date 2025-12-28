#include <vector>

/**
 * Alice plays the following game, loosely based on the card game "21".
 *
 * Alice starts with 0 points and draws numbers while she has less than k points. During each draw,
 * she gains an integer number of points randomly from the range [1, maxPts], where maxPts is an
 * integer. Each draw is independent and the outcomes have equal probabilities.
 *
 * Alice stops drawing numbers when she gets k or more points.
 *
 * Return the probability that Alice has n or fewer points.
 *
 * Answers within 10^-5 of the actual answer are considered accepted.
 *
 * ! 0 <= k <= n <= 10^4
 * ! 1 <= maxPts <= 10^4
 */

class Solution {
public:
    double new21Game(int n, int k, int maxPts)
    {
        if (k == 0 || k - 1 + maxPts <= n)
            return 1;

        // dp[i] = probability that Alice has i points
        // dp[i] = p * (dp[i-1] + ... + dp[i-maxPts]);
        std::vector<double> dp(n + 1, 0);
        dp[0] = 1;
        double sum = dp[0];
        const double p = 1.0 / maxPts;
        double result = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = p * sum;
            if (i < k) {
                sum += dp[i];
            } else {
                result += dp[i];
            }
            if (i >= maxPts) {
                sum -= dp[i - maxPts];
            }
        }
        return result;
    }
};