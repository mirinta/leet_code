#include <string>
#include <unordered_map>
#include <vector>

/**
 * A sentence is a string of single-space separated words where each word consists only of lowercase
 * letters.
 *
 * A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the
 * other sentence.
 *
 * Given two sentences s1 and s2, return a list of all the uncommon words. You may return the answer
 * in any order.
 *
 * ! 1 <= s1.length, s2.length <= 200
 * ! s1 and s2 consist of lowercase English letters and spaces.
 * ! s1 and s2 do not have leading or trailing spaces.
 * ! All the words in s1 and s2 are separated by a single space.
 */

class Solution {
public:
    std::vector<std::string> uncommonFromSentences(std::string s1, std::string s2)
    {
        std::unordered_map<std::string, int> map;
        for (const auto& s : {s1, s2}) {
            int i = 0;
            while (i < s.size()) {
                while (i < s.size() && !std::isalpha(s[i])) {
                    i++;
                }
                int j = i + 1;
                while (j < s.size() && std::isalpha(s[j])) {
                    j++;
                }
                map[s.substr(i, j - i)]++;
                i = j;
            }
        }
        std::vector<std::string> result;
        for (const auto& [s, freq] : map) {
            if (freq == 1) {
                result.push_back(s);
            }
        }
        return result;
    }
};