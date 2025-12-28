#include <string>
#include <unordered_map>

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
        static const std::unordered_map<char, char> map{{'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}};
        auto str = std::to_string(n);
        for (auto& c : str) {
            if (!map.count(c))
                return false;

            c = map.at(c);
        }
        std::reverse(str.begin(), str.end());
        return std::stoi(str) != n;
    }
};
