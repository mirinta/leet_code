#include <string>
#include <unordered_map>

/**
 * Given a string s, your task is to find the length of the longest self-contained substring of s.
 *
 * A substring t of a string s is called self-contained if t != s and for every character in t, it
 * doesn't exist in the rest of s.
 *
 * Return the length of the longest self-contained substring of s if it exists, otherwise, return
 * -1.
 *
 * ! 2 <= s.length <= 5 * 10^4
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    int maxSubstringLength(std::string s)
    {
        const int n = s.size();
        std::unordered_map<char, std::pair<int, int>> map;
        for (int i = 0; i < n; ++i) {
            if (!map.count(s[i])) {
                map[s[i]] = {i, i};
            } else {
                map[s[i]].second = i;
            }
        }
        int result = -1;
        for (const auto& [c, info] : map) {
            int end = info.second;
            for (int i = info.first; i < n; ++i) {
                if (map[s[i]].first < info.first)
                    break;

                end = std::max(end, map[s[i]].second);
                if (end == i && end - info.first + 1 < n) {
                    result = std::max(result, end - info.first + 1);
                }
            }
        }
        return result;
    }
};
