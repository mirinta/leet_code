#include <string>

/**
 * Given a string s containing only digits, return the
 * lexicographically smallest string that can be obtained after swapping adjacent digits in s with
 * the same parity at most once.
 *
 * Digits have the same parity if both are odd or both are even. For example, 5 and 9, as well as 2
 * and 4, have the same parity, while 6 and 9 do not.
 *
 * ! 2 <= s.length <= 100
 * ! s consists only of digits.
 */

class Solution {
public:
    std::string getSmallestString(std::string s)
    {
        const int n = s.size();
        for (int i = 1; i < n; ++i) {
            const int prev = s[i - 1] - '0';
            const int curr = s[i] - '0';
            if (prev % 2 == curr % 2 && curr < prev) {
                std::swap(s[i], s[i - 1]);
                break;
            }
        }
        return s;
    }
};