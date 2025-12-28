#include <vector>

/**
 * No-Zero integer is a positive integer that does not contain any 0 in its decimal representation.
 *
 * Given an integer n, return a list of two integers [a, b] where:
 *
 * - a and b are No-Zero integers.
 *
 * - a + b = n
 *
 * The test cases are generated so that there is at least one valid solution. If there are many
 * valid solutions, you can return any of them.
 *
 * ! 2 <= n <= 10^4
 */

class Solution {
public:
    std::vector<int> getNoZeroIntegers(int n)
    {
        for (int a = 1; a <= n / 2; ++a) {
            if (isValid(a) && isValid(n - a))
                return {a, n - a};
        }
        return {};
    }

private:
    bool isValid(int val)
    {
        if (val == 0)
            return false;

        while (val) {
            if (val % 10 == 0)
                return false;

            val /= 10;
        }
        return true;
    }
};
