/**
 * You are given an integer n. Your task is to compute the GCD (greatest common divisor) of two values:
 *
 * - sumOdd: the sum of the smallest n positive odd numbers.
 *
 * - sumEven: the sum of the smallest n positive even numbers.
 *
 * Return the GCD of sumOdd and sumEven.
 *
 * ! 1 <= n <= 1000
 */

class Solution {
public:
    int gcdOfOddEvenSums(int n)
    {
        // 1, 3, 5, ..., 2k-1
        // 2, 4, 6, ..., 2k
        // sumOdd = n * n;
        // sumEven = (n + 1) * n
        // gcd(sumOdd, sumEven) = n
        return n;
    }
};