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
    std::string addBinary(std::string a, std::string b)
    {
        if (a.empty() || b.empty())
            return a.empty() ? b : a;

        int i = a.size() - 1;
        int j = b.size() - 1;
        int carry = 0;
        std::string result;
        while (i >= 0 || j >= 0) {
            if (i < 0) {
                result.push_back(compute(carry, '0', b[j--]));
            } else if (j < 0) {
                result.push_back(compute(carry, a[i--], '0'));
            } else {
                result.push_back(compute(carry, a[i--], b[j--]));
            }
        }
        if (carry) {
            result.push_back(carry + '0');
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

private:
    char compute(int& carry, char c1, char c2)
    {
        const int sum = (c1 - '0') + (c2 - '0') + carry;
        carry = sum / 2;
        return sum % 2 + '0';
    }
};