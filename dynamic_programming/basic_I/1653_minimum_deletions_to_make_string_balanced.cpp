#include <array>
#include <string>
#include <vector>

/**
 * You are given a string s consisting only of characters 'a' and 'b'​​​​.
 *
 * You can delete any number of characters in s to make s balanced. s is balanced if there is no
 * pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.
 *
 * Return the minimum number of deletions needed to make s balanced.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is 'a' or 'b'​​.
 */

class Solution {
public:
    int minimumDeletions(const std::string& s)
    {
        // dp[i][0] = length of the longest valid subsequence of s[0:i) ending at s[i] = 'a'
        // dp[i][1] = length of the longest valid subsequence of s[0:i) ending at s[i] = 'b'
        const int n = s.size();
        std::vector<std::array<int, 2>> dp(n + 1, {0, 0});
        int result = n;
        for (int i = 1; i <= n; ++i) {
            if (s[i - 1] == 'a') {
                dp[i][0] = dp[i - 1][0] + 1;
                dp[i][1] = dp[i - 1][1];
            } else {
                dp[i][0] = dp[i - 1][0];
                dp[i][1] = std::max(dp[i - 1][0], dp[i - 1][1]) + 1;
            }
            result = std::min(result, n - std::max(dp[i][0], dp[i][1]));
        }
        return result;
    }
};
