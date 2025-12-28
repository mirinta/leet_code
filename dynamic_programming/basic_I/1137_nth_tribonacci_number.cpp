#include <utility>

/**
 * The Tribonacci sequence Tn is defined as follows:
 *
 * T0 = 0, T1 = 1, T2 = 1, and T(n+3) = T(n) + T(n+1) + T(n+2) for n >= 0.
 *
 * Given "n", return the value of T(n).
 *
 * ! 0 <= n <= 37
 * ! The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 - 1.
 */

class Solution {
public:
    int tribonacci(int n)
    {
        if (n < 3)
            return n == 0 ? 0 : 1;

        // f(i) = f(i-1) + f(i-2) +f(i-3)
        int iMinus1 = 1;
        int iMinus2 = 1;
        int iMinus3 = 0;
        int result = 0;
        for (int i = 3; i <= n; ++i) {
            result = iMinus1 + iMinus2 + iMinus3;
            iMinus3 = iMinus2;
            iMinus2 = iMinus1;
            iMinus1 = result;
        }
        return result;
    }
};