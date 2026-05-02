#include <array>

/**
 * An integer x is a good if after rotating each digit individually by 180 degrees, we get a valid number that is
 * different from x. Each digit must be rotated - we cannot choose to leave it alone.
 *
 * A number is valid if each digit remains a digit after rotation. For example:
 *
 * - 0, 1, and 8 rotate to themselves,
 *
 * - 2 and 5 rotate to each other (in this case they are rotated in a different direction, in other words, 2 or 5 gets
 * mirrored),
 *
 * - 6 and 9 rotate to each other, and
 *
 * - the rest of the numbers do not rotate to any other number and become invalid.
 *
 * Given an integer n, return the number of good integers in the range [1, n].
 *
 * ! 1 <= n <= 10^4
 */

class Solution {
public:
    int rotatedDigits(int n)
    {
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            result += isValid(i);
        }
        return result;
    }

private:
    bool isValid(int n)
    {
        static constexpr std::array<int, 10> map{0, 1, 5, -1, -1, 2, 9, -1, 8, 6};
        bool changed = false;
        while (n) {
            const int d = n % 10;
            if (map[d] == -1)
                return false;

            changed |= map[d] != d;
            n /= 10;
        }
        return changed;
    }
};