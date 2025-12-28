#include <string>
#include <vector>

/**
 * Given a string s and an integer k, return true if s is a k-palindrome.
 *
 * A string is k-palindrome if it can be transformed into a palindrome by removing at most k
 * characters from it.
 *
 * ! 1 <= s.length <= 1000
 * ! s consists of only lowercase English letters.
 * ! 1 <= k <= s.length
 */

class Solution {
public:
    bool isValidPalindrome(std::string s, int k)
    {
        return approach2(s, k);
    }

private:
    // DP with space optimization, time O(N^2), space O(N)
    bool approach2(const std::string& s, int k)
    {
        const int n = s.size();
        std::vector<int> dp(n, 0);
        for (int i = n - 1; i >= 0; --i) {
            auto prev = dp;
            dp[i] = 1;
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    dp[j] = prev[j - 1] + 2;
                } else {
                    dp[j] = std::max({prev[j], dp[j - 1], prev[j - 1]});
                }
                if (n - dp[j] <= k)
                    return true;
            }
        }
        return false;
    }

    // DP, time O(N^2), space O(N^2)
    bool approach1(const std::string& s, int k)
    {
        // #deletions <= k
        // n - #deletions = length of palindrome subsequence >= k
        const int n = s.size();
        // dp[i][j] = max length of palindrome subsequence of s[i:j]
        // X X X X i i+1 X X X j-1 j X X X X X
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
                if (n - dp[i][j] <= k)
                    return true;
            }
        }
        return false;
    }
};