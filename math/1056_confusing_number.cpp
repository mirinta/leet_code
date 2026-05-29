#include <array>
#include <string>

/**
 * A confusing number is a number that when rotated 180 degrees becomes a different number with each
 * digit valid.
 *
 * We can rotate digits of a number by 180 degrees to form new digits.
 *
 * - When 0, 1, 6, 8, and 9 are rotated 180 degrees, they become 0, 1, 9, 8, and 6 respectively.
 *
 * - When 2, 3, 4, 5, and 7 are rotated 180 degrees, they become invalid.
 *
 * Note that after rotating a number, we can ignore leading zeros.
 *
 * - For example, after rotating 8000, we have 0008 which is considered as just 8.
 *
 * Given an integer n, return true if it is a confusing number, or false otherwise.
 *
 * ! 0 <= n <= 10^9
 */

class Solution {
public:
    bool confusingNumber(int n)
    {
        static constexpr std::array<int, 10> map{0, 1, -1, -1, -1, -1, 9, -1, 8, 6};
        const int origin = n;
        int rotated = 0;
        while (n) {
            const int d = n % 10;
            if (map[d] == -1)
                return false;

            rotated = rotated * 10 + map[d];
            n /= 10;
        }
        return origin != rotated;
    }
};
