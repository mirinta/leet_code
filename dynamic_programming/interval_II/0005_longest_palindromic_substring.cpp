#include <string>
#include <vector>

/**
 * Given a string s, return the longest palindromic substring in s.
 *
 * ! 1 <= s.length <= 1000
 * ! s consist of only digits and English letters.
 */

class Solution {
public:
    std::string longestPalindrome(std::string s)
    {
        return approach2(s);
    }

private:
    // time O(N^2), space O(1)
    std::string approach2(const std::string& s)
    {
        const int n = s.size();
        int start = 0;
        int maxLength = 0;
        for (int i = 0; i < n; ++i) {
            const auto [oddStart, oddLength] = getPalindrome(i, i, s);
            if (oddLength > maxLength) {
                start = oddStart;
                maxLength = oddLength;
            }
            if (i == n - 1)
                break;

            const auto [evenStart, evenLength] = getPalindrome(i, i + 1, s);
            if (evenLength > maxLength) {
                start = evenStart;
                maxLength = evenLength;
            }
        }
        return s.substr(start, maxLength);
    }

    // return <start, length>
    std::pair<int, int> getPalindrome(int left, int right, const std::string& s)
    {
        // X X X LEFT RIGHT X X X
        //        <-| |->
        const int n = s.size();
        while (left >= 0 && right < n && s[left] == s[right]) {
            left--;
            right++;
        }
        return {left + 1, right - left - 1};
    }

    // DP, time O(N^2), space O(N^2)
    std::string approach1(const std::string& s)
    {
        const int n = s.size();
        // dp[i][j] = whether s[i:j] is a palindrome
        // X X i i+1 X X j-1 j X X
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
        int maxLength = 0;
        int start = 0;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                const int length = j - i + 1;
                if (length == 1) {
                    dp[i][j] = true;
                } else if (length == 2) {
                    dp[i][j] = s[i] == s[j];
                } else {
                    dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]);
                }
                if (dp[i][j] && j - i + 1 > maxLength) {
                    maxLength = j - i + 1;
                    start = i;
                }
            }
        }
        return s.substr(start, maxLength);
    }
};
