#include <array>
#include <string>

/**
 * You are given a string s.
 *
 * You can perform the following process on s any number of times:
 *
 * - Choose an index i in the string such that there is at least one character to the left of index
 * i that is equal to s[i], and at least one character to the right that is also equal to s[i].
 *
 * - Delete the closest character to the left of index i that is equal to s[i].
 *
 * - Delete the closest character to the right of index i that is equal to s[i].
 *
 * Return the minimum length of the final string s that you can achieve.
 *
 * ! 1 <= s.length <= 2 * 10^5
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    int minimumLength(std::string s)
    {
        std::array<int, 26> count{};
        for (const auto& c : s) {
            count[c - 'a']++;
        }
        int result = 0;
        for (const auto& freq : count) {
            if (freq == 0)
                continue;

            result += freq % 2 ? 1 : 2;
        }
        return result;
    }
};
