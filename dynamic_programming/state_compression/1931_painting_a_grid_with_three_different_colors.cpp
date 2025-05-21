#include <cmath>
#include <vector>

/**
 * You are given two integers m and n. Consider an m x n grid where each cell is initially white.
 * You can paint each cell red, green, or blue. All cells must be painted.
 *
 * Return the number of ways to color the grid with no two adjacent cells having the same color.
 * Since the answer can be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= m <= 5
 * ! 1 <= n <= 1000
 */

class Solution
{
public:
    int colorTheGrid(int m, int n)
    {
        std::vector<int> candidates; // valid color distributions of a single column
        for (int val = 0; val < std::pow(3, m); ++val) {
            if (isValid(val, m)) {
                candidates.push_back(val);
            }
        }
        // dp[i][j] = num of ways to fill columns[0:i] while the last column is candidates[j]
        std::vector<std::vector<long long>> dp(n, std::vector<long long>(candidates.size(), 0));
        for (int j = 0; j < candidates.size(); ++j) {
            dp[0][j] = 1;
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < candidates.size(); ++j) {
                for (int k = 0; k < candidates.size(); ++k) {
                    if (j == k)
                        continue;

                    if (isValid(candidates[j], candidates[k], m)) {
                        dp[i][j] = (dp[i][j] + dp[i - 1][k]) % kMod;
                    }
                }
            }
        }
        long long result = 0;
        for (int j = 0; j < candidates.size(); ++j) {
            result = (result + dp[n - 1][j]) % kMod;
        }
        return result;
    }

private:
    static constexpr long long kMod = 1e9 + 7;

    bool isValid(int val, int columns)
    {
        int prev = -1;
        for (int i = 0; i < columns; ++i) {
            if (prev == val % 3)
                return false;

            prev = val % 3;
            val /= 3;
        }
        return true;
    }

    bool isValid(int val1, int val2, int columns)
    {
        for (int i = 0; i < columns; ++i) {
            if (val1 % 3 == val2 % 3)
                return false;

            val1 /= 3;
            val2 /= 3;
        }
        return true;
    }
};
