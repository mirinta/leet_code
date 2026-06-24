#include <array>
#include <vector>

/**
 * You are given three integers n, l, and r.
 *
 * A ZigZag array of length n is defined as follows:
 *
 * - Each element lies in the range [l, r].
 *
 * - No two adjacent elements are equal.
 *
 * - No three consecutive elements from a strictly increasing or strictly decreasing sequence.
 *
 * Return the total number of valid ZigZag arrays.
 *
 * A sequence is said to be strictly increasing if each element is strictly greater than its previous one (if exists).
 *
 * A sequence is said to be strictly decreasing if each element is strictly smaller than its previous one (if exists).
 *
 * ! 3 <= n <= 2000
 * ! 1 <= l < r <= 2000
 */

class Solution {
public:
    int zigZagArrays(int n, int l, int r)
    {
        // let nums be a valid array
        // dp[i][0][j] = num of valid arrays of length i where the last number is j and nums[i] > nums[i-1]
        // dp[i][1][j] = num of valid arrays of length i where the last number is j and nums[i] < nums[i-1]
        //
        // dp[i][0][j] = sum of dp[i-1][1][x], where x is in the range of [l,j)
        // dp[i][1][j] = sum of dp[i-1][0][x], where x is in the range of (j,r]
        static constexpr int kMod = 1e9 + 7;
        std::array<std::vector<int>, 2> dp{};
        std::fill(dp.begin(), dp.end(), std::vector<int>(r + 1, 0));
        std::array<std::vector<int>, 2> sum{};
        std::fill(sum.begin(), sum.end(), std::vector<int>(r + 2, 0));
        for (int j = l; j <= r; ++j) {
            dp[0][j] = 1;
            dp[1][j] = 1;
            sum[0][j + 1] = (sum[0][j] + dp[0][j]) % kMod;
            sum[1][j + 1] = (sum[1][j] + dp[1][j]) % kMod;
        }
        auto query = [&](int index, int left, int right) {
            if (right < left)
                return 0;

            return (sum[index][right + 1] - sum[index][left] + kMod) % kMod;
        };
        for (int i = 2; i <= n; ++i) {
            for (int j = l; j <= r; ++j) {
                dp[0][j] = query(1, l, j - 1);
                dp[1][j] = query(0, j + 1, r);
            }
            std::fill(sum.begin(), sum.end(), std::vector<int>(r + 2, 0));
            for (int j = l; j <= r; ++j) {
                sum[0][j + 1] = (sum[0][j] + dp[0][j]) % kMod;
                sum[1][j + 1] = (sum[1][j] + dp[1][j]) % kMod;
            }
        }
        int result = 0;
        for (int j = l; j <= r; ++j) {
            result = (result + dp[0][j]) % kMod;
            result = (result + dp[1][j]) % kMod;
        }
        return result;
    }
};