#include <string>
#include <vector>

/**
 * Given an input string "s" and a pattern "p", implement regular expression matching with support
 * for '.' and '*' where:
 *
 * - '.' matches any single character.
 *
 * - '*' matches zero or more of the preceding element.
 *
 * The matching should cover the entire input string (not partial).
 *
 * ! 1 <= s.length <= 20
 * ! 1 <= p.length <= 20
 * ! s contains only lowercase English letters.
 * ! p contains only lowercase English letters, '.', and '*'.
 * ! It is guaranteed for each appearance of the character '*', there will be a previous valid
 * ! character to match.
 *
 * Example:
 * Input: s = "ab", p = ".*"
 * Output: true
 * Explanation: ".*" means "zero or more (*) of any character (.)".
 *
 * Example:
 * Input: s = "aa", p = "a*"
 * Output: true
 * Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a'
 * once, it becomes "aa".
 */

class Solution {
public:
    bool isMatch(const std::string& s, const std::string& p)
    {
        // dp[i][j] = isMatch(s[0:i),  p[0:j))
        const auto m = s.size();
        const auto n = p.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, false));
        // base cases: i in range [1,m], j in range [1,n]
        // - dp[0][0] = true, empty pattern matches empty string
        // - dp[i][0] = false, empty pattern doesn't match any non-empty string
        // - dp[0][j] = what kind of pattern can match empty string?
        //   p: S * S * [S *] ..., repeat [S *], S can be any character
        dp[0][0] = true;
        for (int j = 2; j <= n; ++j) {
            dp[0][j] = dp[0][j - 2] && p[j - 1] == '*';
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (std::isalpha(p[j - 1])) {
                    // s: S S S S [?], ? must be X
                    // p: P P P [X]
                    dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1]);
                } else if (p[j - 1] == '.') {
                    // s: S S S S [?], ? can be any character
                    // p: P P P [.]
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (j >= 2 && p[j - 1] == '*') {
                    // there must be a character before '*'
                    // case 1, * matches zero preceding element
                    // s: S S S S [?]
                    // p: P P [X *] => P P
                    const bool case1 = dp[i][j - 2]; // not dp[i-1][j-2]
                    // case 2, * matches at least one preceding element
                    // s: S S S S [?], ? can be any character if X = '.', otherwise it must be X
                    // p: P P [X *]
                    const bool case2 = dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.');
                    dp[i][j] = case1 || case2;
                }
            }
        }
        return dp[m][n];
    }
};
