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
    int minOperations(std::string s)
    {
        const int n = s.size();
        // case1: num of operations to make s valid and s[0] = 0
        // - elements at even indices must be 0
        // - elements at odd indices must be 1
        int case1 = 0;
        // case2: num of operations to make s valid and s[0] = 1
        // - elements at even indices must be 1
        // - elements at odd indices must be 0
        int case2 = 0;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                case1 += s[i] == '0' ? 0 : 1;
                case2 += s[i] == '1' ? 0 : 1;
            } else {
                case1 += s[i] == '1' ? 0 : 1;
                case2 += s[i] == '0' ? 0 : 1;
            }
        }
        return std::min(case1, case2);
    }
};