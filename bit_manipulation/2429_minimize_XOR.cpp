/**
 * Given two positive integers num1 and num2, find the positive integer x such that:
 *
 * - x has the same number of set bits as num2, and
 *
 * - The value x XOR num1 is minimal.
 *
 * Note that XOR is the bitwise XOR operation.
 *
 * Return the integer x. The test cases are generated such that x is uniquely determined.
 *
 * The number of set bits of an integer is the number of 1's in its binary representation.
 *
 * ! 1 <= num1, num2 <= 10^9
 */

class Solution {
public:
    int minimizeXor(int num1, int num2)
    {
        const int m = numOfSetBits(num1);
        const int n = numOfSetBits(num2);
        if (m == n)
            return num1;

        if (m > n) {
            for (int i = 0; i < m - n; ++i) {
                num1 &= num1 - 1;
            }
            return num1;
        }
        for (int i = 0, j = 0; i < 32 && j < n - m; ++i) {
            if ((num1 >> i) & 1)
                continue;

            num1 |= 1 << i;
            j++;
        }
        return num1;
    }

private:
    int numOfSetBits(int n)
    {
        int result = 0;
        while (n) {
            result++;
            n &= n - 1;
        }
        return result;
    }
};