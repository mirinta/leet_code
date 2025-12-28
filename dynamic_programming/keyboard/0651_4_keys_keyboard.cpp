#include <vector>

/**
 * Imagine you have a special keyboard with the following keys:
 *
 * - A: Print one 'A' on the screen.
 *
 * - Ctrl-A: Select the whole screen.
 *
 * - Ctrl-C: Copy selection to buffer.
 *
 * - Ctrl-V: Print buffer on screen appending it after what has already been printed.
 *
 * Given an integer n, return the maximum number of 'A' you can print on the screen with at most n
 * presses on the keys.
 *
 * ! 1 <= n <= 50
 */

class Solution {
public:
    int maxA(int n)
    {
        // dp[i] = max num of 'A' we can print with at most i presses
        // X X X j Ctrl-A Ctrl-C j+3 X X X X X X i
        //                       |<--all Ctrl-V->|
        // total letters = dp[j] + (i-j-2) * dp[j]
        std::vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            dp[i] = i;
            for (int j = i - 3; j >= 0; --j) {
                dp[i] = std::max(dp[i], dp[j] * (i - j - 2) + dp[j]);
            }
        }
        return dp[n];
    }
};