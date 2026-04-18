#include <cmath>

/**
 * You are given an integer n.
 *
 * Define its mirror distance as: abs(n - reverse(n)) where reverse(n) is the integer formed by reversing the digits of
 * n.
 *
 * Return an integer denoting the mirror distance of n.
 *
 * abs(x) denotes the absolute value of x.
 *
 * ! 1 <= n <= 10^9
 */

class Solution {
public:
    int mirrorDistance(int n)
    {
        return std::abs(reverse(n) - n);
    }

private:
    int reverse(int n)
    {
        int result = 0;
        while (n) {
            result = result * 10 + n % 10;
            n /= 10;
        }
        return result;
    }
};