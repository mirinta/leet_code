#include <string>

/**
 * Given an integer x, return true if x is a palindrome, and false otherwise.
 *
 * ! -2^31 <= x <= 2^31 - 1
 *
 * ! Follow up: Could you solve it without converting the integer to a string?
 */

class Solution {
public:
    bool isPalindrome(int x)
    {
        if (x < 0 || (x % 10 == 0 && x != 0))
            return false;

        int reverse = 0;
        while (x > reverse) {
            reverse = reverse * 10 + x % 10;
            x /= 10;
        }
        // x = 12321, after the while loop, x = 12 and reverse = 123
        // x = 1221, after the while loop, x = 12 and reverse = 12
        return x == reverse || reverse / 10 == x;
    }
};