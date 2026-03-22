#include <string>
#include <vector>

/**
 * You are given a string s and a positive integer k.
 *
 * Select a set of non-overlapping substrings from the string s that satisfy the following conditions:
 *
 * - The length of each substring is at least k.
 *
 * - Each substring is a palindrome.
 *
 * Return the maximum number of substrings in an optimal selection.
 *
 * A substring is a contiguous sequence of characters within a string.
 *
 * ! 1 <= k <= s.length <= 2000
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    int maxPalindromes(std::string& s, int k)
    {
        const int n = s.size();
        std::vector<std::vector<bool>> isValid(n, std::vector<bool>(n, false));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if (i + 1 < n && j - 1 >= 0 && i + 1 <= j - 1) {
                    isValid[i][j] = isValid[i + 1][j - 1] && (s[i] == s[j]);
                } else {
                    isValid[i][j] = s[i] == s[j];
                }
            }
        }
        // dp[i] = max num of valid substrings of s[0:i]
        // X X X X X j-1 j X X X X X X X i
        // |<--dp[j]-->| |<-palindrome-->|
        std::vector<int> dp(n, 0);
        for (int i = k - 1; i < n; ++i) {
            dp[i] = i > 0 ? dp[i - 1] : 0;
            for (int j = 0; i - j + 1 >= k; ++j) {
                if (isValid[j][i]) {
                    dp[i] = std::max(dp[i], 1 + (j > 0 ? dp[j - 1] : 0));
                }
            }
        }
        return dp[n - 1];
    }
};