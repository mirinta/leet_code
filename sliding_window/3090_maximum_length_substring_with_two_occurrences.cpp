#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given a string s, return the maximum length of a substring such that it contains at most two
 * occurrences of each character.
 *
 * ! 2 <= s.length <= 100
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    int maximumLengthSubstring(std::string s)
    {
        const int n = s.size();
        std::unordered_map<char, int> map;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            map[s[right]]++;
            while (map[s[right]] > 2) {
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