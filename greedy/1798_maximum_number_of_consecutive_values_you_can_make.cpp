#include <algorithm>
#include <vector>

/**
 * You are given an integer array coins of length n which represents the n coins that you own. The
 * value of the ith coin is coins[i]. You can make some value x if you can choose some of your n
 * coins such that their values sum up to x.
 *
 * Return the maximum number of consecutive integer values that you can make with your coins
 * starting from and including 0.
 *
 * Note that you may have multiple coins of the same value.
 *
 * ! coins.length == n
 * ! 1 <= n <= 4 * 10^4
 * ! 1 <= coins[i] <= 4 * 10^4
 */

class Solution {
public:
    int getMaximumConsecutive(std::vector<int>& coins)
    {
        // similar to 2952
        const int n = coins.size();
        std::sort(coins.begin(), coins.end());
        int x = 0;
        // if we can make up [0,x] using coins[0:i)
        // adding coins[i] will make a new range [coins[i], x+coins[i]]
        // |----| |---------------------|
        // 0    x coins[i]     x+coins[i]
        // if coins[i] = x + 1 or coins[i] <= x, we can merge these two ranges into [0,x+coins[i]]
        for (int i = 0; i < n; ++i) {
            if (coins[i] > x + 1)
                break;

            x += coins[i];
        }
        return x + 1;
    }
};