#include <string>

/**
 * Given an integer n, return the nth digit of the infinite integer sequence [1, 2, 3, 4, 5, 6, 7,
 * 8, 9, 10, 11, ...].
 *
 * ! 1 <= n <= 2^31 - 1
 */

class Solution {
public:
    int findNthDigit(int n)
    {
        // 1~9,     #digits = 1 * 9 * pow(10,0) = 9
        // 10~99,   #digits = 2 * 9 * pow(10,1) = 180
        // 100~999, #digits = 3 * 9 * pow(10,2) = 2700
        // ...      #digits = k * 9 * pow(10,k-1)
        int k = 1;
        long pow = 1;
        while (n > k * 9 * pow) {
            n -= k * 9 * pow;
            k++;
            pow *= 10;
        }
        // n = 11, after the above operations: n = 2, k = 2, pow = 10
        // - k = 2 means the target value is a 2 digits number
        // - n = 2 means the target digit is the 2nd digit (1-indexed) of {10|11|12...}
        // - target value = 10
        // - target index of the target value = 1 (0-indexed, from left to right)
        const int value = pow + (n - 1) / k;
        const int index = (n - 1) % k;
        return std::to_string(value)[index] - '0';
    }
};
