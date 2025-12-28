#include <cstdint>

/**
 * Given a positive integer "num", return "true" if "num" is a perfect square or "false" otherwise.
 *
 * A perfect square is an integer that is the square of an integer. In other words, it is the
 * product of some integer with itself.
 *
 * You must not use any build-in library function, such as "sqrt".
 *
 * ! 1 <= num <= 2^31 - 1
 */

class Solution {
public:
    bool isPerfectSquare(int num)
    {
        if (num == 1)
            return true;

        int lo = 2;
        int hi = num / 2;
        while (lo <= hi) {
            const long long mid = lo + (hi - lo) / 2;
            const long long square = mid * mid;
            if (square == num)
                return true;

            if (square > num) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return false;
    }
};