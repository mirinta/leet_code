#include <vector>

/**
 * There are n piles of stones arranged in a row. The ith pile has stones[i] stones.
 *
 * A move consists of merging exactly k consecutive piles into one pile, and the cost of this move
 * is equal to the total number of stones in these k piles.
 *
 * Return the minimum cost to merge all piles of stones into one pile. If it is impossible, return
 * -1.
 *
 * ! n == stones.length
 * ! 1 <= n <= 30
 * ! 1 <= stones[i] <= 100
 * ! 2 <= k <= 30
 */

class Solution {
public:
    int mergeStones(std::vector<int>& stones, int k)
    {
        // Each time we merge k piles into 1 pile,
        // the number of piles decreases by k-1.
        // Assume we have N piles at the beginning.
        // If we can finally merge them into 1 pile,
        // the total decrement is N-1.
        // Thus, the problem is solvable if and only if (N-1)%(k-1) equals 0.
        const int n = stones.size();
        if ((n - 1) % (k - 1) != 0)
            return -1;

        std::vector<int> prefixSum(1 + n, 0);
        for (int i = 1; i <= n; ++i) {
            prefixSum[i] = prefixSum[i - 1] + stones[i - 1];
        }
        // To get the final 1 pile, we need to merge N piles into k piles first.
        // dp[i][j][p] = min cost to merge stones[i:j] into p piles
        // i ................ x x+1 ................. j
        // |<-merge to 1 pile>| |<-merge to p-1 pile->|
        std::vector<std::vector<std::vector<int>>> dp(
            n, std::vector<std::vector<int>>(n, std::vector<int>(k + 1, INT_MAX)));
        for (int i = 0; i < n; ++i) {
            dp[i][i][1] = 0;
        }
        for (int length = 2; length <= n; ++length) {
            for (int i = 0; i + length - 1 < n; ++i) {
                const int j = i + length - 1;
                for (int p = 2; p <= k; ++p) {
                    if (p > length)
                        continue;

                    for (int x = i; x < j; ++x) {
                        if (dp[i][x][1] == INT_MAX || dp[x + 1][j][p - 1] == INT_MAX)
                            continue;

                        dp[i][j][p] = std::min(dp[i][j][p], dp[i][x][1] + dp[x + 1][j][p - 1]);
                    }
                }
                if (dp[i][j][k] == INT_MAX)
                    continue;

                dp[i][j][1] = dp[i][j][k] + prefixSum[j + 1] - prefixSum[i];
            }
        }
        return dp[0][n - 1][1];
    }
};
