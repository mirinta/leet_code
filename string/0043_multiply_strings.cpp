#include <algorithm>
#include <string>

/**
 * Given two non-negative integers "num1" and "num2" represented as strings, return the product of
 * "num1" and "num2", also represented as a string.
 *
 * Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.
 *
 * ! num1 and num2 consist of digits only.
 *
 * ! Both num1 and num2 do not contain any leading zero, except the number 0 itself.
 */

class Solution {
public:
    std::string multiply(std::string& num1, std::string& num2)
    {
        if (num1.empty() || num2.empty())
            return {};

        if (num1 == k_zero || num2 == k_zero)
            return k_zero;

        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(), num2.end());
        std::string result(k_zero);
        for (size_t i = 0; i < num2.size(); ++i) {
            result = add(result, std::string(i, k_digit_0) + multiplyOneDigit(num1, num2[i]));
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

private:
    static constexpr int k_base = 10;
    static constexpr char k_digit_0 = '0';
    const std::string k_zero = "0";

    // input and output strings are in reverse order
    std::string multiplyOneDigit(const std::string& num, char digit)
    {
        const int val = digit - k_digit_0;
        if (val == 0)
            return k_zero;

        std::string result;
        int carry = 0;
        for (const auto& c : num) {
            const auto product = (c - k_digit_0) * val + carry;
            carry = product / k_base;
            result.push_back(product % k_base + k_digit_0);
        }
        if (carry > 0) {
            result.push_back(carry + k_digit_0);
        }
        return result;
    }

    char addDigits(int& carry, char c1, char c2)
    {
        const int sum = carry + (c1 - k_digit_0) + (c2 - k_digit_0);
        carry = sum / k_base;
        return sum % k_base + k_digit_0;
    }

    // input and output strings are in reverse order
    std::string add(const std::string& num1, const std::string& num2)
    {
        if (num1 == k_zero)
            return num2;

        if (num2 == k_zero)
            return num1;

        int carry = 0;
        int iter1 = 0;
        int iter2 = 0;
        std::string result;
        while (iter1 < num1.size() || iter2 < num2.size()) {
            if (iter1 >= num1.size()) {
                result.push_back(addDigits(carry, k_digit_0, num2[iter2++]));
                continue;
            }
            if (iter2 >= num2.size()) {
                result.push_back(addDigits(carry, num1[iter1++], k_digit_0));
                continue;
            }
            result.push_back(addDigits(carry, num1[iter1++], num2[iter2++]));
        }
        if (carry > 0) {
            result.push_back(carry + k_digit_0);
        }
        return result;
    }
};