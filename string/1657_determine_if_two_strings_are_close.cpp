#include <algorithm>
#include <array>
#include <string>

/**
 * Two strings are considered close if you can attain one from the other using the following
 * operations:
 *
 * - Operation 1: Swap any two existing characters.
 * For example, abcde -> aecdb
 *
 * - Operation 2: Transform every occurrence of one existing character into another existing
 * character, and do the same with the other character. For example, aacabb -> bbcbaa (all a's turn
 * into b's, and all b's turn into a's) You can use the operations on either string as many times as
 * necessary.
 *
 * Given two strings, word1 and word2, return true if word1 and word2 are close, and false
 * otherwise.
 *
 * ! 1 <= word1.length, word2.length <= 10^5
 * ! word1 and word2 contain only lowercase English letters.
 */

class Solution {
public:
    bool closeStrings(std::string word1, std::string word2)
    {
        if (word1.size() != word2.size())
            return false;

        std::array<int, 26> freq1{0};
        for (const auto& c : word1) {
            freq1[c - 'a']++;
        }
        std::array<int, 26> freq2{0};
        for (const auto& c : word2) {
            if (freq1[c - 'a'] == 0)
                return false;

            freq2[c - 'a']++;
        }
        std::sort(freq1.begin(), freq1.end());
        std::sort(freq2.begin(), freq2.end());
        for (int i = 0; i < 26; ++i) {
            if (freq1[i] != freq2[i])
                return false;
        }
        return true;
    }
};