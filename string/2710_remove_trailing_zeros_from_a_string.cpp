#include <string>

/**
 * Given a positive integer num represented as a string, return the integer num without trailing
 * zeros as a string.
 *
 * ! 1 <= num.length <= 1000
 * ! num consists of only digits.
 * ! num doesn't have any leading zeros.
 */

class Solution {
public:
    std::string removeTrailingZeros(std::string num)
    {
        while (!num.empty() && num.back() == '0') {
            num.pop_back();
        }
        return num;
    }
};