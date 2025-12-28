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
    int minimumDeletions(std::string s)
    {
        return approach2(s);
    }

private:
    int approach2(const std::string& s)
    {
        const int n = s.size();
        int endWithA = 0;
        int endWithB = 0;
        for (const auto& c : s) {
            if (c == 'a') {
                endWithA++;
            } else {
                endWithB = std::max(endWithA, endWithB) + 1;
            }
        }
        return n - std::max(endWithA, endWithB);
    }

    int approach1(const std::string& s)
    {
        // dp[i][0] = length of the longest non-decreasing subsequence of nums[0:i] ending at 'a'
        // dp[i][1] = length of the longest non-decreasing subsequence of nums[0:i] ending at 'b'
        const int n = s.size();
        std::vector<std::array<int, 2>> dp(n);
        dp[0][s[0] == 'a'] = 1;
        for (int i = 1; i < n; ++i) {
            if (s[i] == 'a') {
                dp[i][1] = dp[i - 1][1] + 1;
                dp[i][0] = dp[i - 1][0];
            } else {
                dp[i][0] = std::max(dp[i - 1][1], dp[i - 1][0]) + 1;
                dp[i][1] = dp[i - 1][1];
            }
        }
        return n - std::max(dp[n - 1][0], dp[n - 1][1]);
    }
};
