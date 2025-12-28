#include <vector>

/**
 * Alice and Bob continue their games with piles of stones. There are a number of piles arranged in
 * a row, and each pile has a positive integer number of stones "piles[i]". The objective of the
 * game is to end with the most stones.
 *
 * Alice and Bob take turns, with Alice starting first. Initially, M = 1.
 *
 * On each player's turn, that player can take all the stones in the first X remaining piles, where
 * 1 <= X <= 2M. Then, we set M = max(M, X).
 *
 * The game continues until all the stones have been taken.
 *
 * Assuming Alice and Bob optimally, return the maximum number of stones Alice can get.
 *
 * ! 1 <= piles.length <= 100
 * ! 1 <= piles[i] <= 104
 */

class Solution {
public:
    int stoneGameII(std::vector<int>& piles)
    {
        const int n = piles.size();
        std::vector<int> presum(n + 1);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + piles[i - 1];
        }
        std::vector<std::vector<int>> memo(n, std::vector<int>(1 + n, -1));
        return dfs(memo, 0, 1, n, presum);
    }

private:
    // max score the first player can get in the game of piles[i:n-1]
    int dfs(std::vector<std::vector<int>>& memo, int i, int M, int n, const std::vector<int>& presum)
    {
        if (i == n)
            return 0;

        if (memo[i][M] != -1)
            return memo[i][M];

        int result = INT_MIN;
        for (int X = 1; X <= std::min(n - i, 2 * M); ++X) {
            const int score = presum[i + X] - presum[i];
            const int remaining = presum.back() - presum[i + X];
            result = std::max(result, score + remaining - dfs(memo, i + X, std::max(M, X), n, presum));
        }
        return memo[i][M] = result;
    }
};