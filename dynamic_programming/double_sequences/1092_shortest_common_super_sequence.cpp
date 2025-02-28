#include <string>
#include <vector>

/**
 * Given two strings str1 and str2, return the shortest string that has both str1 and str2 as
 * subsequences. If there are multiple valid strings, return any of them.
 *
 * A string s is a subsequence of string t if deleting some number of characters from t (possibly 0)
 * results in the string s.
 *
 * ! 1 <= str1.length, str2.length <= 1000
 * ! str1 and str2 consist of lowercase English letters.
 */

class Solution
{
public:
    std::string shortestCommonSupersequence(std::string str1, std::string str2)
    {
        // dp[i][j] = length of the shortest common supersequence of str1[0:i) and str2[0:j)
        const int m = str1.size();
        const int n = str2.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + std::min(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        int i = m;
        int j = n;
        std::string result;
        while (i > 0 || j > 0) {
            if (i == 0) {
                result.push_back(str2[j - 1]);
                j--;
                continue;
            }
            if (j == 0) {
                result.push_back(str1[i - 1]);
                i--;
                continue;
            }
            if (str1[i - 1] == str2[j - 1]) {
                result.push_back(str1[i - 1]);
                i--;
                j--;
            } else if (dp[i][j] == dp[i - 1][j] + 1) {
                result.push_back(str1[i - 1]);
                i--;
            } else {
                result.push_back(str2[j - 1]);
                j--;
            }
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};
