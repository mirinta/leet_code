#include <string>

/**
 * Given a string n representing an integer, return the closest integer (not including itself),
 * which is a palindrome. If there is a tie, return the smaller one.
 *
 * The closest is defined as the absolute difference minimized between two integers.
 *
 * ! 1 <= n.length <= 18
 * ! n consists of only digits.
 * ! n does not have leading zeros.
 * ! n is representing an integer in the range [1, 10^18 - 1].
 */

class Solution {
public:
    std::string nearestPalindromic(std::string n)
    {
        const auto smaller = smallerPalindrome(n);
        const auto greater = greaterPalindrome(n);
        const long long num = std::stoll(n);
        if (num - std::stoll(smaller) <= std::stoll(greater) - num)
            return smaller;

        return greater;
    }

private:
    std::string smallerPalindrome(const std::string& s)
    {
        const int n = s.size();
        std::string result(s);
        for (int i = 0, j = n - 1; i <= j; ++i, --j) {
            result[j] = result[i];
        }
        if (result < s)
            return result;

        int carry = 1;
        for (int i = n / 2 - (1 - n % 2); i >= 0; --i) {
            const int x = result[i] - '0' - carry;
            if (x >= 0) {
                result[i] = x + '0';
                carry = 0;
            } else {
                result[i] = '9';
                carry = 1;
            }
            result[n - 1 - i] = result[i];
        }
        if (result.front() == '0' && n > 1)
            return std::string(n - 1, '9');

        return result;
    }

    std::string greaterPalindrome(const std::string& s)
    {
        const int n = s.size();
        std::string result(s);
        for (int i = 0, j = n - 1; i <= j; ++i, --j) {
            result[j] = result[i];
        }
        if (result > s)
            return result;

        int carry = 1;
        for (int i = n / 2 - (1 - n % 2); i >= 0; --i) {
            const int x = result[i] - '0' + carry;
            if (x <= 9) {
                result[i] = x + '0';
                carry = 0;
            } else {
                result[i] = '0';
                carry = 1;
            }
            result[n - 1 - i] = result[i];
        }
        if (carry == 1) {
            result = std::string(n + 1, '0');
            result.front() = '1';
            result.back() = '1';
        }
        return result;
    }
};