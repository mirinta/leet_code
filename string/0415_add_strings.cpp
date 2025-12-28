#include <string>

/**
 * Given two non-negative integers, num1 and num2 represented as string, return the sum of num1 and
 * num2 as a string.
 *
 * You must solve the problem without using any built-in library for handling large integers (such
 * as BigInteger). You must also not convert the inputs to integers directly.
 *
 * ! 1 <= num1.length, num2.length <= 10^4
 * ! num1 and num2 consist of only digits.
 * ! num1 and num2 don't have any leading zeros except for the zero itself.
 */

class Solution {
public:
    std::string addStrings(std::string num1, std::string num2)
    {
        int i1 = num1.size() - 1;
        int i2 = num2.size() - 1;
        int carry = 0;
        std::string result;
        while (i1 >= 0 || i2 >= 0) {
            const int val1 = i1 >= 0 ? num1[i1] - '0' : 0;
            const int val2 = i2 >= 0 ? num2[i2] - '0' : 0;
            const int sum = val1 + val2 + carry;
            result.push_back('0' + sum % 10);
            carry = sum / 10;
            i1--;
            i2--;
        }
        if (carry > 0) {
            result.push_back(carry + '0');
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};