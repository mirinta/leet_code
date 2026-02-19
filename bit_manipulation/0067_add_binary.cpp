#include <algorithm>
#include <string>

/**
 * Given two binary strings "a" and "b", return their sum as a binary string.
 *
 * Example:
 * Input: a = "11", b = "1"
 * Output: "100"
 *
 * ! 1 <= a.length, b.length <= 10^4
 * ! a and b consist only of '0' or '1' characters.
 * ! Each string does not contain leading zeros except for the zero itself.
 */

class Solution {
public:
    std::string addBinary(std::string& a, std::string& b)
    {
        const int n1 = a.size();
        const int n2 = b.size();
        std::string result;
        int i = n1 - 1;
        int j = n2 - 1;
        int carry = 0;
        while (i >= 0 || j >= 0) {
            const int d1 = i < 0 ? 0 : a[i--] - '0';
            const int d2 = j < 0 ? 0 : b[j--] - '0';
            const int sum = d1 + d2 + carry;
            result.push_back(sum % 2 + '0');
            carry = sum / 2;
        }
        if (carry > 0) {
            result.push_back('1');
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};