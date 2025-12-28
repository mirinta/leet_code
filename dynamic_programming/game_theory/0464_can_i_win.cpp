#include <vector>

/**
 * In the "100 game" two players take turns adding, to a running total, any integer from 1 to 10.
 * The player who first causes the running total to reach or exceed 100 wins.
 *
 * What if we change the game so that players cannot re-use integers?
 *
 * For example, two players might take turns drawing from a common pool of numbers from 1 to 15
 * without replacement until they reach a total >= 100.
 *
 * Given two integers maxChoosableInteger and desiredTotal, return true if the first player to move
 * can force a win, otherwise, return false. Assume both players play optimally.
 *
 * ! 1 <= maxChoosableInteger <= 20
 * ! 0 <= desiredTotal <= 300
 */

class Solution {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal)
    {
        const int actualTotal = (1 + maxChoosableInteger) * maxChoosableInteger / 2;
        if (actualTotal < desiredTotal)
            return false;

        // state compression
        // - index: 5 4 3 2 1 0
        // - state: 1 0 0 0 1 0 means num 1 and 5 are chosen
        // memorization:
        // - for state i, memo[i] = 0, 1, or 2
        // - 0 means state i is not calculated
        // - 1 means player1 loses the game with state i
        // - 2 means player2 wins the game with state i
        std::vector<int> memo(1 << (maxChoosableInteger + 1), 0);
        return dp(memo, 0, 0, maxChoosableInteger, desiredTotal);
    }

private:
    // return true if this player wins, otherwise false
    bool dp(std::vector<int>& memo, int state, int currentTotal, int maxChoosableInteger, int desiredTotal)
    {
        if (memo[state] == 1)
            return false;

        if (memo[state] == 2)
            return true;

        for (int i = 1; i <= maxChoosableInteger; ++i) {
            if ((state >> i) & 1)
                continue;

            if (currentTotal + i >= desiredTotal) {
                memo[state] = 2;
                return true;
            }

            // this player picks num i and checks whether the other player can deal with the new
            // state
            // - if the other player can't win, then num i brings this player victory
            // - otherwise, this player should try other nums
            if (!dp(memo, state | (1 << i), currentTotal + i, maxChoosableInteger, desiredTotal)) {
                memo[state] = 2;
                return true;
            }
        }
        // this player can't win after all options are checked, then he loses
        memo[state] = 1;
        return false;
    }
};