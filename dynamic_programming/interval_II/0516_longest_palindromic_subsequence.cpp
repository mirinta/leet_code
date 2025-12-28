#include <string>
#include <vector>

/**
 * Given a string s, find the longest palindromic subsequence's length in s.
 *
 * A subsequence is a sequence that can be derived from another sequence by deleting some or no
 * elements without changing the order of the remaining elements.
 *
 * ! 1 <= s.length <= 1000
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    int longestPalindromeSubseq(const std::string& s)
    {
        return approach2(s);
    }

private:
    // DP with space optimization, time O(N^2), space O(N)
    int approach2(const std::string& s)
    {
        const int n = s.size();
        std::vector<int> dp(n, 0);
        std::vector<int> prev(n, 0);
        for (int i = n - 1; i >= 0; --i) {
            prev = dp;
            dp[i] = 1;
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    dp[j] = prev[j - 1] + 2;
                } else {
                    dp[j] = std::max({prev[j], dp[j - 1], prev[j - 1]});
                }
            }
        }
        return dp[n - 1];
    }

    // DP, time O(N^2), space O(N^2)
    int approach1(const std::string& s)
    {
        // dp[i][j] = length of the longest palindromic subsequence in s[i:j]
        // ... i i+1 X X X j-1 j ...
        // - if s[i] == s[j], dp[i][j] = 2 + dp[i+1][j-1]
        // - otherwise, dp[i][j] = max(dp[i+1][j-1], dp[i+1][j], d[i][j-1])
        // either s[i] or s[j] is not in the LPS, or both of them are not in the LPS
        // base case:
        // - dp[i][i] = 1, only one character
        const int n = s.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = std::max({dp[i + 1][j], dp[i][j - 1], dp[i + 1][j - 1]});
                }
            }
        }
        return dp[0][n - 1];
    }
};