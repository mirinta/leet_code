#include <array>
#include <vector>

/**
 * You are painting a fence of n posts with k different colors. You must paint the posts following
 * these rules:
 *
 * - Every post must be painted exactly one color.
 *
 * - There cannot be three or more consecutive posts with the same color.
 *
 * Given the two integers n and k, return the number of ways you can paint the fence.
 *
 * ! 1 <= n <= 50
 * ! 1 <= k <= 10^5
 * ! The test cases are generated such that the answer is in the range [0, 231 - 1] for the given n
 * ! and k.
 */

class Solution {
public:
    int numWays(int n, int k)
    {
        return approach2(n, k);
    }

private:
    // DP with space optimization, TC = O(N), SC = O(1)
    int approach2(int n, int k)
    {
        if (n == 1)
            return k;

        int diff = k * (k - 1); // last two posts have different colors
        int same = k;           // last two posts have the same color
        for (int i = 2; i < n; ++i) {
            const int backup = diff;
            diff = (backup + same) * (k - 1);
            same = backup;
        }
        return diff + same;
    }

    // DP, TC = O(N), SC = O(N)
    int approach1(int n, int k)
    {
        if (n == 1)
            return k; // corner case, only one post

        // dp[i][0] = num of ways to paint posts[0:i] while the last two posts have different colors
        // dp[i][1] = num of ways to paint posts[0:i] while the last two posts have the same color
        // #NOTE# we need at least two posts
        std::vector<std::array<int, 2>> dp(n, {0, 0});
        dp[1] = {k * (k - 1), k}; // base case, two posts
        for (int i = 2; i < n; ++i) {
            // X X X i-2 i-1 i
            // case 1: posts[i] and posts[i-1] have different colors
            // - if posts[i-1] and posts[i-2] have the same color, post[i] has k-1 choices
            // - if posts[i-1] and posts[i-2] have different colors, posts[i] has k-1 choices
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) * (k - 1);
            // case 2: posts[i] and posts[i-1] have the same color
            // - posts[i-1] and posts[i-2] have different colors, posts[i] has only 1 choice
            dp[i][1] = dp[i - 1][0];
        }
        return dp[n - 1][0] + dp[n - 1][1];
    }
};
