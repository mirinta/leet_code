#include <string>
#include <unordered_set>
#include <vector>

/**
 * You are given a 0-indexed string s and a dictionary of words dictionary. You have to break s into
 * one or more non-overlapping substrings such that each substring is present in dictionary. There
 * may be some extra characters in s which are not present in any of the substrings.
 *
 * Return the minimum number of extra characters left over if you break up s optimally.
 *
 * ! 1 <= s.length <= 50
 * ! 1 <= dictionary.length <= 50
 * ! 1 <= dictionary[i].length <= 50
 * ! dictionary[i] and s consists of only lowercase English letters
 * ! dictionary contains distinct words
 */

class Solution {
public:
    int minExtraChar(std::string s, std::vector<std::string>& dictionary)
    {
        const int n = s.size();
        std::unordered_set<std::string> words(dictionary.begin(), dictionary.end());
        // dp[i] = min num of extra characters left over if we break up s[0:i) optimally
        // X X X X X j-1 j X X X i-1 i
        // |<--dp[j]-->| |<--word->|
        // |<--------dp[i]-------->|
        std::vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                dp[i] = std::min(dp[i], dp[j] + i - j);
                if (words.count(s.substr(j, i - j))) {
                    dp[i] = std::min(dp[i], dp[j]);
                }
            }
        }
        return dp[n];
    }
};