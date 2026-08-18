#include <array>
#include <vector>

/**
 * Alice and Bob continue their games with stones. There is a row of n stones, and each stone has an associated value.
 * You are given an integer array stones, where stones[i] is the value of the ith stone.
 *
 * Alice and Bob take turns, with Alice starting first. On each turn, the player may remove any stone from stones. The
 * player who removes a stone loses if the sum of the values of all removed stones is divisible by 3. Bob will win
 * automatically if there are no remaining stones (even if it is Alice's turn).
 *
 * Assuming both players play optimally, return true if Alice wins and false if Bob wins.
 *
 * ! 1 <= stones.length <= 10^5
 * ! 1 <= stones[i] <= 10^4
 */

class Solution {
public:
    bool stoneGameIX(std::vector<int>& stones)
    {
        std::array<int, 3> count{0, 0, 0};
        for (const auto& val : stones) {
            count[val % 3]++;
        }
        // Alice starts first and he can pick either 1 or 2
        // player = 0 for Alice, 1 for Bob
        for (const auto& val : {1, 2}) {
            if (count[val] == 0)
                continue;

            auto copy = count;
            copy[val]--;
            if (!dfs(copy, val, 1))
                return true;
        }
        return false;
    }

private:
    // check whether the 1st action player wins
    // player = 0 for Alice, 1 for Bob
    bool dfs(std::array<int, 3>& count, int sum, int player)
    {
        if (count[0] + count[1] + count[2] == 0)
            return player; // no stones, Bob wins

        // picking 0 is the optimal strategy of current player
        // it doesn't change the remainder
        if (count[0] > 0) {
            count[0]--;
            return !dfs(count, sum, 1 - player);
        }
        // if sum % 3 = 1, current player has to pick 1
        // if sum % 3 = 2, current player has to pick 2
        if (count[sum % 3] > 0) {
            count[sum % 3]--;
            return !dfs(count, sum + sum % 3, 1 - player);
        }
        return false;
    }
};