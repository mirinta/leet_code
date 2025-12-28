/**
 * Given an integer n, return true if it is a power of four. Otherwise, return false.
 *
 * An integer n is a power of four, if there exists an integer x such that n == 4x.
 *
 * ! -2^31 <= n <= 2^31 - 1
 *
 * ! Follow up: Could you solve it without loops/recursion?
 */

class Solution {
public:
    bool isPowerOfFour(int n)
    {
        //  n = 1, 0000 0001, bits[0]=1
        //  n = 4, 0000 0100, bits[2]=1
        // n = 16, 0001 0000, bits[4]=1
        // n = 64, 0100 0000, bits[6]=1
        if (n <= 0)
            return false;

        if (n & (n - 1))
            return false;

        return n & 0x55555555;
    }
};
