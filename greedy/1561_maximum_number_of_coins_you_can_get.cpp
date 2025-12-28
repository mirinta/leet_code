#include <algorithm>
#include <vector>

/**
 * There are 3n piles of coins of varying size, you and your friends will take piles of coins as
 * follows:
 *
 * - In each step, you will choose any 3 piles of coins (not necessarily consecutive).
 *
 * - Of your choice, Alice will pick the pile with the maximum number of coins.
 *
 * - You will pick the next pile with the maximum number of coins.
 *
 * - Your friend Bob will pick the last pile.
 *
 * - Repeat until there are no more piles of coins.
 *
 * Given an array of integers piles where piles[i] is the number of coins in the ith pile.
 *
 * Return the maximum number of coins that you can have.
 *
 * ! 3 <= piles.length <= 10^5
 * ! piles.length % 3 == 0
 * ! 1 <= piles[i] <= 10^4
 */

class Solution {
public:
    int maxCoins(std::vector<int>& piles)
    {
        const int n = piles.size() / 3;
        std::sort(piles.begin(), piles.end(), std::greater());
        int result = 0;
        for (int i = 1; i <= 1 + (n - 1) * 2; i += 2) {
            result += piles[i];
        }
        return result;
    }
};