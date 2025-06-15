#include <algorithm>
#include <string>

/**
 * You are given an integer num. You know that Bob will sneakily remap one of the 10 possible digits
 * (0 to 9) to another digit.
 *
 * Return the difference between the maximum and minimum values Bob can make by remapping exactly
 * one digit in num.
 *
 * Notes:
 *
 * - When Bob remaps a digit d1 to another digit d2, Bob replaces all occurrences of d1 in num with
 * d2.
 *
 * - Bob can remap a digit to itself, in which case num does not change.
 *
 * - Bob can remap different digits for obtaining minimum and maximum values respectively.
 *
 * - The resulting number after remapping can contain leading zeroes.
 *
 * ! 1 <= num <= 10^8
 */

class Solution
{
public:
    int minMaxDifference(int num)
    {
        auto max = std::to_string(num);
        auto pos = max.find_first_not_of('9');
        if (pos != std::string::npos) {
            const auto change1 = max[pos];
            std::replace(max.begin(), max.end(), change1, '9');
        }
        auto min = std::to_string(num);
        const auto change2 = min[0];
        std::replace(min.begin(), min.end(), change2, '0');
        return std::stoi(max) - std::stoi(min);
    }
};
