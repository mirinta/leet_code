#include <numeric>
#include <vector>

/**
 * You are given an array of integers stones where stones[i] is the weight of the ith stone.
 *
 * We are playing a game with the stones. On each turn, we choose any two stones and smash them
 * together. Suppose the stones have weights x and y with x <= y. The result of this smash is:
 *
 * - If x == y, both stones are destroyed, and
 *
 * - If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
 *
 * At the end of the game, there is at most one stone left.
 *
 * Return the smallest possible weight of the left stone. If there are no stones left, return 0.
 *
 * ! 1 <= stones.length <= 30
 * ! 1 <= stones[i] <= 100
 */

class Solution {
public:
    int lastStoneWeightII(std::vector<int>& stones)
    {
        return approach2(stones);
    }

private:
    int approach2(const std::vector<int>& stones)
    {
        const int total = std::accumulate(stones.begin(), stones.end(), 0);
        const int A = total / 2;
        std::vector<int> dp(A + 1, 0);
        for (const auto& val : stones) {
            for (int j = A; j >= 1; --j) {
                if (j - val >= 0) {
                    dp[j] = std::max(dp[j], val + dp[j - val]);
                }
            }
        }
        return std::abs(dp[A] * 2 - total);
    }

    int approach1(const std::vector<int>& stones)
    {
        // A + B = total
        // we want to minimize A - B
        // then both A and B need to be close to total/2
        const int n = stones.size();
        const int total = std::accumulate(stones.begin(), stones.end(), 0);
        const int A = total / 2;
        // dp[i][j] = max weight of putting stones[0:i-1] into a knapsack with capacity j
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(A + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= A; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (j - stones[i - 1] >= 0) {
                    dp[i][j] = std::max(dp[i][j], stones[i - 1] + dp[i - 1][j - stones[i - 1]]);
                }
            }
        }
        return std::abs(2 * dp[n][A] - total);
    }
};