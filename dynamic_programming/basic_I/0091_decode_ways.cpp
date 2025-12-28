#include <string>
#include <vector>

/**
 * A message containing letters from A-Z can be encoded into numbers using the following mapping:
 *
 * 'A' -> "1"
 * 'B' -> "2"
 * ...
 * 'Z' -> "26"
 *
 * To decode an encoded message, all the digits must be grouped then mapped back into letters using
 * the reverse of the mapping above (there may be multiple ways). For example, "11106" can be mapped
 * into:
 *
 * - "AAJF" with the grouping (1 1 10 6)
 *
 * - "KJF" with the grouping (11 10 6)
 *
 * Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F' since "6" is
 * different from "06".
 *
 * Given a string "s" containing only digits, return the number of ways to decode it.
 *
 * The test cases are generated so that the answer fits in a 32-bit integer.
 *
 * ! 1 <= s.length <= 100
 * ! s contains only digits and may contain leading zero(s).
 */

class Solution {
public:
    int numDecodings(std::string s)
    {
        return approach2(s);
    }

private:
    // DP with space optimization, time O(N), space O(1)
    int approach2(const std::string& s)
    {
        if (s.empty())
            return 0;

        const int n = s.size();
        int iMinus1 = s[0] == '0' ? 0 : 1;
        int iMinus2 = 1;
        for (int i = 2; i <= n; ++i) {
            if (iMinus1 == 0)
                return 0;

            int dp = 0;
            const auto& curr = s[i - 1];
            if (curr > '0') {
                dp = iMinus1;
            }
            const auto& prev = s[i - 2];
            if (prev == '1' || (prev == '2' && curr <= '6')) {
                dp += iMinus2;
            }
            iMinus2 = iMinus1;
            iMinus1 = dp;
        }
        return iMinus1;
    }

    // DP, time O(N), space O(N)
    int approach1(const std::string& s)
    {
        if (s.empty())
            return 0;

        const int n = s.size();
        // dp[i] = num of ways to decode s[0:i)
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            if (dp[i - 1] == 0)
                return 0;

            // s contains only digits
            const auto& curr = s[i - 1];
            if (curr > '0') {
                dp[i] = dp[i - 1]; // single digit 1~9 are valid
            }
            if (i >= 2) {
                const auto& prev = s[i - 2];
                // combine with the previous digit, 10~19 and 20~26 are valid
                if (prev == '1' || (prev == '2' && curr <= '6')) {
                    dp[i] += dp[i - 2];
                }
            }
        }
        return dp[n];
    }
};