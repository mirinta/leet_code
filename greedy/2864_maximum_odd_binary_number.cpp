#include <string>

/**
 * You are given a binary string s that contains at least one '1'.
 *
 * You have to rearrange the bits in such a way that the resulting binary number is the maximum odd
 * binary number that can be created from this combination.
 *
 * Return a string representing the maximum odd binary number that can be created from the given
 * combination.
 *
 * Note that the resulting string can have leading zeros.
 *
 * ! 1 <= s.length <= 100
 * ! s consists only of '0' and '1'.
 * ! s contains at least one '1'.
 */

class Solution {
public:
    std::string maximumOddBinaryNumber(std::string s)
    {
        const int n = s.size();
        int ones = 0;
        for (const auto& c : s) {
            ones += c == '1';
        }
        std::string result(n, '0');
        result[n - 1] = '1';
        ones--;
        for (int i = 0; i < n - 1 && ones > 0; ++i, --ones) {
            result[i] = '1';
        }
        return result;
    }
};