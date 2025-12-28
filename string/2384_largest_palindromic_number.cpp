#include <array>
#include <string>

/**
 * You are given a string num consisting of digits only.
 *
 * Return the largest palindromic integer (in the form of a string) that can be formed using digits
 * taken from num. It should not contain leading zeroes.
 *
 * Notes:
 *
 * - You do not need to use all the digits of num, but you must use at least one digit.
 *
 * - The digits can be reordered.
 *
 * ! 1 <= num.length <= 10^5
 * ! num consists of digits.
 */

class Solution {
public:
    std::string largestPalindromic(std::string num)
    {
        std::array<int, 10> count{};
        for (const auto& c : num) {
            count[c - '0']++;
        }
        std::string mid;
        for (int i = 9; i >= 0; --i) {
            if (count[i] % 2) {
                mid.push_back(i + '0');
                break;
            }
        }
        std::string left;
        for (int i = 9; i >= 0; --i) {
            if (count[i] >= 2) {
                left.insert(left.end(), count[i] / 2, i + '0');
            }
        }
        int i = 0;
        while (i < left.size() && left[i] == '0') {
            i++;
        }
        if (i == left.size() && mid.empty())
            return "0";

        if (i == left.size() && !mid.empty())
            return mid;

        std::string result(left.begin() + i, left.end());
        result.append(mid);
        result.insert(result.end(), left.rbegin(), left.rend() - i);
        return result.empty() ? "0" : result;
    }
};