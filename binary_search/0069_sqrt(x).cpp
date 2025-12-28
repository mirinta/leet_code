#include <climits>

/**
 * Given a non-negative integer x, return the square root of x rounded down to the nearest integer.
 * The returned integer should be non-negative as well.
 *
 * You must not use any built-in exponent function or operator.
 *
 * - For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.
 *
 * ! 0 <= num <= 2^31 - 1
 */

class Solution {
public:
    int mySqrt(int x)
    {
        int lo = 0;
        int hi = INT_MAX;
        while (lo <= hi) {
            const long long mid = lo + (hi - lo) / 2;
            const long long square = mid * mid;
            if (square == x)
                return mid;

            if (square > x) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return hi; // round down to the nearest integer, it means square < x
    }
};
