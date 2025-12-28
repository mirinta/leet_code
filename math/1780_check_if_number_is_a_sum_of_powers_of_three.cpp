/**
 * Given an integer n, return true if it is possible to represent n as the sum of distinct powers of
 * three. Otherwise, return false.
 *
 * An integer y is a power of three if there exists an integer x such that y == 3^x.
 *
 * ! 1 <= n <= 10^7
 */

class Solution {
public:
    bool checkPowersOfThree(int n)
    {
        while (n > 0) {
            if (n % 3 == 2)
                return false;

            n /= 3;
        }
        return true;
    }
};
