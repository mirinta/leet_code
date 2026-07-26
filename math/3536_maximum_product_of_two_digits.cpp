#include <utility>

/**
 * You are given a positive integer n.
 *
 * Return the maximum product of any two digits in n.
 *
 * Note: You may use the same digit twice if it appears more than once in n.
 *
 * ! 10 <= n <= 10^9
 */

class Solution {
public:
    int maxProduct(int n)
    {
        int max = 0;
        int secondMax = 0;
        while (n) {
            const int digit = n % 10;
            if (digit > max) {
                std::swap(max, secondMax);
                max = digit;
            } else if (digit > secondMax) {
                secondMax = digit;
            }
            n /= 10;
        }
        return max * secondMax;
    }
};