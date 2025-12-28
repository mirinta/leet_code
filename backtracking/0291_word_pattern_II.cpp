#include <string>
#include <unordered_map>

/**
 * Given a pattern and a string s, return true if s matches the pattern.
 *
 * A string s matches a pattern if there is some bijective mapping of single characters to non-empty
 * strings such that if each character in pattern is replaced by the string it maps to, then the
 * resulting string is s. A bijective mapping means that no two characters map to the same string,
 * and no character maps to two different strings.
 *
 * ! 1 <= pattern.length, s.length <= 20
 * ! pattern and s consist of only lowercase English letters.
 */

class Solution {
public:
    bool wordPatternMatch(std::string pattern, std::string s)
    {
        std::unordered_map<char, std::string> map;
        return backtrack(map, 0, 0, pattern, s);
    }

private:
    // check if s[j::] matches pattern[i::]
    bool backtrack(std::unordered_map<char, std::string>& map,
                   int i,
                   int j,
                   const std::string& pattern,
                   const std::string& s)
    {
        if (i == pattern.size() || j == s.size())
            return j == s.size() && i == pattern.size();

        if (map.count(pattern[i])) {
            if (s.substr(j, map[pattern[i]].size()) != map[pattern[i]])
                return false;

            return backtrack(map, i + 1, j + map[pattern[i]].size(), pattern, s);
        }
        for (int k = j; k < s.size(); ++k) {
            const auto sub = s.substr(j, k - j + 1);
            bool isValid = true;
            for (const auto& [key, val] : map) {
                if (val == sub) {
                    isValid = false;
                    break;
                }
            }
            if (!isValid)
                continue;

            map[pattern[i]] = sub;
            if (backtrack(map, i + 1, k + 1, pattern, s))
                return true;

            map.erase(pattern[i]);
        }
        return false;
    }
};