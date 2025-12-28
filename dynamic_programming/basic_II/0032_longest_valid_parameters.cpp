#include <string>
#include <vector>

/**
 * Given a string containing just the characters '(' and ')', return the length of the longest valid
 * (well-formed) parentheses substring.
 *
 * ! 0 <= s.length <= 3 * 10^4
 * ! s[i] is '(', or ')'.
 */

class Solution {
public:
    int longestValidParentheses(std::string s)
    {
        // dp[i] = length of the longest valid substring of s[0:i] ending at s[i]
        // case 1: s[i] = '(', dp[i] = 0
        // case 2: s[i] = ')' and s[i-1] = '('
        // X X i-2 ( )
        // case 3: s[i] = ')' and s[i-1] = '('
        // x j-2 j-1 ( X X X X X X ) )
        //           |<-L=dp[i-1]->|, j = i-L
        const int n = s.size();
        std::vector<int> dp(n, 0);
        int result = 0;
        for (int i = 1; i < n; ++i) {
            if (s[i] == '(') {
                dp[i] = 0;
            } else if (s[i - 1] == '(') {
                dp[i] = 2 + (i >= 2 ? dp[i - 2] : 0);
            } else {
                const int L = dp[i - 1];
                const int j = i - L;
                if (j - 1 >= 0 && s[j - 1] == '(') {
                    dp[i] = (j >= 2 ? dp[j - 2] : 0) + L + 2;
                }
            }
            result = std::max(result, dp[i]);
        }
        return result;
    }
};