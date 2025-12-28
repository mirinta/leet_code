#include <string>
#include <vector>

/**
 * Given two strings "word1" and "word2", return the minimum number of operations required to
 * convert "word1" to "word2".
 *
 * You have the following three operations permitted on a word:
 *
 * - Insert a character
 *
 * - Delete a character
 *
 * - Replace a character
 *
 * ! 0 <= word1.length, word2.length <= 500
 * ! word1 and word2 consist of lowercase English letters.
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
        const int n = s2.size();
        std::vector<int> dp(n + 1, 0);
        for (int j = 0; j <= n; ++j) {
            dp[j] = j;
        }
        for (const auto& c1 : s1) {
            auto prev = dp;
            dp[0] += 1;
            for (int j = 1; j <= n; ++j) {
                if (c1 == s2[j - 1]) {
                    dp[j] = prev[j - 1];
                } else {
                    const int case1 = 1 + prev[j - 1];
                    const int case2 = 1 + prev[j];
                    const int case3 = 1 + dp[j - 1];
                    dp[j] = std::min({case1, case2, case3});
                }
            }
        }
        return dp[n];
    }

    int approach1(const std::string& s1, const std::string& s2)
    {
        // dp[i][j] = min num of operations to convert s1[0:i-1] to s2[0:j-1]
        const int m = s1.size();
        const int n = s2.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, INT_MAX));
        dp[0][0] = 0;
        for (int i = 1; i <= m; ++i) {
            dp[i][0] = i; // delete all characters of s1[0:i-1]
        }
        for (int j = 1; j <= n; ++j) {
            dp[0][j] = j; // insert all characters of s2[0:j-1]
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    const int case1 = 1 + dp[i - 1][j - 1]; // replace s1[i-1] with s2[j-1]
                    const int case2 = 1 + dp[i - 1][j];     // delete s1[i-1]
                    const int case3 = 1 + dp[i][j - 1];     // insert s2[j-1]
                    dp[i][j] = std::min({case1, case2, case3});
                }
            }
        }
        return dp[m][n];
    }
};
