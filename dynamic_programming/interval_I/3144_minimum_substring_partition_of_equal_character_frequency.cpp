#include <array>
#include <string>
#include <vector>

/**
 * Given a string s, you need to partition it into one or more balanced substrings. For example, if
 * s == "ababcc" then ("abab", "c", "c"), ("ab", "abc", "c"), and ("ababcc") are all valid
 * partitions, but ("a", "bab", "cc"), ("aba", "bc", "c"), and ("ab", "abcc") are not. The
 * unbalanced substrings are bolded.
 *
 * Return the minimum number of substrings that you can partition s into.
 *
 * Note: A balanced string is a string where each character in the string occurs the same number of
 * times.
 *
 * ! 1 <= s.length <= 1000
 * ! s consists only of English lowercase letters.
 */

class Solution {
public:
    int minimumSubstringsInPartition(std::string s)
    {
        const int n = s.size();
        // count[i][c] = occurrences of letter c in s[0:i-1]
        std::vector<std::array<int, 26>> count(n + 1);
        for (int i = 1; i <= n; ++i) {
            count[i] = count[i - 1];
            count[i][s[i - 1] - 'a']++;
        }
        // dp[i] = min num of balanced substrings of s[0:i] ending at s[i]
        std::vector<int> dp(n, INT_MAX);
        dp[0] = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = i; j >= 0; --j) {
                if (isValid(j, i, count)) {
                    dp[i] = std::min(dp[i], 1 + (j > 0 ? dp[j - 1] : 0));
                }
            }
        }
        return dp[n - 1];
    }

private:
    // check if s[lo:hi] is a balanced substring
    bool isValid(int lo, int hi, const std::vector<std::array<int, 26>>& count)
    {
        int prev = 0;
        for (int i = 0; i < 26; ++i) {
            const int freq = count[hi + 1][i] - count[lo][i];
            if (freq == 0)
                continue;

            if (prev != 0 && prev != freq)
                return false;

            if (prev == 0) {
                prev = freq;
            }
        }
        return true;
    }
};