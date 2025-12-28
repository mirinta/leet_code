#include <string>
#include <vector>

/**
 * Given a string s, return the number of palindromic substrings in it.
 *
 * A string is a palindrome when it reads the same backward as forward.
 *
 * A substring is a contiguous sequence of characters within the string.
 *
 * ! 1 <= s.length <= 1000
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    int countSubstrings(std::string s)
    {
        return approach2(s);
    }

private:
    // DP, TC = O(N^2), SC = O(N^2)
    int approach2(const std::string& s)
    {
        // dp[i][j] = whether s[i:j] is a palindromic substring
        // X X X i i+1 X X X j-1 j X X X
        // if s[i] = s[j] and s[i+1:j-1] is a palindromic substring
        // then dp[i][j] = true
        // otherwise, dp[i][j] = false
        const int n = s.size();
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
        int result = 0;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                const int length = j - i + 1;
                if (length == 1) {
                    dp[i][j] = true;
                } else if (s[i] == s[j] && length == 2) {
                    dp[i][j] = true;
                } else {
                    dp[i][j] = s[i] == s[j] && dp[i + 1][j - 1];
                }
                result += dp[i][j];
            }
        }
        return result;
    }

    // Expand around centers, TC = O(N^2), SC = O(1)
    int approach1(const std::string& s)
    {
        const int n = s.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += count(i, i, s);
            result += count(i, i + 1, s);
        }
        return result;
    }

    // return num of palindromic substrings around given centers
    int count(int centerLeft, int centerRight, const std::string& s)
    {
        const int n = s.size();
        int result = 0;
        int i = centerLeft;
        int j = centerRight;
        while (i >= 0 && j < n && s[i] == s[j]) {
            i--;
            j++;
            result++;
        }
        return result;
    }
};