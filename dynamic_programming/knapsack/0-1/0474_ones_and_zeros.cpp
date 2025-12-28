#include <algorithm>
#include <string>
#include <vector>

/**
 * You are given an array of binary strings strs and two integers m and n.
 *
 * Return the size of the largest subset of strs such that there are at most m 0's and n 1's in the
 * subset.
 *
 * A set x is a subset of a set y if all elements of x are also elements of y.
 *
 * ! 1 <= strs.length <= 600
 * ! 1 <= strs[i].length <= 100
 * ! strs[i] consists only of digits '0' and '1'.
 * ! 1 <= m, n <= 100
 */

class Solution {
public:
    int findMaxForm(std::vector<std::string>& strs, int m, int n)
    {
        return approach2(strs, m, n);
    }

private:
    int approach2(const std::vector<std::string>& strs, int m, int n)
    {
        const int sz = strs.size();
        std::vector<int> countZeros(sz);
        for (int i = 0; i < sz; ++i) {
            countZeros[i] = std::count_if(strs[i].begin(), strs[i].end(), [](const auto& c) { return c == '0'; });
        }
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= sz; ++i) {
            const int zeros = countZeros[i - 1];
            const int ones = strs[i - 1].size() - zeros;
            for (int p = m; p >= 0; --p) {
                for (int q = n; q >= 0; --q) {
                    if (p - zeros >= 0 && q - ones >= 0) {
                        dp[p][q] = std::max(dp[p][q], 1 + dp[p - zeros][q - ones]);
                    }
                }
            }
        }
        return dp[m][n];
    }

    int approach1(const std::vector<std::string>& strs, int m, int n)
    {
        // dp[i][p][q] = size of the largest subset of strs[0:i-1] such that
        // there are at most p 0's and q 1's
        const int sz = strs.size();
        std::vector<int> countZeros(sz);
        for (int i = 0; i < sz; ++i) {
            countZeros[i] = std::count_if(strs[i].begin(), strs[i].end(), [](const auto& c) { return c == '0'; });
        }
        std::vector<std::vector<std::vector<int>>> dp(sz + 1,
                                                      std::vector<std::vector<int>>(m + 1, std::vector<int>(n + 1, 0)));
        for (int i = 1; i <= sz; ++i) {
            const int zeros = countZeros[i - 1];
            const int ones = strs[i - 1].size() - zeros;
            for (int p = 0; p <= m; ++p) {
                for (int q = 0; q <= n; ++q) {
                    dp[i][p][q] = dp[i - 1][p][q];
                    if (p - zeros >= 0 && q - ones >= 0) {
                        dp[i][p][q] = std::max(dp[i][p][q], 1 + dp[i - 1][p - zeros][q - ones]);
                    }
                }
            }
        }
        return dp[sz][m][n];
    }
};