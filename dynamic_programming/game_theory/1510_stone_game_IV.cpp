#include <vector>

/**
 * Alice and Bob take turns playing a game, with Alice starting first.
 *
 * Initially, there are n stones in a pile. On each player's turn, that player makes a move
 * consisting of removing any non-zero square number of stones in the pile.
 *
 * Also, if a player cannot make a move, he/she loses the game.
 *
 * Given a positive integer n, return true if and only if Alice wins the game otherwise return
 * false, assuming both players play optimally.
 *
 * ! 1 <= n <= 10^5
 */

class Solution {
public:
    bool winnerSquareGame(int n)
    {
        std::vector<int> memo(n + 1, -1);
        return dfs(memo, n);
    }

private:
    // whether the 1st action player can win the game that has n stones
    bool dfs(std::vector<int>& memo, int n)
    {
        if (n == 0)
            return false;

        if (n == 1)
            return true;

        if (memo[n] != -1)
            return memo[n];

        for (int remove = 1; remove * remove <= n; ++remove) {
            if (!dfs(memo, n - remove * remove))
                return memo[n] = true;
        }
        return memo[n] = false;
    }
};