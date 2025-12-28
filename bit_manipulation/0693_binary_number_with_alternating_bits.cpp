/**
 * Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits
 * will always have different values.
 *
 * ! 1 <= n <= 2^31 - 1
 */

class Solution {
public:
    bool hasAlternatingBits(int n)
    {
        while (n) {
            if ((n & 1) == ((n >> 1) & 1))
                return false;

            n >>= 1;
        }
        return true;
    }
};