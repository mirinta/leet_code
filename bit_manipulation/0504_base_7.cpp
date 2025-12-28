#include <string>

/**
 * Given an integer num, return a string of its base 7 representation.
 *
 * ! -10^7 <= num <= 10^7
 */

class Solution {
public:
    std::string convertToBase7(int num)
    {
        if (num < 0)
            return '-' + convertToBase7(-num);

        if (num < 7)
            return std::to_string(num);

        std::string result;
        while (num) {
            result.push_back(num % 7 + '0');
            num /= 7;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};