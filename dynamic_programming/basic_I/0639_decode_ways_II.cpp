#include <string>
#include <vector>

/**
 * A message containing letters from A-Z can be encoded into numbers using the following mapping:
 *
 *  'A' -> "1"
 *  'B' -> "2"
 *  ...
 *  'Z' -> "26"
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
 * In addition to the mapping above, an encoded message may contain the '*' character, which can
 * represent any digit from '1' to '9' ('0' is excluded). For example, the encoded message "1*" may
 * represent any of the encoded messages "11", "12", "13", "14", "15", "16", "17", "18", or "19".
 * Decoding "1*" is equivalent to decoding any of the encoded messages it can represent.
 *
 * Given a string s consisting of digits and '*' characters, return the number of ways to decode it.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is a digit or '*'.
 */

class Solution {
public:
    int numDecodings(std::string s)
    {
        // dp[i] = num of ways to decode s[0:i-1]
        constexpr int kMod = 1e9 + 7;
        const int n = s.size();
        std::vector<long long> dp(n + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            const auto& curr = s[i - 1];
            if (std::isdigit(curr) && curr > '0') {
                dp[i] = dp[i - 1];
            } else if (curr == '*') {
                dp[i] = dp[i - 1] * 9 % kMod;
                ;
            } else {
                dp[i] = 0;
            }
            if (i < 2)
                continue;

            const auto& prev = s[i - 2];
            if (std::isdigit(curr)) {
                if (prev == '1' || (prev == '2' && curr <= '6')) {
                    dp[i] = (dp[i] + dp[i - 2]) % kMod;
                } else if (prev == '*') {
                    // *[0~6], * can be either 1 or 2 => #options = 2
                    // *[7~9], * must be 1 => #options = 1
                    dp[i] = (dp[i] + dp[i - 2] * (curr <= '6' ? 2 : 1) % kMod) % kMod;
                }
            } else {
                if (prev == '1') {
                    // 1*, * can be 1~9 => #options = 9
                    dp[i] = (dp[i] + dp[i - 2] * 9 % kMod) % kMod;
                } else if (prev == '2') {
                    // 2*, * can be 1~6 => #options = 6
                    dp[i] = (dp[i] + dp[i - 2] * 6 % kMod) % kMod;
                } else if (prev == '*') {
                    // **, 1[1~9] or 2[1~6] => #options = 15
                    dp[i] = (dp[i] + dp[i - 2] * 15 % kMod) % kMod;
                }
            }
        }
        return dp[n];
    }
};