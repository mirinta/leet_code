#include <vector>

/**
 * You are given an integer array nums. Two players are playing a game with this array: player 1 and
 * player 2.
 *
 * Player 1 and player 2 take turns, with player 1 starting first. Both players start the game with
 * a score of 0. At each turn, the player takes one of the numbers from either end of the array
 * (i.e., nums[0] or nums[nums.length - 1]) which reduces the size of the array by 1. The player
 * adds the chosen number to their score. The game ends when there are no more elements in the
 * array.
 *
 * Return true if Player 1 can win the game. If the scores of both players are equal, then player 1
 * is still the winner, and you should also return true. You may assume that both players are
 * playing optimally.
 *
 * ! 1 <= nums.length <= 20
 * ! 0 <= nums[i] <= 10^7
 */

class Solution {
public:
    bool predictTheWinner(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1));
        const int player1 = dfs(memo, 0, n - 1, nums, presum);
        return 2 * player1 >= presum.back();
    }

private:
    // max score that the 1st action player can get at the end of the game nums[lo:hi]
    int dfs(std::vector<std::vector<int>>& memo,
            int lo,
            int hi,
            const std::vector<int>& nums,
            const std::vector<int>& presum)
    {
        if (lo > hi)
            return 0;

        if (memo[lo][hi] != -1)
            return memo[lo][hi];

        const int case1 = nums[lo] + presum[hi + 1] - presum[lo + 1] - dfs(memo, lo + 1, hi, nums, presum);
        const int case2 = nums[hi] + presum[hi] - presum[lo] - dfs(memo, lo, hi - 1, nums, presum);
        return memo[lo][hi] = std::max(case1, case2);
    }
};