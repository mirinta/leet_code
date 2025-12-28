#include <string>
#include <unordered_map>

/**
 * Given the string s, return the size of the longest substring containing each vowel an even number
 * of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.
 *
 * ! 1 <= s.length <= 5 x 10^5
 * ! s contains only lowercase English letters.
 */

class Solution {
public:
    int findTheLongestSubstring(std::string s)
    {
        // state[0] = whether the appearances of 'a' is an odd number
        // state[1] = whether the appearances of 'e' is an odd number
        // state[2] = whether the appearances of 'i' is an odd number
        // state[3] = whether the appearances of 'o' is an odd number
        // state[4] = whether the appearances of 'u' is an odd number
        const int n = s.size();
        int state = 0;
        std::unordered_map<int, int> map;
        map[0] = -1;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            state ^= getState(s[i]);
            if (map.count(state)) {
                result = std::max(result, i - map[state]);
            } else {
                map[state] = i;
            }
        }
        return result;
    }

private:
    int getState(char c)
    {
        switch (c) {
            case 'a':
                return 1;
            case 'e':
                return 1 << 1;
            case 'i':
                return 1 << 2;
            case 'o':
                return 1 << 3;
            case 'u':
                return 1 << 4;
            default:
                break;
        }
        return 0;
    }
};