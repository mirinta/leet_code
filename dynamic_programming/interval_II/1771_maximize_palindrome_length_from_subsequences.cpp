#include <string>
#include <vector>

/**
 * You are given two strings, word1 and word2. You want to construct a string in the following
 * manner:
 *
 * - Choose some non-empty subsequence subsequence1 from word1.
 *
 * - Choose some non-empty subsequence subsequence2 from word2.
 *
 * - Concatenate the subsequences: subsequence1 + subsequence2, to make the string.
 *
 * Return the length of the longest palindrome that can be constructed in the described manner. If
 * no palindromes can be constructed, return 0.
 *
 * A subsequence of a string s is a string that can be made by deleting some (possibly none)
 * characters from s without changing the order of the remaining characters.
 *
 * A palindrome is a string that reads the same forward as well as backward.
 *
 * ! 1 <= word1.length, word2.length <= 1000
 * ! word1 and word2 consist of lowercase English letters.
 */

class Solution {
public:
    int longestPalindrome(const std::string& word1, const std::string& word2)
    {
        // let s = word1 + word2
        // find the length of the longest palindrome subsequence in s
        // let seq1 and seq2 be subsequences taken from word1 and word2, respectively
        // we need to ensure:
        // - seq1 is taken from s[0:m-1] and seq2 is taken from s[m,m+n-1]
        // - if seq1 + seq2 is a palindrome, seq1.front() = seq2.back()
        const int m = word1.size();
        const auto s = word1 + word2;
        // dp[i][j] = length of the longest palindrome subsequence in s[i:j]
        // X X i i+1 ... j-1 j X X
        std::vector<std::vector<int>> dp(s.size(), std::vector<int>(s.size()));
        for (int i = 0; i < s.size(); ++i) {
            dp[i][i] = 1;
        }
        int result = 0;
        for (int i = s.size() - 1; i >= 0; --i) {
            for (int j = i + 1; j < s.size(); ++j) {
                if (s[i] == s[j]) {
                    dp[i][j] = 2 + dp[i + 1][j - 1];
                    if (i < m && j >= m) {
                        result = std::max(result, dp[i][j]);
                    }
                } else {
                    dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return result;
    }
};
