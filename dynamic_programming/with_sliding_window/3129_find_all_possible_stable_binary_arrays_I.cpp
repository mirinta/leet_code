#include <array>
#include <vector>

/**
 * You are given 3 positive integers zero, one, and limit.
 *
 * A binary array arr is called stable if:
 *
 * - The number of occurrences of 0 in arr is exactly zero.
 *
 * - The number of occurrences of 1 in arr is exactly one.
 *
 * - Each subarray of arr with a size greater than limit must contain both 0 and 1.
 *
 * Return the total number of stable binary arrays.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= zero, one, limit <= 200
 */

class Solution {
public:
    int numberOfStableArrays(int zero, int one, int limit)
    {
        return approach2(zero, one, limit);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    // DP with sliding window, TC = O(zero*one), SC = O(zero*one)
    int approach2(int zero, int one, int limit)
    {
        std::vector<std::vector<std::array<int, 2>>> dp(zero + 1, std::vector<std::array<int, 2>>(one + 1, {0, 0}));
        dp[0][0] = {1, 1};
        std::vector<int> sum1(one + 1, 0);  // sum1[j] = dp[i-1][j][1] + ... + dp[i-limit][j][1]
        std::vector<int> sum0(zero + 1, 0); // sum0[i] = dp[i][j-1][0] + ... + dp[i][j-limit][0]
        for (int i = 0; i <= zero; ++i) {
            for (int j = 0; j <= one; ++j) {
                if (i > limit) {
                    sum1[j] = (sum1[j] - dp[i - limit - 1][j][1] + kMod) % kMod;
                }
                if (j > limit) {
                    sum0[i] = (sum0[i] - dp[i][j - limit - 1][0] + kMod) % kMod;
                }
                dp[i][j][0] = (dp[i][j][0] + sum1[j]) % kMod;
                dp[i][j][1] = (dp[i][j][1] + sum0[i]) % kMod;
                sum1[j] = (sum1[j] + dp[i][j][1]) % kMod;
                sum0[i] = (sum0[i] + dp[i][j][0]) % kMod;
            }
        }
        return (dp[zero][one][0] + dp[zero][one][1]) % kMod;
    }

    // DP, TC = O(zero*one*max(zero,one)), SC = O(zero*one)
    int approach1(int zero, int one, int limit)
    {
        // dp[i][j][0] = num of valid arrays that each array has i 1's and j 0's, and each array is
        // ending at 0
        // dp[i][j][1] = num of valid arrays that each array has i 1's and j 0's, and each array is
        // ending at 1
        std::vector<std::vector<std::array<int, 2>>> dp(zero + 1, std::vector<std::array<int, 2>>(one + 1, {0, 0}));
        dp[0][0] = {1, 1};
        for (int i = 0; i <= zero; ++i) {
            for (int j = 0; j <= one; ++j) {
                // X X X X 1 [0], 1 tailing zero, dp[i][j][0] += dp[i-1][j][1]
                // X X X 1 0 [0], 2 tailing zeros, dp[i][j][0] += dp[i-2][j][1]
                // X X 1 0 0 [0], 3 tailing zeros, dp[i][j][0] += dp[i-3][j][1]
                // ...
                // X 1 0 ... [0], limit tailing zeros, dp[i][j][0] += dp[i-limit][j][1]
                for (int k = 1; k <= std::min(i, limit); ++k) {
                    dp[i][j][0] = (dp[i][j][0] + dp[i - k][j][1]) % kMod;
                }
                // X X X X 0 [1], 1 tailing one, dp[i][j][1] += dp[i][j-1][0]
                // X X X 0 1 [1], 2 tailing ones, dp[i][j][1] += dp[i-1][j-2][0]
                // X X 0 1 1 [1], 3 tailing ones, dp[i][j][1] += dp[i-1][j-3][0]
                // ...
                // X 0 1 ... [1], limit tailing ones, dp[i][j][1] += dp[i-1][j-limit][0]
                for (int k = 1; k <= std::min(j, limit); ++k) {
                    dp[i][j][1] = (dp[i][j][1] + dp[i][j - k][0]) % kMod;
                }
            }
        }
        return (dp[zero][one][0] + dp[zero][one][1]) % kMod;
    }
};