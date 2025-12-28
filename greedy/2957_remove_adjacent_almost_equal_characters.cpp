#include <string>
#include <vector>

/**
 * You are given a 0-indexed string word.
 *
 * In one operation, you can pick any index i of word and change word[i] to any lowercase English
 * letter.
 *
 * Return the minimum number of operations needed to remove all adjacent almost-equal characters
 * from word.
 *
 * Two characters a and b are almost-equal if a == b or a and b are adjacent in the alphabet.
 *
 * ! 1 <= word.length <= 100
 * ! word consists only of lowercase English letters.
 */

class Solution {
public:
    int removeAlmostEqualCharacters(std::string word)
    {
        return approach3(word);
    }

private:
    // Greedy, time O(N), space O(1)
    int approach3(std::string& word)
    {
        // X X X i-1 i i+1 X X X
        //           ^
        // if word[i] and word[i-1] are almost-equal,
        // we can change word[i] to any character such that
        // both word[i-1] and word[i+1] are not almost-equal to word[i]
        const int n = word.size();
        int i = 1;
        int result = 0;
        while (i < n) {
            if (std::abs(word[i] - word[i - 1]) <= 1) {
                result++;
                i++;
            }
            i++;
        }
        return result;
    }

    // DP with space optimization, time O(N), space O(1)
    int approach2(std::string& word)
    {
        const int n = word.size();
        int iMinus1 = 0;
        int iMinus2 = 0;
        int dp = 0;
        for (int i = 2; i <= n; ++i) {
            if (std::abs(word[i - 1] - word[i - 2]) <= 1) {
                dp = std::min(iMinus1, iMinus2) + 1;
            } else {
                dp = iMinus1;
            }
            iMinus2 = iMinus1;
            iMinus1 = dp;
        }
        return dp;
    }

    // DP, time O(N), space O(N)
    int approach1(std::string& word)
    {
        // dp[i] = min num of operations to make word[0:i) valid
        // X X X i-2 i-1 i
        // if character i and i-1 are not almost-equal, then dp[i] = dp[i-1]
        // otherwise, we have two options:
        // - change character i, dp[i] = dp[i-1] + 1
        // - change character i-1, dp[i] = dp[i-2] + 1
        const int n = word.size();
        std::vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        dp[1] = 0;
        for (int i = 2; i <= n; ++i) {
            if (std::abs(word[i - 1] - word[i - 2]) <= 1) {
                dp[i] = std::min(dp[i - 1], dp[i - 2]) + 1;
            } else {
                dp[i] = dp[i - 1];
            }
        }
        return dp[n];
    }
};