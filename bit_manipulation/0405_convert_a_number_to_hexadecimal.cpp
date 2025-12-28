#include <string>

/**
 * Given an integer num, return a string representing its hexadecimal representation. For negative
 * integers, two’s complement method is used.
 *
 * All the letters in the answer string should be lowercase characters, and there should not be any
 * leading zeros in the answer except for the zero itself.
 *
 * Note: You are not allowed to use any built-in library method to directly solve this problem.
 *
 * ! -2^31 <= num <= 2^31 - 1
 */

class Solution {
public:
    std::string toHex(int num)
    {
        static const std::string kBits{"0123456789abcdef"};
        if (num == 0)
            return "0";

        std::string result;
        unsigned val = num;
        while (val) {
            result.push_back(kBits[val % 16]);
            val /= 16;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};