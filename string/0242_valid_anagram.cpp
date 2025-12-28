#include <string>
#include <unordered_map>

/**
 * Given two strings "s" and "t", return "true" if "t" is an anagram of "s", and "false" otherwise.
 *
 * An anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
 * typically using all the original letters exactly once.
 *
 * ! 1 <= s.length, t.length <= 5 * 10^4
 * ! s and t consist of lowercase English letters.
 */

class Solution {
public:
    bool isAnagram(std::string s, std::string t)
    {
        if (s.size() != t.size())
            return false;

        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            map[c]++;
        }
        for (const auto& c : t) {
            if (!map.count(c) || --map[c] < 0)
                return false;
        }
        return true;
    }
};