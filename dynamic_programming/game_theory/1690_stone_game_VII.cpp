#include <vector>

/**
 * Alice and Bob take turns playing a game, with Alice starting first.
 *
 * There are n stones arranged in a row. On each player's turn, they can remove either the leftmost
 * stone or the rightmost stone from the row and receive points equal to the sum of the remaining
 * stones' values in the row. The winner is the one with the higher score when there are no stones
 * left to remove.
 *
 * Bob found that he will always lose this game (poor Bob, he always loses), so he decided to
 * minimize the score's difference. Alice's goal is to maximize the difference in the score.
 *
 * Given an array of integers stones where stones[i] represents the value of the ith stone from the
 * left, return the difference in Alice and Bob's score if they both play optimally.
 *
 * ! n == stones.length
 * ! 2 <= n <= 1000
 * ! 1 <= stones[i] <= 1000
 */

class Solution {
public:
    int stoneGameVII(std::vector<int>& stones)
    {
        const int n = stones.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + stones[i - 1];
        }
        std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1));
        return dp(memo, 0, n - 1, presum);
    }

private:
    // given game stones[lo:hi],
    // return the max score difference between the 1st action player and the 2nd action player
    int dp(std::vector<std::vector<int>>& memo, int lo, int hi, const std::vector<int>& presum)
    {
        if (lo > hi)
            return 0;

        if (memo[lo][hi] != -1)
            return memo[lo][hi];

        // case 1: remove stones[lo], score = sum of stones[lo+1:hi]
        const int diff1 = presum[hi + 1] - presum[lo + 1] - dp(memo, lo + 1, hi, presum);
        // case 2: remove stones[hi], score = sum of stones[lo:hi-1]
        const int diff2 = presum[hi] - presum[lo] - dp(memo, lo, hi - 1, presum);
        return memo[lo][hi] = std::max(diff1, diff2);
    }
};