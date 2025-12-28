#include <string>

/**
 * You are given a 0-indexed string s typed by a user. Changing a key is defined as using a key
 * different from the last used key. For example, s = "ab" has a change of a key while s = "bBBb"
 * does not have any.
 *
 * Return the number of times the user had to change the key.
 *
 * Note: Modifiers like shift or caps lock won't be counted in changing the key that is if a user
 * typed the letter 'a' and then the letter 'A' then it will not be considered as a changing of key.
 *
 * ! 1 <= s.length <= 100
 * ! s consists of only upper case and lower case English letters.
 */

class Solution {
public:
    int countKeyChanges(std::string s)
    {
        const int n = s.size();
        int result = 0;
        for (int i = 1; i < n; ++i) {
            if (std::tolower(s[i]) != std::tolower(s[i - 1])) {
                result++;
            }
        }
        return result;
    }
};