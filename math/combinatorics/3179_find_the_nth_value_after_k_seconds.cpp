#include <vector>

/**
 * You are given two integers n and k.
 *
 * Initially, you start with an array a of n integers where a[i] = 1 for all 0 <= i <= n - 1. After
 * each second, you simultaneously update each element to be the sum of all its preceding elements
 * plus the element itself. For example, after one second, a[0] remains the same, a[1] becomes a[0]
 * + a[1], a[2] becomes a[0] + a[1] + a[2], and so on.
 *
 * Return the value of a[n - 1] after k seconds.
 *
 * Since the answer may be very large, return it modulo 109 + 7.
 *
 * ! 1 <= n, k <= 1000
 */

long long fastPowMod(long long a, long long b, long long mod = 1e9 + 7)
{
    long long result = 1;
    long long base = a;
    while (b > 0) {
        if (b & 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        b >>= 1;
    }
    return result;
}

long long combinationsMod(long long m, long long n, long long mod = 1e9 + 7)
{
    std::vector<long long> factorial(m + 1, 1);
    for (long long i = 1; i <= m; ++i) {
        factorial[i] = factorial[i - 1] * i % mod;
    }
    std::vector<long long> invFactorial(m + 1);
    invFactorial[m] = fastPowMod(factorial[m], mod - 2, mod);
    for (long long i = m - 1; i >= 0; --i) {
        invFactorial[i] = invFactorial[i + 1] * (i + 1) % mod;
    }
    return factorial[m] * invFactorial[n] % mod * invFactorial[m - n] % mod;
}

class Solution {
public:
    int valueAfterKSeconds(int n, int k)
    {
        return approach4(n, k);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    // pascal triangle
    int approach4(int n, int k)
    {
        // answer(n,k) = combination(n+k-1, n-1)
        return combinationsMod(n + k - 1, n - 1);
    }

    // DP with space optimization
    int approach3(int n, int k)
    {
        std::vector<int> dp(n, 1);
        for (int t = 1; t <= k; ++t) {
            for (int i = 1; i < n; ++i) {
                dp[i] = (dp[i] + dp[i - 1]) % kMod;
            }
        }
        return dp[n - 1];
    }

    // DP
    int approach2(int n, int k)
    {
        // dp[t][i] = value of a[i] after t seconds
        std::vector<std::vector<int>> dp(k + 1, std::vector<int>(n));
        std::fill(dp[0].begin(), dp[0].end(), 1);
        for (int t = 1; t <= k; ++t) {
            dp[t][0] = 1;
        }
        for (int t = 1; t <= k; ++t) {
            for (int i = 1; i < n; ++i) {
                dp[t][i] = (dp[t - 1][i] + dp[t][i - 1]) % kMod;
            }
        }
        return dp[k][n - 1];
    }

    // simulation + prefix sum
    int approach1(int n, int k)
    {
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = i;
        }
        for (int t = 0; t < k; ++t) {
            auto prev = presum;
            for (int i = 0; i < n; ++i) {
                presum[i + 1] = (presum[i] + prev[i + 1]) % kMod;
            }
        }
        return (presum[n] - presum[n - 1] + kMod) % kMod;
    }
};