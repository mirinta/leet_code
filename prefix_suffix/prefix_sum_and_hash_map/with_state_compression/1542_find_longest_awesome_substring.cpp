#include <string>
#include <unordered_map>

/**
 * You are given a string s. An awesome substring is a non-empty substring of s such that we can
 * make any number of swaps in order to make it a palindrome.
 *
 * Return the length of the maximum length awesome substring of s.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists only of digits.
 */

class Solution {
public:
    int longestAwesome(std::string s)
    {
        // similar to LC.1915
        const int n = s.size();
        std::unordered_map<int, int> map;
        map[0] = -1;
        int state = 0; // state[i] = whether the ith digit appear odd num of times
        int result = 0;
        for (int i = 0; i < n; ++i) {
            state ^= 1 << (s[i] - '0');
            // case 1: all digits in s[j+1:i] appear even num of times
            if (map.find(state) != map.end()) {
                result = std::max(result, i - map[state]);
            }
            // case 2: only one digit appears odd num of times
            // and other digits appear even num of times
            for (int k = 0; k < 10; ++k) {
                const int target = state ^ (1 << k);
                if (map.find(target) != map.end()) {
                    result = std::max(result, i - map[target]);
                }
            }
            if (map.find(state) == map.end()) {
                map[state] = i;
            }
        }
        return result;
    }
};