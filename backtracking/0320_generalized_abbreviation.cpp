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
    std::vector<std::string> generateAbbreviations(std::string word)
    {
        std::string s;
        std::vector<std::string> result;
        backtrack(result, s, 0, true, word);
        backtrack(result, s, 0, false, word);
        return result;
    }

private:
    void backtrack(std::vector<std::string>& result,
                   std::string& s,
                   int i,
                   bool canBeAbbreviated,
                   const std::string& word)
    {
        if (i == word.size()) {
            result.push_back(s);
            return;
        }
        const int originalLength = s.size();
        for (int len = 1; len <= word.size() - i; ++len) {
            if (canBeAbbreviated) {
                s.append(std::to_string(len));
            } else {
                s.append(word.begin() + i, word.begin() + i + len);
            }
            backtrack(result, s, i + len, !canBeAbbreviated, word);
            s.erase(s.begin() + originalLength, s.end());
        }
    }
};