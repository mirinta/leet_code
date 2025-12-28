#include <vector>

/**
 * You are given k identical eggs and you have access to a building with n floors labeled from 1 to
 * n.
 *
 * You know that there exists a floor f where 0 <= f <= n such that any egg dropped at a floor
 * higher than f will break, and any egg dropped at or below floor f will not break.
 *
 * Each move, you may take an unbroken egg and drop it from any floor x (where 1 <= x <= n). If the
 * egg breaks, you can no longer use it. However, if the egg does not break, you may reuse it in
 * future moves.
 *
 * Return the minimum number of moves that you need to determine with certainty what the value of f
 * is.
 *
 * ! 1 <= k <= 100
 * ! 1 <= n <= 10^4
 */

class Solution {
public:
    int superEggDrop(int k, int n)
    {
        return approach3(k, n);
    }

private:
    // Approach 3: time O(KN), space O(KN)
    int approach3(int k, int n)
    {
        // dp[i][j] = max num of floors we can check given i moves and j eggs
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
        int i = 0;
        while (dp[i][k] < n) {
            i++;
            for (int j = 1; j <= k; ++j) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] + 1;
            }
        }
        return i;
    }

    // Approach 2: time O(KNlogN), space (KN)
    int approach2(int k, int n)
    {
        // same dp definition as approach1
        std::vector<std::vector<int>> dp(k + 1, std::vector<int>(n + 1, 0));
        for (int j = 1; j <= n; ++j) {
            dp[1][j] = j;
        }
        for (int i = 1; i <= k; ++i) {
            dp[i][1] = 1;
        }
        for (int i = 2; i <= k; ++i) {
            for (int j = 2; j <= n; ++j) {
                // BINARY SEARCH
                int lo = 1;
                int hi = j;
                int min = INT_MAX;
                while (lo <= hi) {
                    const int mid = lo + (hi - lo) / 2;
                    const int broken = dp[i - 1][mid - 1];
                    const int notBroken = dp[i][j - mid];
                    if (broken > notBroken) {
                        hi = mid - 1;
                        min = std::min(min, broken + 1);
                    } else {
                        lo = mid + 1;
                        min = std::min(min, notBroken + 1);
                    }
                }
                dp[i][j] = min;
            }
        }
        return dp[k][n];
    }

    // Approach 1: TLE, time O(K*N^2), space O(KN)
    int approach1(int k, int n)
    {
        // dp[i][j] = min moves of determining f with i eggs and j floors
        std::vector<std::vector<int>> dp(k + 1, std::vector<int>(n + 1, 0));
        // base case:
        // - dp[1][j] = j, for j > 0, only one egg
        // - dp[i][1] = 1, for i > 0, only one floor
        for (int j = 1; j <= n; ++j) {
            dp[1][j] = j;
        }
        for (int i = 1; i <= k; ++i) {
            dp[i][1] = 1;
        }
        for (int i = 2; i <= k; ++i) {
            for (int j = 2; j <= n; ++j) {
                // BRUTE FORCE SEARCH
                int min = INT_MAX;
                for (int x = 1; x <= j; ++x) {
                    // we are standing at floor x with i eggs (1 <= x <= j),
                    // the problem is f(i, x)
                    // now, we drop an egg at floor x:
                    // - case1, the egg breaks, go downstairs and try x-1 floors with i-1 eggs,
                    //   i.e., #moves_1 = f(i-1, x-1) + 1
                    // - case2, the egg doesn't break, consider x as ground (floor 0)
                    //   and try the remaining j-x floors with i eggs,
                    //   i.e., #moves_2 = f(i, j-x) + 1
                    // both cases should be covered, so f(i, x) = max(#moves_1, #moves_2)
                    min = std::min(min, std::max(dp[i - 1][x - 1], dp[i][j - x]) + 1);
                }
                dp[i][j] = min;
            }
        }
        return dp[k][n];
    }
};
