#include <cmath>
#include <vector>

/**
 * Given an integer n, break it into the sum of k positive integers, where k >= 2, and maximize the
 * product of those integers.
 *
 * Return the maximum product you can get.
 *
 * ! 2 <= n <= 58
 */

class Solution {
public:
    int integerBreak(int n)
    {
        return approach2(n);
    }

private:
    // DP, time O(N^2), space O(N)
    int approach1(int n)
    {
        if (n < 2)
            return 0;

        // dp[i] = max product of breaking integer i
        // - find a breaking position j in the range [1, i/2]
        // - j>=1 because we need to break it into at least two positive integers
        // - j<=i/2 because the breaking parts are symmetric when j>i/2
        std::vector<int> dp(n + 1, 0);
        dp[2] = 1;
        for (int i = 3; i <= n; ++i) {
            for (int j = 1; j <= i / 2; ++j) {
                // choice1, continue to break the remaining part i-j
                // choice2, stop breaking
                dp[i] = std::max({dp[i], j * (i - j), j * dp[i - j]});
            }
        }
        return dp[n];
    }

    // Greedy, time O(N), space O(1)
    int approach2(int n)
    {
        // n = 2, max product = 1x1 = 1, smaller than n
        // n = 3, max product = 1x2 = 2, smaller than n
        // n = 4, max product = 2x2 = 4, equal to n
        // n = 5, max product = 2x3 = 6, greater than n
        // n = 6, max product = 3x3 = 9, greater than n
        // thus, break n into 3's as much as possible,
        // - if the remaining part is <= 4, we stop breaking the number,
        //   because it will make the product smaller
        if (n < 2)
            return 0;
        if (n == 2)
            return 1;
        if (n == 3)
            return 2;
        if (n == 4)
            return 4;
        int result = 1;
        while (n > 4) {
            result *= 3;
            n -= 3;
        }
        result *= n;
        return result;
    }
};