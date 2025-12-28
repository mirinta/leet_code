#include <string>

/**
 * You are given a binary string s.
 *
 * You can perform the following operation on the string any number of times:
 *
 * - Choose any index i from the string where i + 1 < s.length such that s[i] == '1' and s[i + 1] ==
 * '0'.
 *
 * - Move the character s[i] to the right until it reaches the end of the string or another '1'.
 * For example, for s = "010010", if we choose i = 1, the resulting string will be s = "000110".
 *
 * Return the maximum number of operations that you can perform.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is either '0' or '1'.
 */

class Solution {
public:
    int maxOperations(std::string s)
    {
        // to perform the max num of operations
        // we need to traverse s from left to right
        // 1 1 ... 1 0 ...
        // |<--k-->| ^
        //           i
        // if s[i] = 0,
        // then we can move each s[j] = 1 one time (0 <= j < i)
        // - if the num of 1's within s[i+1:n-1] > 0, then we can apply the operation
        // - if the num of 1's within s[i+1:n-1] = 0, then we can move s[j] to the end of s
        const int n = s.size();
        int ones = 0;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            ones += s[i] == '1';
            if (s[i] == '0' && i > 0 && s[i - 1] == '1') {
                result += ones; // s[i-1] != 0 to prevent redundant calculations
            }
        }
        return result;
    }
};