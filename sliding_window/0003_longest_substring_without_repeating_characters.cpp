#include <string>
#include <unordered_map>

/**
 * Given a string s, find the length of the longest substring without repeating characters.
 *
 * ! 0 <= s.length <= 5 * 10^4
 * ! s consists of English letters, digits, symbols and spaces.
 */

class Solution {
public:
    int lengthOfLongestSubstring(std::string s)
    {
        const int n = s.size();
        std::unordered_map<char, int> map;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            map[s[right]]++;
            while (map[s[right]] > 1) {
                if (--map[s[left]] == 0) {
                    map.erase(s[left]);
                }
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};
