#include <string>

/**
 * You are given a string num, representing a large integer. Return the largest-valued odd integer
 * (as a string) that is a non-empty substring of num, or an empty string "" if no odd integer
 * exists.
 *
 * A substring is a contiguous sequence of characters within a string.
 *
 * ! 1 <= num.length <= 10^5
 * ! num only consists of digits and does not contain any leading zeros.
 */

class Solution {
public:
    std::string largestOddNumber(std::string num)
    {
        const int n = num.size();
        // find the rightmost odd value
        for (int i = n - 1; i >= 0; --i) {
            if ((num[i] - '0') % 2)
                return num.substr(0, i + 1);
        }
        return {};
    }
};