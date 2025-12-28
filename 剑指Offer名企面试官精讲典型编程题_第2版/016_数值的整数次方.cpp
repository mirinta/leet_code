#include <climits>

/**
 * 实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，xn）。不得使用库函数，同时不需要考虑大数问题。
 *
 * ! -100.0 < x < 100.0
 * ! -2^31 <= n <= 2^31-1
 * ! -10^4 <= x^n <= 10^4
 *
 * ! 本题与LC 50相同。
 */

class Solution {
public:
    double myPow(double x, int n)
    {
        if (n == 0 || x == 1)
            return 1;

        if (x < 0) {
            const int sign = n % 2 == 0 ? 1 : -1;
            return sign * myPow(-x, n);
        }
        if (n < 0)
            return n == INT_MIN ? myPow(1 / x, INT_MAX) / x : myPow(1 / x, -n);

        if (n % 2 != 0)
            return x * myPow(x, n - 1);

        const double half = myPow(x, n / 2);
        return half * half;
    }
};
