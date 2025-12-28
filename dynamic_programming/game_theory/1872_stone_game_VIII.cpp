#include <vector>

/**
 * Alice and Bob take turns playing a game, with Alice starting first.
 *
 * There are n stones arranged in a row. On each player's turn, while the number of stones is more
 * than one, they will do the following:
 *
 * Choose an integer x > 1, and remove the leftmost x stones from the row.
 * Add the sum of the removed stones' values to the player's score.
 * Place a new stone, whose value is equal to that sum, on the left side of the row.
 * The game stops when only one stone is left in the row.
 *
 * The score difference between Alice and Bob is (Alice's score - Bob's score). Alice's goal is to
 * maximize the score difference, and Bob's goal is the minimize the score difference.
 *
 * Given an integer array stones of length n where stones[i] represents the value of the ith stone
 * from the left, return the score difference between Alice and Bob if they both play optimally.
 *
 * ! n == stones.length
 * ! 2 <= n <= 10^5
 * ! -10^4 <= stones[i] <= 10^4
 */

class Solution {
public:
    int stoneGameVIII(std::vector<int>& stones)
    {
        // presum[i] = sum of nums[0:i-1)
        // dp[i] = max score difference between the 1st action player
        //         and the 2nd action player in a game with i piles of stones
        // dp[1] = 0, 1st action player must pick at least 2 piles of stones
        // dp[2] = presum[n] - dp[1], 1st action player picks all stones and put back a new stone
        // dp[3]:
        // - pick 2 piles, max diff = presum[n-1] - dp[2]
        // - pick 3 piles, max diff = presum[n] - dp[1]
        // - thus, dp[3] = std::max(presum[n-1] - dp[2], presum[n] - dp[1])
        // dp[4]:
        // - pick 2 piles, max diff = presum[n-2] - dp[3]
        // - pick 3 piles, max diff = presum[n-1] - dp[2]
        // - pick 4 piles, max diff = presum[n] - dp[1]
        // - thus, dp[4] = std::max(presum[n-2] - dp[3], presum[n-1] - dp[2], presum[n] - dp[1])
        // observation:
        // dp[4] = std::max(presum[n-2] - dp[3], std::max(presum[n-1] - dp[2], presum[n] - dp[1]))
        // dp[4] = std::max(presum[n-2] - dp[3], dp[3])
        // therefore, the transition function is dp[i] = std::max(presum[n-i+2] - dp[i-1], dp[i-1])
        const int n = stones.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + stones[i - 1];
        }
        std::vector<int> dp(n + 1);
        dp[1] = 0;
        dp[2] = presum[n] - dp[1];
        for (int i = 3; i <= n; ++i) {
            dp[i] = std::max(presum[n - i + 2] - dp[i - 1], dp[i - 1]);
        }
        return dp[n];
    }
};
