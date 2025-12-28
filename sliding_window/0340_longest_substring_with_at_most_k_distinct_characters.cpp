#include <string>
#include <unordered_map>

/**
 * Given a string s and an integer k, return the length of the longest substring of s that contains
 * at most k distinct characters.
 *
 * ! 1 <= s.length <= 5 * 10^4
 * ! 0 <= k <= 50
 */

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(std::string s, int k)
    {
        const int n = s.size();
        if (n <= k)
            return n;

        std::unordered_map<char, int> map;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            map[s[right]]++;
            while (map.size() > k) {
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
