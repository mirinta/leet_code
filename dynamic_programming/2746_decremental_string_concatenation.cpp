#include <cstring>
#include <string>
#include <vector>

/**
 * You are given a 0-indexed array words containing n strings.
 *
 * Let's define a join operation join(x, y) between two strings x and y as concatenating them into
 * xy. However, if the last character of x is equal to the first character of y, one of them is
 * deleted.
 *
 * For example join("ab", "ba") = "aba" and join("ab", "cde") = "abcde".
 *
 * You are to perform n - 1 join operations. Let str0 = words[0]. Starting from i = 1 up to i = n -
 * 1, for the ith operation, you can do one of the following:
 *
 * - Make stri = join(stri - 1, words[i])
 *
 * - Make stri = join(words[i], stri - 1)
 *
 * Your task is to minimize the length of strn - 1.
 *
 * Return an integer denoting the minimum possible length of strn - 1.
 *
 * ! 1 <= words.length <= 1000
 * ! 1 <= words[i].length <= 50
 * ! Each character in words[i] is an English lowercase letter
 */

class Solution {
public:
    int minimizeConcatenatedLength(std::vector<std::string>& words)
    {
        // dp[i][j][k] = length of concatenating words[0:i] that starts with letter j and ends with
        // letter k
        const auto n = words.size();
        // constraint: words.size() <= 1000, words[i].size() <= 50
        int dp[1000][26][26];
        std::memset(dp, 50000, sizeof(dp));
        dp[0][words[0].front() - 'a'][words[0].back() - 'a'] = words[0].size();
        for (int i = 1; i < n; ++i) {
            const int front = words[i].front() - 'a';
            const int back = words[i].back() - 'a';
            const int length = words[i].size();
            for (int j = 0; j < 26; ++j) {
                for (int k = 0; k < 26; ++k) {
                    // put word at back
                    if (front == k) {
                        dp[i][j][back] = std::min(dp[i][j][back], dp[i - 1][j][k] + length - 1);
                    } else {
                        dp[i][j][back] = std::min(dp[i][j][back], dp[i - 1][j][k] + length);
                    }
                    // put word at front
                    if (back == j) {
                        dp[i][front][k] = std::min(dp[i][front][k], dp[i - 1][j][k] + length - 1);
                    } else {
                        dp[i][front][k] = std::min(dp[i][front][k], dp[i - 1][j][k] + length);
                    }
                }
            }
        }
        int result = INT_MAX;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                result = std::min(result, dp[n - 1][i][j]);
            }
        }
        return result;
    }
};