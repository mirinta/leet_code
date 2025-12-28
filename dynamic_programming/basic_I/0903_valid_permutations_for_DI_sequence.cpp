#include <string>
#include <vector>

/**
 * You are given a string "s" of length "n" where s[i] is either:
 *
 * - 'D' means decreasing, or
 *
 * - 'I' means increasing.
 *
 * A permutation "perm" of n + 1 integers of all the integers in the range [0, n] is called a valid
 * permutation if for all valid i:
 *
 * - If s[i] == 'D', then perm[i] > perm[i + 1], and
 *
 * - If s[i] == 'I', then perm[i] < perm[i + 1].
 *
 * Return the number of valid permutations "perm". Since the answer may be large, return it modulo
 * 1e9 + 7.
 *
 * ! n == s.length
 * ! 1 <= n <= 200
 * ! s[i] is either 'I' or 'D'.
 */

class Solution {
public:
    int numPermsDISequence(const std::string& s)
    {
        if (s.empty())
            return 0;

        constexpr int kMod = 1e9 + 7;
        const auto n = s.size();
        // dp[i][j] = num of permutations made by digit[0:i] that satisfies s[0:i) and ends with
        // digit j
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (s[i - 1] == 'D') {
                    for (int k = j; k < i; ++k) {
                        dp[i][j] += dp[i - 1][k]; // dp[i-1][?], max(?)=i-1
                        dp[i][j] %= kMod;
                    }
                } else {
                    for (int k = j - 1; k >= 0; --k) {
                        dp[i][j] += dp[i - 1][k];
                        dp[i][j] %= kMod;
                    }
                }
            }
        }
        int result = 0;
        for (const auto& val : dp[n]) {
            result += val;
            result %= kMod;
        }
        return result;
    }
};