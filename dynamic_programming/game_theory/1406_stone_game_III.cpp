#include <string>
#include <vector>

/**
 * Alice and Bob continue their games with piles of stones. There are several stones arranged in a
 * row, and each stone has an associated value which is an integer given in the array stoneValue.
 *
 * Alice and Bob take turns, with Alice starting first. On each player's turn, that player can take
 * 1, 2, or 3 stones from the first remaining stones in the row.
 *
 * The score of each player is the sum of the values of the stones taken. The score of each player
 * is 0 initially.
 *
 * The objective of the game is to end with the highest score, and the winner is the player with the
 * highest score and there could be a tie. The game continues until all the stones have been taken.
 *
 * Assume Alice and Bob play optimally.
 *
 * Return "Alice" if Alice will win, "Bob" if Bob will win, or "Tie" if they will end the game with
 * the same score.
 *
 * ! 1 <= stoneValue.length <= 5 * 104
 * ! -1000 <= stoneValue[i] <= 1000
 */

class Solution {
public:
    std::string stoneGameIII(std::vector<int>& stoneValue)
    {
        const int n = stoneValue.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + stoneValue[i - 1];
        }
        std::vector<int> memo(n, INT_MIN);
        const int Alice = dfs(memo, 0, n, presum);
        const int Bob = presum.back() - Alice;
        if (Alice == Bob)
            return "Tie";

        return Alice > Bob ? "Alice" : "Bob";
    }

private:
    // max score that the 1st action player can get at the end of the game nums[lo:n-1]
    int dfs(std::vector<int>& memo, int lo, int n, const std::vector<int>& presum)
    {
        if (lo >= n)
            return 0;

        if (memo[lo] != INT_MIN)
            return memo[lo];

        int result = INT_MIN;
        for (int take = 1; take <= std::min(3, n - lo); ++take) {
            const int score = presum[lo + take] - presum[lo];
            result = std::max(result, score + presum[n] - presum[lo + take] - dfs(memo, lo + take, n, presum));
        }
        return memo[lo] = result;
    }
};