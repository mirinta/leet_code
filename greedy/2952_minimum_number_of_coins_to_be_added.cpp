#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed integer array coins, representing the values of the coins available,
 * and an integer target.
 *
 * An integer x is obtainable if there exists a subsequence of coins that sums to x.
 *
 * Return the minimum number of coins of any value that need to be added to the array so that every
 * integer in the range [1, target] is obtainable.
 *
 * A subsequence of an array is a new non-empty array that is formed from the original array by
 * deleting some (possibly none) of the elements without disturbing the relative positions of the
 * remaining elements.
 *
 * ! 1 <= target <= 10^5
 * ! 1 <= coins.length <= 10^5
 * ! 1 <= coins[i] <= target
 */

class Solution {
public:
    int minimumAddedCoins(std::vector<int>& coins, int target)
    {
        // same as LC.330
        // assume we can obtain [0, x] using coins[0:i)
        // adding coins[i] to [0, x] gives us a new range [coins[i], coins[i]+x]
        // |------|  |--------------------|
        // 0      x  coins[i]    coins[i]+x
        // if coins[i] = x+1 or coins[i] <= x, then the two ranges are intersected and we can obtain
        // [0, coins[i]+x] otherwise, we have to add an new integer x+1 and update our obtainable
        // range to [0, 2x+1], then check coins[i] again repeat the above steps until x >= target
        const int n = coins.size();
        std::sort(coins.begin(), coins.end());
        int x = 0;
        int i = 0;
        int result = 0;
        while (x < target) {
            if (i < n && (coins[i] == x + 1 || coins[i] <= x)) {
                x += coins[i];
                i++;
            } else {
                x = 2 * x + 1; // add an new integer x+1 to coins
                result++;
            }
        }
        return result;
    }
};