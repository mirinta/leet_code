#include <vector>

/**
 * 一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。
 *
 * 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
 */

class Solution {
public:
    int numWays(int n)
    {
        return approach2(n);
    }

private:
    int approach1(int n)
    {
        if (n <= 0)
            return n == 0 ? 1 : -1;

        // dp[i] = number of ways to climb i stairs
        // base cases: dp[1] and dp[0]
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        constexpr auto mod = 1e9 + 7;
        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
            if (dp[i] > mod) {
                dp[i] -= mod;
            }
        }
        return dp[n];
    }

    int approach2(int n)
    {
        // dp[i] is only dependent on dp[i-1] and dp[i-2]
        // thus, it is a Fibonacci Pattern
        if (n <= 1)
            return n >= 0 ? 1 : -1;

        int fibN = 0;
        int fibNMinusOne = 1;
        int fibNMinusTwo = 1;
        constexpr auto mod = 1e9 + 7;
        for (int i = 2; i <= n; ++i) {
            fibN = fibNMinusOne + fibNMinusTwo;
            if (fibN > mod) {
                fibN -= mod;
            }
            fibNMinusTwo = fibNMinusOne;
            fibNMinusOne = fibN;
        }
        return fibN;
    }
};