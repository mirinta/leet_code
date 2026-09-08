#include <array>
#include <string>
#include <vector>

/**
 * Given a string s, return the number of distinct non-empty subsequences of s. Since the answer may be very large,
 * return it modulo 10^9 + 7.
 *
 * A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of
 * the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence
 * of "abcde" while "aec" is not.)
 *
 * ! 1 <= s.length <= 2000
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    int distinctSubseqII(std::string& s)
    {
        static constexpr long long kMod = 1e9 + 7;
        const int n = s.size();
        // dp[i] = num of valid subsequences of s[0:i-1]
        std::vector<long long> dp(n + 1, 0);
        dp[0] = 1;
        std::array<int, 26> last{};
        last.fill(-1);
        for (int i = 1; i <= n; ++i) {
            dp[i] = (dp[i - 1] + dp[i - 1]) % kMod; // select or not select
            const int index = s[i - 1] - 'a';
            if (last[index] != -1) {
                dp[i] = (dp[i] - dp[last[index] - 1] + kMod) % kMod; // remove duplicates
            }
            last[index] = i;
        }
        return (dp[n] - 1 + kMod) % kMod; // remove empty subsequence
    }
};
