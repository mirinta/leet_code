#include <array>
#include <string>
#include <vector>

/**
 * You are given a string s, a string chars of distinct characters and an integer array vals of the
 * same length as chars.
 *
 * The cost of the substring is the sum of the values of each character in the substring. The cost
 * of an empty string is considered 0.
 *
 * The value of the character is defined in the following way:
 *
 * - If the character is not in the string chars, then its value is its corresponding position
 * (1-indexed) in the alphabet. For example, the value of 'a' is 1, the value of 'b' is 2, and so
 * on. The value of 'z' is 26.
 *
 * - Otherwise, assuming i is the index where the character occurs in the string chars, then its
 * value is vals[i].
 *
 * Return the maximum cost among all substrings of the string s.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consist of lowercase English letters.
 * ! 1 <= chars.length <= 26
 * ! chars consist of distinct lowercase English letters.
 * ! vals.length == chars.length
 * ! -1000 <= vals[i] <= 1000
 */

class Solution {
public:
    int maximumCostSubstring(std::string s, std::string chars, std::vector<int>& vals)
    {
        return approach2(s, chars, vals);
    }

private:
    // DP with space optimization, SC = O(N), SC = O(26)
    int approach2(const std::string& s, const std::string& chars, const std::vector<int>& vals)
    {
        std::array<int, 26> cost{};
        for (int i = 0; i < 26; ++i) {
            cost[i] = i + 1;
        }
        for (int i = 0; i < chars.size(); ++i) {
            cost[chars[i] - 'a'] = vals[i];
        }
        const int n = s.size();
        int dp = 0;
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            dp = std::max(cost[s[i - 1] - 'a'], dp + cost[s[i - 1] - 'a']);
            result = std::max(result, dp);
        }
        return result;
    }

    // DP, TC = O(N), SC = O(N+26)
    int approach1(const std::string& s, const std::string& chars, const std::vector<int>& vals)
    {
        std::array<int, 26> cost{};
        for (int i = 0; i < 26; ++i) {
            cost[i] = i + 1;
        }
        for (int i = 0; i < chars.size(); ++i) {
            cost[chars[i] - 'a'] = vals[i];
        }
        // dp[i] = max cost of subarrays of s[0:i-1] ending at s[i-1]
        const int n = s.size();
        std::vector<int> dp(n + 1);
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = std::max(cost[s[i - 1] - 'a'], dp[i - 1] + cost[s[i - 1] - 'a']);
            result = std::max(result, dp[i]);
        }
        return result;
    }
};