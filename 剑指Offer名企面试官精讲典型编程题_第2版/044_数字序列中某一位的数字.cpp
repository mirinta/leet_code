#include <string>

/**
 * 数字以0123456789101112131415…的格式序列化到一个字符序列中。在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。
 *
 * 请写一个函数，求任意第n位对应的数字。
 *
 * ! 0 <= n < 2^31
 *
 * ! 本题与LC 400相同。
 */

class Solution {
public:
    int findNthDigit(int n)
    {
        if (n == 0)
            return 0;

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
