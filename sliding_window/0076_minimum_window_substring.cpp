#include <string>
#include <unordered_map>

/**
 * Given two strings s and t of lengths m and n respectively, return the minimum window
 * substring of s such that every character in t (including duplicates) is included in the window.
 * If there is no such substring, return the empty string "".
 *
 * The testcases will be generated such that the answer is unique.
 *
 * ! m == s.length
 * ! n == t.length
 * ! 1 <= m, n <= 10^5
 * ! s and t consist of uppercase and lowercase English letters.
 */

class Solution {
public:
    std::string minWindow(std::string s, std::string t)
    {
        if (s.size() < t.size())
            return {};

        const int n = s.size();
        std::unordered_map<char, int> map;
        for (const auto& c : t) {
            map[c]++;
        }
        int distinct = 0;
        int startIndex = -1;
        int minLength = INT_MAX;
        for (int left = 0, right = 0; right < n; ++right) {
            if (map.count(s[right]) && --map[s[right]] == 0) {
                distinct++;
            }
            while (distinct == map.size()) {
                if (right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    startIndex = left;
                }
                if (map.count(s[left]) && map[s[left]]++ == 0) {
                    distinct--;
                }
                left++;
            }
        }
        return minLength == INT_MAX ? "" : s.substr(startIndex, minLength);
    }
};
