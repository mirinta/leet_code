#include <array>

/**
 * An integer x is numerically balanced if for every digit d in the number x, there are exactly d
 * occurrences of that digit in x.
 *
 * Given an integer n, return the smallest numerically balanced number strictly greater than n.
 *
 * ! 0 <= n <= 10^6
 */

class Solution {
public:
    int nextBeautifulNumber(int n)
    {
        for (int i = n + 1; i <= 1224444; ++i) {
            if (isValid(i))
                return i;
        }
        return -1;
    }

private:
    bool isValid(int n)
    {
        std::array<int, 10> count{};
        while (n) {
            count[n % 10]++;
            n /= 10;
        }
        for (int i = 0; i < 10; ++i) {
            if (count[i] > 0 && count[i] != i)
                return false;
        }
        return true;
    }
};