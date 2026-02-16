#include <cstdint>

/**
 * Reverse bits of a given 32 bits unsigned integer.
 *
 * ! 0 <= n <= 2^31 - 2
 * ! n is even.
 */

class Solution {
public:
    int reverseBits(int n)
    {
        int bits = 31;
        int result = 0;
        while (n) {
            result |= (n & 1) << bits;
            bits--;
            n >>= 1;
        }
        return result;
    }
};