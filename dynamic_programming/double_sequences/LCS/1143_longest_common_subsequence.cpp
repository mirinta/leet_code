#include <string>
#include <vector>

/**
 * Given two strings "text1" and "text2", return the length of their longest common subsequence. If
 * there is no common subsequence, return 0.
 *
 * A subsequence of a string is a new string generated from the original string with some characters
 * (can be none) deleted without changing the relative order of the remaining characters.
 *
 * - For example, "ace" is a subsequence of "abcde".
 *
 * A common subsequence of two strings is a subsequence that is common to both strings.
 *
 * ! 1 <= text1.length, text2.length <= 1000
 * ! text1 and text2 consist of only lowercase English characters.
 */

class Solution {
public:
    int longestCommonSubsequence(std::string text1, std::string text2)
    {
        return approach2(text1, text2);
    }

private:
    int approach2(const std::string& text1, const std::string& text2)
    {
        const int n = text2.size();
        std::vector<int> dp(n + 1, 0);
        for (const auto& c1 : text1) {
            auto prev = dp;
            for (int j = 1; j <= n; ++j) {
                if (c1 == text2[j - 1]) {
                    dp[j] = 1 + prev[j - 1];
                } else {
                    dp[j] = std::max(prev[j], dp[j - 1]);
                }
            }
        }
        return dp[n];
    }

    int approach1(const std::string& text1, const std::string& text2)
    {
        // dp[i][j] = length of the longest common subsequence of text1[0:i-1] and text2[0:j-1]
        const int m = text1.size();
        const int n = text2.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            const auto& c1 = text1[i - 1];
            for (int j = 1; j <= n; ++j) {
                const auto& c2 = text2[j - 1];
                if (c1 == c2) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};