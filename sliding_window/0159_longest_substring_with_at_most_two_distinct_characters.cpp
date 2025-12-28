#include <string>
#include <unordered_map>

/**
 * Given a string s, return the length of the longest substring that contains at most two distinct
 * characters.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of English letters.
 */

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(std::string s)
    {
        const int n = s.size();
        if (n <= 2)
            return n;

        std::unordered_map<char, int> map;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            map[s[right]]++;
            while (map.size() > 2) {
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
