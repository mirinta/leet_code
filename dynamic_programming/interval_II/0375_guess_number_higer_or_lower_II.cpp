#include <vector>

/**
 * We are playing the Guessing Game. The game will work as follows:
 *
 * 1. I pick a number between 1 and n.
 *
 * 2. You guess a number.
 *
 * 3. If you guess the right number, you win the game.
 *
 * 4. If you guess the wrong number, then I will tell you whether the number I picked is higher or
 * lower, and you will continue guessing.
 *
 * 5. Every time you guess a wrong number x, you will pay x dollars. If you run out of money, you
 * lose the game.
 *
 * Given a particular n, return the minimum amount of money you need to guarantee a win regardless
 * of what number I pick.
 *
 * ! 1 <= n <= 200
 */

class Solution {
public:
    int getMoneyAmount(int n)
    {
        // dp[i][j] = min amount of money to guarantee a win game of guessing a number in [i,j]
        // i X X X X X X X k-1 k k+1 X X X X X X X j
        // |<----dp[i][k]--->|   |<----dp[k][j]--->|
        // |<---------------dp[i][j]-------------->|
        //
        // guess a number k in the range [i,j]:
        // - base case: if i==j, only one number to choose, cost = 0
        // - base case: if j-i+1<=0, no way to choose a k, cost = INT_MAX
        //
        // if k is the target, cost = 0
        //
        // if k is wrong, we pay k and then guess a new number in [i,k-1] or in [k+1,j]
        // - cost = k + max(dp[i][k-1], dp[k+1][j])
        // - if k-1<i, dp[i][k-1] = 0, because the left part doesn't exist
        // - if k+1>j, dp[k+1][j-1] = 0, because the right part doesn't exist
        //
        // thus, dp[i][j] = min(k + max(dp[i][k-1], dp[k+1][j-1])), where k is in the range [i,j]
        std::vector<std::vector<long>> dp(1 + n, std::vector<long>(1 + n, INT_MAX));
        for (int i = n; i >= 1; --i) {
            for (int j = i; j <= n; ++j) {
                if (j - i + 1 <= 0) {
                    dp[i][j] = INT_MAX;
                    continue;
                }
                if (j - i == 0) {
                    dp[i][j] = 0;
                    continue;
                }
                for (int k = i; k <= j; ++k) {
                    const auto left = k - 1 >= i ? dp[i][k - 1] : 0;
                    const auto right = k + 1 <= j ? dp[k + 1][j] : 0;
                    dp[i][j] = std::min(dp[i][j], k + std::max(left, right));
                }
            }
        }
        return dp[1][n];
    }
};
