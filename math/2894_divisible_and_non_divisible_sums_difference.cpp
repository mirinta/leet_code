/**
 * You are given positive integers n and m.
 *
 * Define two integers, num1 and num2, as follows:
 *
 * - num1: The sum of all integers in the range [1, n] that are not divisible by m.
 *
 * - num2: The sum of all integers in the range [1, n] that are divisible by m.
 *
 * Return the integer num1 - num2.
 *
 * ! 1 <= n, m <= 1000
 */

class Solution {
public:
    int differenceOfSums(int n, int m)
    {
        // num1 + num2 = total
        // num1 - num2 = total - 2 * num2
        // num2 = m + 2m + 3m + ... + km, km <= n
        const int k = n / m;
        const int num2 = m * (1 + k) * k / 2;
        return (1 + n) * n / 2 - 2 * num2;
    }
};