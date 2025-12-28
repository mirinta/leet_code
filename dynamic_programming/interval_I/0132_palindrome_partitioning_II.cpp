#include <string>
#include <vector>

/**
 * Given a string s, partition s such that every  substring of the partition is a palindrome.
 *
 * Return the minimum cuts needed for a palindrome partitioning of s.
 *
 * ! 1 <= s.length <= 2000
 * ! s consists of lowercase English letters only.
 */

class Solution {
public:
    int minCut(const std::string& s)
    {
        const int n = s.size();
        const auto isPalindrome = getPalindromeValidator(s);
        // dp[i] = min cuts needed for a palindrome partitioning of s[0:i]
        // 0 X X X X j-1 j X X X X X X X i
        // |<--dp[j]-->| |<-palindrome?->|
        // |<-----------dp[i]----------->|
        std::vector<int> dp(n, INT_MAX);
        dp[0] = 0; // only one character in the range [0:0]
        for (int i = 1; i < n; ++i) {
            for (int j = i; j >= 0; --j) {
                if (!isPalindrome[j][i])
                    continue;

                dp[i] = std::min(dp[i], j - 1 >= 0 ? 1 + dp[j - 1] : 0);
            }
        }
        return dp[n - 1];
    }

private:
    std::vector<std::vector<bool>> getPalindromeValidator(const std::string& s)
    {
        const int n = s.size();
        // dp[i][j] = whether s[i:j] is a palindrome
        // X X i i+1 X X X X X X j-1 j X X
        //       |<--dp[i+1][j-1]->|
        //     |<------dp[i][j]----->|
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                const int length = j - i + 1;
                if (length <= 0) {
                    dp[i][j] = false;
                } else if (length == 1) {
                    dp[i][j] = true;
                } else if (s[i] == s[j] && length == 2) {
                    dp[i][j] = true;
                } else if (s[i] == s[j] && dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                } else {
                    dp[i][j] = false;
                }
            }
        }
        return dp;
    }
};
