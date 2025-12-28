#include <string>
#include <vector>

/**
 * Given a string s and an integer k, partition s into k substrings such that the sum of the number
 * of letter changes required to turn each substring into a semi-palindrome is minimized.
 *
 * Return an integer denoting the minimum number of letter changes required.
 *
 * Notes
 *
 * - A string is a palindrome if it can be read the same way from left to right and right to left.
 *
 * - A string with a length of len is considered a semi-palindrome if there exists a positive
 * integer d such that 1 <= d < len and len % d == 0, and if we take indices that have the same
 * modulo by d, they form a palindrome. For example, "aa", "aba", "adbgad", and, "abab" are
 * semi-palindrome and "a", "ab", and, "abca" are not.
 *
 * - A substring is a contiguous sequence of characters within a string.
 *
 * ! 2 <= s.length <= 200
 * ! 1 <= k <= s.length / 2
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    int minimumChanges(std::string s, int k)
    {
        const int n = s.size();
        const auto divisors = getDivisors(n);
        // changes[i][len] = min changes to make s[i:i+len) semi-palindrome
        std::vector<std::vector<int>> changes(n, std::vector<int>(1 + n, INT_MAX / 2));
        for (int i = 0; i < n; ++i) {
            for (int length = 2; i + length - 1 < n; ++length) {
                const int j = length + i - 1;
                changes[i][length] = calcMinChanges(i, length, s, divisors);
            }
        }
        // dp[i][j] = min changes to partition s[0:j) into i substrings
        // such that each substring is a semi-palindrome
        // X X X X X X X X X t X X X X X X j
        // |<--dp[i-1][t]->| |<--substr->|
        // |<----------dp[i][j]--------->|
        std::vector<std::vector<int>> dp(1 + k, std::vector<int>(1 + n, INT_MAX / 2));
        dp[0][0] = 0;
        for (int i = 1; i <= k; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int t = j - 1; t >= 0; --t) {
                    dp[i][j] = std::min(dp[i][j], dp[i - 1][t] + changes[t][j - t]);
                }
            }
        }
        return dp[k][n];
    }

private:
    std::vector<std::vector<int>> getDivisors(int n)
    {
        std::vector<std::vector<int>> result(1 + n); // result[i] stores the divisors of number i
        for (int i = 1; i <= n; ++i) {
            // i is the divisor of {i, 2i, 3i, ...}
            for (int j = 2 * i; j <= n; j += i) {
                result[j].push_back(i);
            }
        }
        return result;
    }

    int calcMinChanges(int start, int length, const std::string& s, const std::vector<std::vector<int>>& divisors)
    {
        int result = INT_MAX / 2;
        if (length < 2)
            return result;

        for (const auto& d : divisors[length]) {
            int count = 0;
            for (int remainder = 0; remainder < d; ++remainder) {
                int left = start + remainder;
                int right = left + length - d;
                while (left < right) {
                    if (s[left] != s[right]) {
                        count++;
                    }
                    left += d;
                    right -= d;
                }
            }
            result = std::min(result, count);
        }
        return result;
    }
};