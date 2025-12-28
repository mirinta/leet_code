#include <string>
#include <vector>

/**
 * Run-length encoding is a string compression method that works by replacing consecutive identical
 * characters (repeated 2 or more times) with the concatenation of the character and the number
 * marking the count of the characters (length of the run). For example, to compress the string
 * "aabccc" we replace "aa" by "a2" and replace "ccc" by "c3". Thus the compressed string becomes
 * "a2bc3".
 *
 * Notice that in this problem, we are not adding '1' after single characters.
 *
 * Given a string s and an integer k. You need to delete at most k characters from s such that the
 * run-length encoded version of s has minimum length.
 *
 * Find the minimum length of the run-length encoded version of s after deleting at most k
 * characters.
 *
 * ! 1 <= s.length <= 100
 * ! 0 <= k <= s.length
 * ! s contains only lowercase English letters.
 */

class Solution {
public:
    int getLengthOfOptimalCompression(std::string s, int k)
    {
        // dp[i][t] = min length of the encoded version of s[0:i) after deleting at most t
        // characters
        const int n = s.size();
        s.insert(s.begin(), '#');
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, INT_MAX));
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int t = 0; t <= std::min(i, k); ++t) {
                // case 1: delete the current character
                if (t > 0) {
                    dp[i][t] = std::min(dp[i][t], dp[i - 1][t - 1]); // delete current character
                }
                // case 2: keep the current character
                // X j-1 j X X X X X i
                //       |<--------->|
                // check s[j:i]
                // - #same = the num of characters == s[i]
                // - #diff = the num of characters != s[i], we need to delete these characters
                // then dp[i][t] = dp[j-1][t-diff] + length of encoded s[i]*#same
                // NOTE: iterate over j backwards to get the correct answer
                int same = 0;
                int diff = 0;
                for (int j = i; j >= 1; --j) {
                    if (s[j] == s[i]) {
                        same++;
                    } else {
                        diff++;
                    }
                    if (t < diff || t - diff > j - 1)
                        break;

                    if (same >= 100) {
                        dp[i][t] = std::min(dp[i][t], dp[j - 1][t - diff] + 4); // 1 for character, 3 for count
                    } else if (same >= 10) {
                        dp[i][t] = std::min(dp[i][t],
                                            dp[j - 1][t - diff] + 3); // 1 for character, 2 for count
                    } else if (same >= 2) {
                        dp[i][t] = std::min(dp[i][t],
                                            dp[j - 1][t - diff] + 2); // 1 for character, 1 for count
                    } else {
                        dp[i][t] = std::min(dp[i][t], dp[j - 1][t - diff] + 1); // 1 for character
                    }
                }
            }
        }
        return dp[n][k];
    }
};