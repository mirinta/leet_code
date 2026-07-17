#include <functional>
#include <string>
#include <vector>

/**
 * A word's generalized abbreviation can be constructed by taking any number of non-overlapping and
 * non-adjacent substrings and replacing them with their respective lengths.
 *
 * For example, "abcde" can be abbreviated into:
 *
 * - "a3e" ("bcd" turned into "3")
 *
 * - "1bcd1" ("a" and "e" both turned into "1")
 *
 * - "5" ("abcde" turned into "5")
 *
 * - "abcde" (no substrings replaced)
 *
 * However, these abbreviations are invalid:
 *
 * - "23" ("ab" turned into "2" and "cde" turned into "3") is invalid as the substrings chosen are
 * adjacent.
 *
 * - "22de" ("ab" turned into "2" and "bc" turned into "2") is invalid as the substring chosen
 * overlap.
 *
 * Given a string word, return a list of all the possible generalized abbreviations of word. Return
 * the answer in any order.
 *
 * ! 1 <= word.length <= 15
 * ! word consists of only lowercase English letters.
 */

class Solution {
public:
    std::vector<std::string> generateAbbreviations(std::string& word)
    {
        const int n = word.size();
        std::string s;
        std::vector<std::string> result;
        std::function<void(int, bool)> backtrack = [&](int i, bool can) {
            if (i >= n) {
                result.emplace_back(s);
                return;
            }
            s.push_back(word[i]);
            backtrack(i + 1, true);
            s.pop_back();
            for (int len = 1, orgLen = s.size(); can && (i + len - 1 < n); ++len) {
                s.append(std::to_string(len));
                backtrack(i + len, false);
                s.resize(orgLen);
            }
        };
        backtrack(0, true);
        return result;
    }
};