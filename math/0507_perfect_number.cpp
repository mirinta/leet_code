/**
 * A perfect number is a positive integer that is equal to the sum of its positive divisors,
 * excluding the number itself. A divisor of an integer x is an integer that can divide x evenly.
 *
 * Given an integer n, return true if n is a perfect number, otherwise return false.
 *
 * ! 1 <= num <= 10^8
 */

class Solution {
public:
    bool checkPerfectNumber(int num)
    {
        if (num == 1)
            return false;

        int sum = 1;
        for (int f = 2; f * f <= num; ++f) {
            if (num % f)
                continue;

            sum += f;
            if (num / f != f) {
                sum += num / f;
            }
        }
        return sum == num;
    }
};