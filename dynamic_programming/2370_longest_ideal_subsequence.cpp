#include <array>
#include <string>
#include <vector>

/**
 * You are given a string s consisting of lowercase letters and an integer k. We call a string t
 * ideal if the following conditions are satisfied:
 *
 * - t is a subsequence of the string s.
 *
 * - The absolute difference in the alphabet order of every two adjacent letters in t is less than
 * or equal to k.
 *
 * Return the length of the longest ideal string.
 *
 * A subsequence is a string that can be derived from another string by deleting some or no
 * characters without changing the order of the remaining characters.
 *
 * Note that the alphabet order is not cyclic. For example, the absolute difference in the alphabet
 * order of 'a' and 'z' is 25, not 1.
 *
 * ! 1 <= s.length <= 10^5
 * ! 0 <= k <= 25
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    int longestIdealString(std::string s, int k)
    {
        // dp[i] = length of the longest valid subsequence of s[0:i]
        const int n = s.size();
        std::array<int, 26> last{};
        std::fill(last.begin(), last.end(), -1);
        std::vector<int> dp(n, 0);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            dp[i] = 1;
            const int index = s[i] - 'a';
            for (int j = 0; j < 26; ++j) {
                if (std::abs(index - j) <= k && last[j] != -1) {
                    dp[i] = std::max(dp[i], 1 + dp[last[j]]);
                }
            }
            result = std::max(result, dp[i]);
            last[index] = i;
        }
        return result;
    }
};