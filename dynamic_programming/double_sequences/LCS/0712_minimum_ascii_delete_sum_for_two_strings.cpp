#include <string>
#include <vector>

/**
 * Given two strings s1 and s2, return the lowest ASCII sum of deleted characters to make two
 * strings equal.
 *
 * ! 1 <= s1.length, s2.length <= 1000
 * ! s1 and s2 consist of lowercase English letters.
 */

class Solution {
public:
    int minimumDeleteSum(std::string s1, std::string s2)
    {
        return approach2(s1, s2);
    }

private:
    int approach2(const std::string& s1, const std::string& s2)
    {
        const int n = s2.size();
        std::vector<int> dp(n + 1, 0);
        for (int j = 1; j <= n; ++j) {
            dp[j] = dp[j - 1] + s2[j - 1];
        }
        for (const auto& c1 : s1) {
            auto prev = dp;
            dp[0] = prev[0] + c1;
            for (int j = 1; j <= n; ++j) {
                const auto& c2 = s2[j - 1];
                if (c1 == c2) {
                    dp[j] = prev[j - 1];
                } else {
                    dp[j] = std::min(prev[j] + c1, dp[j - 1] + c2);
                }
            }
        }
        return dp[n];
    }

    int approach1(const std::string& s1, const std::string& s2)
    {
        // dp[i][j] = min ASCII sum of deleted characters to make
        // s1[0:i-1] and s2[0:j-1] the same
        const int m = s1.size();
        const int n = s2.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, INT_MAX));
        dp[0][0] = 0;
        for (int i = 1; i <= m; ++i) {
            dp[i][0] = dp[i - 1][0] + s1[i - 1];
        }
        for (int j = 1; j <= n; ++j) {
            dp[0][j] = dp[0][j - 1] + s2[j - 1];
        }
        for (int i = 1; i <= m; ++i) {
            const auto& c1 = s1[i - 1];
            for (int j = 1; j <= n; ++j) {
                const auto& c2 = s2[j - 1];
                if (c1 == c2) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::min(dp[i - 1][j] + c1, dp[i][j - 1] + c2);
                }
            }
        }
        return dp[m][n];
    }
};
