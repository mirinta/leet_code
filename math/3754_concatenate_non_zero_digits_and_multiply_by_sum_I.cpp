/**
 * You are given an integer n.
 *
 * Form a new integer x by concatenating all the non-zero digits of n in their original order. If there are no non-zero
 * digits, x = 0.
 *
 * Let sum be the sum of digits in x.
 *
 * Return an integer representing the value of x * sum.
 *
 * ! 0 <= n <= 10^9
 */

class Solution {
public:
    long long sumAndMultiply(int n)
    {
        long long x = 0;
        long long sum = 0;
        long long base = 1;
        while (n) {
            const long long r = n % 10;
            sum += r;
            if (r) {
                x += r * base;
                base *= 10;
            }
            n /= 10;
        }
        return x * sum;
    }
};