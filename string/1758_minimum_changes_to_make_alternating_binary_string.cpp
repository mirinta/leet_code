#include <string>

/**
 * You are given a string s consisting only of the characters '0' and '1'. In one operation, you can
 * change any '0' to '1' or vice versa.
 *
 * The string is called alternating if no two adjacent characters are equal. For example, the string
 * "010" is alternating, while the string "0100" is not.
 *
 * Return the minimum number of operations needed to make s alternating.
 *
 * ! 1 <= s.length <= 10^4
 * ! s[i] is either '0' or '1'.
 */

class Solution {
public:
    int minOperations(std::string& s)
    {
        const int n = s.size();
        int count = 0; // start with 0
        for (int i = 0; i < n; ++i) {
            count += s[i] != i % 2 + '0';
        }
        return std::min(count, n - count);
    }
};
