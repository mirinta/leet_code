#include <string>

/**
 * You are given a string num representing a large integer. An integer is good if it meets the
 * following conditions:
 *
 * - It is a substring of num with length 3.
 *
 * - It consists of only one unique digit.
 *
 * Return the maximum good integer as a string or an empty string "" if no such integer exists.
 *
 * Note:
 *
 * - A substring is a contiguous sequence of characters within a string.
 *
 * - There may be leading zeroes in num or a good integer.
 *
 * ! 3 <= num.length <= 1000
 * ! num only consists of digits.
 */

class Solution {
public:
    std::string largestGoodInteger(std::string num)
    {
        int maxVal = INT_MIN;
        int maxIdx = -1;
        for (int i = 1; i + 1 < num.size(); ++i) {
            if (num[i] == num[i - 1] && num[i] == num[i + 1]) {
                const int value = (num[i - 1] - 'a') * 100 + (num[i] - 'a') * 10 + (num[i + 1] - 'a');
                if (value > maxVal) {
                    maxIdx = i;
                    maxVal = value;
                }
            }
        }
        return maxIdx == -1 ? "" : num.substr(maxIdx - 1, 3);
    }
};