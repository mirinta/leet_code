#include <vector>

/**
 * You are given a large integer represented as an integer array "digits", where each digits[i] is
 * the ith digit of the integer. The digits are ordered from most significant to least significant
 * in left-to-right order. The large integer does not contain any leading 0's.
 *
 * Increment the large integer by one and return the resulting array of digits.
 *
 * ! 1 <= digits.length <= 100
 * ! 0 <= digits[i] <= 9
 * ! digits does not contain any leading 0's.
 */

class Solution {
public:
    std::vector<int> plusOne(std::vector<int>& digits)
    {
        if (digits.empty())
            return {};

        int carry = 1;
        for (int i = digits.size() - 1; i >= 0 && carry; --i) {
            if (digits[i] + carry < 10) {
                digits[i] += carry;
                carry = 0;
            } else {
                digits[i] = 0;
                carry = 1;
            }
        }
        if (carry) {
            digits.insert(digits.begin(), carry);
        }
        return digits;
    }
};