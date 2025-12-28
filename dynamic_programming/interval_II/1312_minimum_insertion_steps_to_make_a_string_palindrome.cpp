#include <string>
#include <vector>

/**
 * Given a string s. In one step you can insert any character at any index of the string.
 *
 * Return the minimum number of steps to make s palindrome.
 *
 * A Palindrome String is one that reads the same backward as well as forward.
 *
 * ! 1 <= s.length <= 500
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    int minInsertions(std::string s)
    {
        // dp[i][j] = min num of insertions to make s[i:j] palindrome
        // ... i i+1 X X X j-1 j ...
        const int n = s.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, INT_MAX));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                const int length = j - i + 1;
                if (length <= 0) {
                    dp[i][j] = INT_MAX; // s[i:j] has no characters
                } else if (length == 1) {
                    dp[i][j] = 0;
                } else if (length == 2 && s[i] == s[j]) {
                    dp[i][j] = 0;
                } else if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1];
                } else {
                    // case1: insert j* = j at i
                    // we need to make s[i:j-1] a palindrome
                    // j* i X X X X X X j-1 j
                    //    |<--dp[i][j-1]->|
                    // case2: insert i* = i at j
                    // we need to make s[i+1,j] a palindrome
                    // i i+1 X X X X X X j i*
                    //   |<--dp[i+1][j]->|
                    dp[i][j] = 1 + std::min(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][n - 1];
    }
};