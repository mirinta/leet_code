#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given an array of words where each word consists of lowercase English letters.
 *
 * wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA
 * without changing the order of the other characters to make it equal to wordB.
 *
 * - For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
 *
 * A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a
 * predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a
 * word chain with k == 1.
 *
 * Return the length of the longest possible word chain with words chosen from the given list of
 * words.
 *
 * ! 1 <= words.length <= 1000
 * ! 1 <= words[i].length <= 16
 * ! words[i] only consists of lowercase English letters.
 */

class Solution {
public:
    int longestStrChain(std::vector<std::string>& words)
    {
        // dp[i] = length of the longest word chain chosen from words[0:i] that ending at words[i]
        const int n = words.size();
        std::sort(words.begin(), words.end(), [](const auto& s1, const auto& s2) { return s1.size() < s2.size(); });
        std::unordered_map<std::string, int> map;
        std::vector<int> dp(n);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            dp[i] = 1;
            for (int j = 0; j < words[i].size(); ++j) {
                auto s = words[i];
                s.erase(s.begin() + j);
                if (map.count(s)) {
                    dp[i] = std::max(dp[i], dp[map[s]] + 1);
                }
            }
            map[words[i]] = i;
            result = std::max(result, dp[i]);
        }
        return result;
    }
};