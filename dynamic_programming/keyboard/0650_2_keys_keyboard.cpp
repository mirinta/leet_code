#include <vector>

/**
 * There is only one character 'A' on the screen of a notepad. You can perform one of two operations
 * on this notepad for each step:
 *
 * - Copy All: You can copy all the characters present on the screen (a partial copy is not
 * allowed).
 *
 * - Paste: You can paste the characters which are copied last time.
 *
 * Given an integer n, return the minimum number of operations to get the character 'A' exactly n
 * times on the screen.
 *
 * ! 1 <= n <= 1000
 */

class Solution {
public:
    int minSteps(int n)
    {
        // dp[i] = min operations to get exactly i 'A's
        // A A A A ... A copy paste ... paste
        // |<---#A=j-->|
        // |<-------------#A=i------------->|
        // let x = num of paste operations
        // i = j + x * j, x = i / j - 1 >= 1, then i / j >= 2
        // #operations = dp[j] + x + 1 = dp[j] + i / j
        std::vector<int> dp(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            dp[i] = i;
            for (int j = 1; j <= i / 2; ++j) {
                if (i % j == 0) {
                    dp[i] = std::min(dp[i], dp[j] + i / j);
                }
            }
        }
        return dp[n];
    }
};