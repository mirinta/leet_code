#include <vector>

/**
 * For an integer array nums, an inverse pair is a pair of integers [i, j] where 0 <= i < j <
 * nums.length and nums[i] > nums[j].
 *
 * Given two integers n and k, return the number of different arrays consisting of numbers from 1 to
 * n such that there are exactly k inverse pairs. Since the answer can be huge, return it modulo
 * 10^9 + 7.
 *
 * ! 1 <= n <= 1000
 * ! 0 <= k <= 1000
 */

class Solution {
public:
    int kInversePairs(int n, int k)
    {
        return approach2(n, k);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    // DP with space optimization, TC = O(NK), SC = O(K)
    int approach2(int n, int k)
    {
        std::vector<int> dp(k + 1, 0);
        dp[0] = 1;
        auto prev = dp;
        for (int i = 1; i <= n; ++i) {
            prev.assign(dp.begin(), dp.end());
            dp[0] = 1;
            for (int j = 1; j <= k; ++j) {
                dp[j] = (dp[j - 1] + prev[j]) % kMod;
                if (j - i >= 0) {
                    dp[j] = (dp[j] - prev[j - i] + kMod) % kMod;
                }
            }
        }
        return dp[k];
    }

    // DP, TC = O(NK), SC = O(NK)
    int approach1(int n, int k)
    {
        // dp[i][j] = num of different arrays consisting of numbers from 1 to i
        // such that there are exactly j inverse pairs
        //
        // use integer 1~i-1 to construct an array A = { (P1) X1 (P2) X2 (P3) X3 (P4) ... (Pi-1)
        // Xi-1 (Pi)} assume A contains X inverse pairs there are i positions {P1,...,Pi} to insert
        // integer i into A
        // - if we pick P1, then new array contains X + (i - 1) inverse pairs
        // - if we pick P2, then new array contains X + (i - 2) inverse pairs
        // - ...
        // - if we pick Pi, then new array contains X + 0 inverse pairs
        //
        // Eq1: dp[i][j] = dp[i-1][j-0] + dp[i-1][j-1] + ... + dp[i-1][j-(i-1)]
        // Eq2: dp[i][j-1] = dp[i-1][j-1] + dp[i-1][j-2] + ... + dp[i-1][j-1-(i-2)] +
        // dp[i-1][j-1-(i-1)] Eq1-Eq2: dp[i][j] = dp[i][j-1] + dp[i-1][j] - dp[i-1][j-i]
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % kMod;
                if (j - i >= 0) {
                    dp[i][j] = (dp[i][j] - dp[i - 1][j - i] + kMod) % kMod;
                }
            }
        }
        return dp[n][k];
    }
};