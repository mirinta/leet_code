#include <cstdint>

/**
 * Write a function that takes the binary representation of an unsigned integer and returns the
 * number of '1' bits it has (also known as the Hamming weight).
 *
 * ! 1 <= n <= 2^31 - 1
 */

class Solution {
public:
    int hammingWeight(int n)
    {
        int result = 0;
        while (n) {
            result++;
            n &= n - 1;
        }
        return result;
    }
};
