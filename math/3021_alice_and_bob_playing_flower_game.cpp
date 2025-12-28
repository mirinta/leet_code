#include <utility>

/**
 * Alice and Bob are playing a turn-based game on a circular field surrounded by flowers. The circle
 * represents the field, and there are x flowers in the clockwise direction between Alice and Bob,
 * and y flowers in the anti-clockwise direction between them.
 *
 * The game proceeds as follows:
 *
 * 1. Alice takes the first turn.
 *
 * 2. In each turn, a player must choose either the clockwise or anti-clockwise direction and pick
 * one flower from that side.
 *
 * 3. At the end of the turn, if there are no flowers left at all, the current player captures their
 * opponent and wins the game.
 *
 * Given two integers, n and m, the task is to compute the number of possible pairs (x, y) that
 * satisfy the conditions:
 *
 * - Alice must win the game according to the described rules.
 *
 * - The number of flowers x in the clockwise direction must be in the range [1,n].
 *
 * - The number of flowers y in the anti-clockwise direction must be in the range [1,m].
 *
 * Return the number of possible pairs (x, y) that satisfy the conditions mentioned in the
 * statement.
 *
 * ! 1 <= n, m <= 10^5
 */

class Solution {
public:
    long long flowerGame(int n, int m)
    {
        // whoever picks the last flower wins
        // let k = total num of turns of the game that Alice wins
        //   kth turn: #flowers = 1, Alice picks it and wins
        // k-1th turn: #flowers = 2, Bob picks one of them
        // k-2th turn: #flowers = 3, Alice picks one of them
        // k-3th turn: #flowers = 4, Bob picks one of them
        // ...
        // observation: there are odd num of flowers in the beginning of Alice's turns
        // since Alice takes the first turn, then x+y must be an odd integer
        // x is in s1 = {1,2,...,n} and y is in s2 = {1,2,...,m}
        // case 1: x is even and y is odd => x+y is odd
        // case 2: x is odd and y is even => x+y is odd
        const auto [odd1, even1] = helper(n);
        const auto [odd2, even2] = helper(m);
        return odd1 * even2 + even1 * odd2;
    }

private:
    // return <num of odd integers in [1,n], num of even integers in [1,n]>
    std::pair<long long, long long> helper(int n)
    {
        return std::make_pair(n / 2, n - n / 2);
    }
};