#include <string>
#include <vector>

/**
 * Given two strings s and t, return the number of distinct subsequences of s which equals t.
 *
 * The test cases are generated so that the answer fits on a 32-bit signed integer.
 *
 * ! 1 <= s.length, t.length <= 1000
 * ! s and t consist of English letters.
 */

class Solution {
public:
    int numDistinct(std::string s, std::string t)
    {
        return approach2(s, t);
    }

private:
    int approach2(const std::string& s, const std::string& t)
    {
        const int m = s.size();
        const int n = t.size();
        if (m < n)
            return 0;

        std::vector<size_t> dp(n + 1, 0);
        dp[0] = 1;
        for (const auto& c : s) {
            for (int j = n; j >= 1; --j) {
                if (c == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }
        return dp[n];
    }

    int approach1(const std::string& s, const std::string& t)
    {
        // dp[i][j] = num of distinct subsequences of s[0:i-1] which equals t[0:j-1]
        const int m = s.size();
        const int n = t.size();
        if (m < n)
            return 0;

        std::vector<std::vector<size_t>> dp(m + 1, std::vector<size_t>(n + 1, 0));
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] += dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};