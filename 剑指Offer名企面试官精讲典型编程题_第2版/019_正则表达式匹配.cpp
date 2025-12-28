#include <string>
#include <vector>

/**
 * 请实现一个函数用来匹配包含'.'和'*'的正则表达式。
 *
 * 模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。
 *
 * 在本题中，匹配是指字符串的所有字符匹配整个模式。
 *
 * 例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但与"aa.a"和"ab*a"均不匹配。
 *
 * ! s 可能为空，且只包含从 a-z 的小写字母。
 * ! p 可能为空，且只包含从 a-z 的小写字母以及字符 . 和 *，无连续的 '*'。
 *
 * ! 本题与LC 10相同。
 */

class Solution {
public:
    bool isMatch(const std::string& s, const std::string& p)
    {
        // dp[i][j] = s[0:i) does/doesn't match with pattern p[0:j)
        const auto m = s.size();
        const auto n = p.size();
        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
        // base cases:
        // - dp[0][0] = true, empty pattern matches empty string
        // - dp[i][0] = false, for i!=0
        // - dp[0][j] = what kind of pattern can match empty string: p = [P *] repeat n times
        dp[0][0] = true;
        for (int j = 2; j <= n; ++j) {
            dp[0][j] = dp[0][j - 2] && (p[j - 1] == '*');
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] != '*') {
                    // s: S S S S i
                    // p: P P P j, j = '.' or any alphabet
                    dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                } else {
                    // s: S S S S i
                    // p: P P ? *, ? = '.' or any alphabet (no consecutive '*')
                    // case1: ? is matched at least 1 time
                    const bool case1 = dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.');
                    // case2: ? is matched 0 time
                    const bool case2 = dp[i][j - 2];
                    dp[i][j] = case1 || case2;
                }
            }
        }
        return dp[m][n];
    }
};