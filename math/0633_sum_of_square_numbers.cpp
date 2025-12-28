/**
 * Given a non-negative integer c, decide whether there're two integers a and b such that a2 + b2 =
 * c.
 *
 * ! 0 <= c <= 2^31 - 1
 */

class Solution {
public:
    bool judgeSquareSum(int c)
    {
        for (long long a = 0; a * a <= c; ++a) {
            if (isValid(static_cast<long long>(c) - a * a))
                return true;
        }
        return false;
    }

private:
    // check if n == x * x
    bool isValid(long long n)
    {
        long long lo = 0;
        long long hi = n;
        while (lo <= hi) {
            const long long mid = lo + (hi - lo) / 2;
            const long long square = mid * mid;
            if (square == n)
                return true;

            if (square > n) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return false;
    }
};