#include <array>
#include <vector>

/**
 * Alice and Bob play a game with piles of stones. There are an even number of piles arranged in a
 * row, and each pile has a positive integer number of stones piles[i].
 *
 * The objective of the game is to end with the most stones. The total number of stones across all
 * the piles is odd, so there are no ties.
 *
 * Alice and Bob take turns, with Alice starting first. Each turn, a player takes the entire pile of
 * stones either from the beginning or from the end of the row. This continues until there are no
 * more piles left, at which point the person with the most stones wins.
 *
 * Assuming Alice and Bob play optimally, return true if Alice wins the game, or false if Bob wins.
 *
 * ! 2 <= piles.length <= 500
 * ! piles.length is even.
 * ! 1 <= piles[i] <= 500
 * ! sum(piles[i]) is odd.
 */

class Solution {
public:
    bool stoneGame(std::vector<int>& piles)
    {
        const int n = piles.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + piles[i - 1];
        }
        std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1));
        const int Alice = dfs(memo, 0, n - 1, piles, presum);
        return Alice > presum.back() / 2;
    }

private:
    // max score that the 1st action player can get at the end of the game piles[lo:hi]
    int dfs(std::vector<std::vector<int>>& memo,
            int lo,
            int hi,
            const std::vector<int>& piles,
            const std::vector<int>& presum)
    {
        if (lo > hi)
            return 0;

        if (memo[lo][hi] != -1)
            return memo[lo][hi];

        // case 1: take piles[lo]
        const int case1 = piles[lo] + (presum[hi + 1] - presum[lo + 1]) - dfs(memo, lo + 1, hi, piles, presum);
        // case 2: take piles[hi]
        const int case2 = piles[hi] + (presum[hi] - presum[lo]) - dfs(memo, lo, hi - 1, piles, presum);
        return memo[lo][hi] = std::max(case1, case2);
    }
};