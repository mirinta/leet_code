#include <string>
#include <unordered_map>

/**
 * Given a string s, return the length of the longest substring between two equal characters,
 * excluding the two characters. If there is no such substring return -1.
 *
 * A substring is a contiguous sequence of characters within a string.
 *
 * ! 1 <= s.length <= 300
 * ! s contains only lowercase English letters.
 */

class Solution {
public:
    int maxLengthBetweenEqualCharacters(std::string s)
    {
        const int n = s.size();
        std::unordered_map<char, int> map;
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            if (map.count(s[i])) {
                result = std::max(result, i - map[s[i]] - 1);
            } else {
                map[s[i]] = i;
            }
        }
        return result == INT_MIN ? -1 : result;
    }
};