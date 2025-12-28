#include <string>
#include <vector>

/**
 * Given two strings word1 and word2, return the minimum number of steps required to make word1 and
 * word2 the same.
 *
 * In one step, you can delete exactly one character in either string.
 *
 * ! 1 <= word1.length, word2.length <= 500
 * ! word1 and word2 consist of only lowercase English letters.
 */

class Solution {
public:
    int minDistance(std::string word1, std::string word2)
    {
        return approach2(word1, word2);
    }

private:
    int approach2(const std::string& s1, const std::string& s2)
    {
        // dp[i][j] = min num of steps to make s1[0:i-1] and s2[0:j-1] the same
        const int m = s1.size();
        const int n = s2.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // delete s1[i-1] or delete s2[j-1]
                    dp[i][j] = 1 + std::min(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }

    int approach1(const std::string& s1, const std::string& s2)
    {
        // dp[i][j] = length of LCS of s1[0:i-1] and s2[0:j-1]
        const int m = s1.size();
        const int n = s2.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return m + n - 2 * dp[m][n];
    }
};
