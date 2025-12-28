#include <vector>

/**
 * You are given three integers n, m and k. Consider the following algorithm to find the maximum
 * element of an array of positive integers:
 *
 * maximum_value = -1
 * maximum_index = -1
 * search_cost = 0
 * n = arr.length
 * for (i = 0; i < n; i++) {
 *     if (maximum_value < arr[i]) {
 *         maximum_value = arr[i]
 *         maximum_index = i
 *         search_cost = search_cost + 1
 *     }
 * }
 * return maximum_index
 *
 * You should build the array arr which has the following properties:
 *
 * - arr has exactly n integers.
 *
 * - 1 <= arr[i] <= m where (0 <= i < n).
 *
 * - After applying the mentioned algorithm to arr, the value search_cost is equal to k.
 *
 * Return the number of ways to build the array arr under the mentioned conditions. As the answer
 * may grow large, the answer must be computed modulo 10^9 + 7.
 *
 * ! 1 <= n <= 50
 * ! 1 <= m <= 100
 * ! 0 <= k <= n
 */

class Solution {
public:
    int numOfArrays(int N, int M, int K)
    {
        // dp[i][j][k] = num of arrays to build array[0:i],
        // and j is the maximum element of array[0:i],
        // and we use K search times to get the maximum value
        // - j is in the range [1:M]
        // case1: array[i] is the maximum element, i.e., array[i] = j
        // the maximum element of array[0:i-1] can be {1,2,...,j-1}
        // thus, dp[i][j][k] = dp[i-1][j-1][k-1] + dp[i-1][j-2][k-1] + ... + dp[i-1][1][k-1]
        // case2: j is the max element of array[0:i-1], and array[i] can be {1,2,...,j}
        // thus, dp[i][j][k] = dp[i-1][j][k] + ... + dp[i-1][j][k] = dp[i-1][j][k] * j
        constexpr int kMod = 1e9 + 7;
        long dp[N][M + 1][K + 1];
        std::memset(dp, 0, sizeof(dp));
        // base case: dp[0][j][1] = 1, only one element
        for (int j = 1; j <= M; ++j) {
            dp[0][j][1] = 1;
        }
        for (int i = 1; i < N; ++i) {
            for (int j = 1; j <= M; ++j) {
                for (int k = 1; k <= K; ++k) {
                    // case1:
                    for (int t = 1; t <= j - 1; ++t) {
                        dp[i][j][k] = (dp[i][j][k] + dp[i - 1][t][k - 1]) % kMod;
                    }
                    // case2:
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k] * j) % kMod;
                }
            }
        }
        int result = 0;
        for (int j = 1; j <= M; ++j) {
            result = (result + dp[N - 1][j][K]) % kMod;
        }
        return result;
    }
};
