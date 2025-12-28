#include <array>
#include <string>
#include <unordered_map>

/**
 * Given two strings s and t, determine if they are isomorphic.
 *
 * Two strings s and t are isomorphic if the characters in s can be replaced to get t.
 *
 * All occurrences of a character must be replaced with another character while preserving the order
 * of characters. No two characters may map to the same character, but a character may map to
 * itself.
 *
 * ! 1 <= s.length <= 5 * 10^4
 * ! t.length == s.length
 * ! s and t consist of any valid ascii character.
 */

class Solution {
public:
    bool isIsomorphic(std::string s, std::string t)
    {
        const int n = s.size();
        std::array<bool, 256> used{};
        std::unordered_map<char, char> map;
        for (int i = 0; i < n; ++i) {
            if (map.count(s[i]) && (map[s[i]] != t[i]))
                return false;

            if (!map.count(s[i]) && used[t[i]])
                return false;

            map[s[i]] = t[i];
            used[t[i]] = true;
        }
        return true;
    }
};