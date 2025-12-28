#include <climits>
#include <cmath>

/**
 * Given an integer n, return true if it is a power of three. Otherwise, return false.
 *
 * An integer n is a power of three, if there exists an integer x such that n == 3^x.
 *
 * ! -2^31 <= n <= 2^31 - 1
 */

class Solution {
public:
    bool isPowerOfThree(int n)
    {
        return approach2(n);
    }

private:
    bool approach2(int n)
    {
        static const int max = std::pow(3, static_cast<int>(std::log(INT_MAX) / std::log(3)));
        return n > 0 && max % n == 0;
    }

    bool approach1(int n)
    {
        if (n < 1)
            return false;

        while (n % 3 == 0) {
            n /= 3;
        }
        return n == 1;
    }
};
