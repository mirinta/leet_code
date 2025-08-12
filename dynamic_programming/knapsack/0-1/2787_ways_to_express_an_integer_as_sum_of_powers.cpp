#include <cmath>
#include <vector>

/**
 * Given two positive integers n and x.
 *
 * Return the number of ways n can be expressed as the sum of the xth power of unique positive
 * integers, in other words, the number of sets of unique integers [n1, n2, ..., nk] where n = n1^x
 * + n2^x + ... + nk^x.
 *
 * Since the result can be very large, return it modulo 10^9 + 7.
 *
 * For example, if n = 160 and x = 3, one way to express n is n = 23 + 33 + 53.
 *
 * ! 1 <= n <= 300
 * ! 1 <= x <= 5
 */

class Solution
{
public:
    int numberOfWays(int n, int x) { return approach2(n, x); }

private:
    static constexpr int kMod = 1e9 + 7;

    int approach2(int n, int x)
    {
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            const long long pow = std::pow(i, x);
            for (int j = n; j >= pow; --j) {
                dp[j] = (dp[j] + dp[j - pow]) % kMod;
            }
        }
        return dp[n];
    }

    int approach1(int n, int x)
    {
        // dp[i][j] = num of unique ways to make up j using integer [1:i]
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            const long long pow = std::pow(i, x);
            for (int j = 1; j <= n; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (j >= pow) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - pow]) % kMod;
                }
            }
        }
        return dp[n][n];
    }
};