#include <array>
#include <vector>

/**
 * Given an integer n, your task is to count how many strings of length n can be formed under the
 * following rules:
 *
 * - Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
 *
 * - Each vowel 'a' may only be followed by an 'e'.
 *
 * - Each vowel 'e' may only be followed by an 'a' or an 'i'.
 *
 * - Each vowel 'i' may not be followed by another 'i'.
 *
 * - Each vowel 'o' may only be followed by an 'i' or a 'u'.
 *
 * - Each vowel 'u' may only be followed by an 'a'.
 *
 * Since the answer may be too large, return it modulo 10^9 + 7.
 *
 * ! 1 <= n <= 2 * 10^4
 */

class Solution {
public:
    int countVowelPermutation(int n)
    {
        return approach2(n);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    // DP with space optimization, time O(N), space O(1)
    int approach2(int n)
    {
        long endingAtA = 1;
        long endingAtE = 1;
        long endingAtI = 1;
        long endingAtO = 1;
        long endingAtU = 1;
        for (int i = 2; i <= n; ++i) {
            auto backupA = endingAtA;
            auto backupE = endingAtE;
            auto backupI = endingAtI;
            auto backupO = endingAtO;
            auto backupU = endingAtU;

            endingAtA = (backupE + backupI + backupU) % kMod;
            endingAtE = (backupA + backupI) % kMod;
            endingAtI = (backupE + backupO) % kMod;
            endingAtO = backupI;
            endingAtU = (backupI + backupO) % kMod;
        }
        return (endingAtA + endingAtE + endingAtI + endingAtO + endingAtU) % kMod;
    }

    // DP, time O(N), space O(N)
    int approach1(int n)
    {
        // rules:
        // - a can be followed by {e}
        // - e can be followed by {a, i}
        // - i can be followed by {a, e, o, u}
        // - o can be followed by {i, u}
        // - u can be followed by {a}
        // in other words:
        // - ending at a, the previous character(s) can be {e, i, u}
        // - ending at e, the previous character(s) can be {a, i}
        // - ending at i, the previous character(s) can be {e, o}
        // - ending at o, the previous character(s) can be {i}
        // - ending at u, the previous character(s) can be {i, o}
        // dp[i][0] = num of strings of length i ending at 'a'
        // dp[i][1] = num of strings of length i ending at 'e'
        // dp[i][2] = num of strings of length i ending at 'i'
        // dp[i][3] = num of strings of length i ending at 'o'
        // dp[i][4] = num of strings of length i ending at 'u'
        const std::vector<std::vector<int>> kValidPrevVowels{{1, 2, 4}, {0, 2}, {1, 3}, {2}, {2, 3}};
        std::vector<std::array<int, 5>> dp(n + 1, {0});
        dp[1] = {1, 1, 1, 1, 1};
        for (int i = 2; i <= n; ++i) {
            for (int curr = 0; curr < 5; ++curr) {
                for (const auto& prev : kValidPrevVowels[curr]) {
                    dp[i][curr] = (dp[i][curr] + dp[i - 1][prev]) % kMod;
                }
            }
        }
        int result = 0;
        for (const auto& val : dp[n]) {
            result = (result + val) % kMod;
        }
        return result;
    }
};