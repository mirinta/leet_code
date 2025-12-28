#include <algorithm>
#include <bitset>
#include <vector>

/**
 * You are given an integer array rewardValues of length n, representing the values of rewards.
 *
 * Initially, your total reward x is 0, and all indices are unmarked. You are allowed to perform the
 * following operation any number of times:
 *
 * - Choose an unmarked index i from the range [0, n - 1].
 *
 * - If rewardValues[i] is greater than your current total reward x, then add rewardValues[i] to x
 * (i.e., x = x + rewardValues[i]), and mark the index i.
 *
 * Return an integer denoting the maximum total reward you can collect by performing the operations
 * optimally.
 *
 * ! 1 <= rewardValues.length <= 5 * 10^4
 * ! 1 <= rewardValues[i] <= 5 * 10^4
 */

class Solution {
public:
    int maxTotalReward(std::vector<int>& rewardValues)
    {
        // based on the 2nd approach (DP with space optimization) of LC.3181
        std::sort(rewardValues.begin(), rewardValues.end());
        auto iter = std::unique(rewardValues.begin(), rewardValues.end());
        rewardValues.erase(iter, rewardValues.end());
        // rewardValues[i] <= max = 50000
        // then max score < 2 * max = 100000
        std::bitset<100000> dp;
        dp.set(0);
        for (const auto& val : rewardValues) {
            const auto shift = dp.size() - 2 * val;
            std::bitset<100000> mask;
            mask.set();
            mask = mask >> val << val;     // set mask[0:val) = 0
            mask = mask << shift >> shift; // set mask[2*val,N) = 0
            dp |= mask & (dp << val);
        }
        for (int j = 2 * rewardValues.back() - 1; j >= 0; --j) {
            if (dp[j])
                return j;
        }
        return -1;
    }
};