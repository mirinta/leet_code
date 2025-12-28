#include <vector>

/**
 * Given an integer n, return the least number of perfect square numbers that sum to n.
 *
 * A perfect square is an integer that is the square of an integer; in other words, it is the
 * product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and
 * 11 are not.
 *
 * ! 1 <= n <= 10^4
 */

class Solution {
public:
    int numSquares(int n)
    {
        // dp[i] = min num of perfect square numbers that sum to i
        std::vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                dp[i] = std::min(dp[i], 1 + dp[i - j * j]);
            }
        }
        return dp[n];
    }
};
