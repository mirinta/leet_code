#include <climits>

/**
 * Implement pow(x, n) which calculates x raised to the power n (i.e., x^n)
 *
 * ! -2^31 <= n <= 2^31 - 1
 * ! n is an integer
 * ! Either x is not zero or n > 0.
 */

class Solution {
public:
    double myPow(double x, int n)
    {
        if (n == INT_MIN)
            return myPow(1 / x, INT_MAX) / x;

        if (n < 0)
            return myPow(1 / x, -n);

        double result = 1;
        double base = x;
        while (n > 0) {
            if (n & 1) {
                result *= base;
            }
            base *= base;
            n >>= 1;
        }
        return result;
    }
};
