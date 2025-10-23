#include <string>
#include <vector>

/**
 * You are given a string s consisting of digits. Perform the following operation repeatedly until
 * the string has exactly two digits:
 *
 * - For each pair of consecutive digits in s, starting from the first digit, calculate a new digit
 * as the sum of the two digits modulo 10.
 *
 * - Replace s with the sequence of newly calculated digits, maintaining the order in which they are
 * computed.
 *
 * Return true if the final two digits in s are the same; otherwise, return false.
 *
 * ! 3 <= s.length <= 100
 * ! s consists of only digits.
 */

class Solution
{
public:
    bool hasSameDigits(std::string s)
    {
        const int n = s.size();
        std::vector<std::vector<int>> mat(n - 1, std::vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            mat[0][i] = s[i] - '0';
        }
        for (int i = 1; i < n - 1; ++i) {
            for (int j = 0; j < n - i; ++j) {
                mat[i][j] = (mat[i - 1][j] + mat[i - 1][j + 1]) % 10;
            }
        }
        return mat.back()[0] == mat.back()[1];
    }
};
