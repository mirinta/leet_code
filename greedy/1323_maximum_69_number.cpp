#include <string>

/**
 * You are given a positive integer num consisting only of digits 6 and 9.
 *
 * Return the maximum number you can get by changing at most one digit (6 becomes 9, and 9 becomes
 * 6).
 *
 * ! 1 <= num <= 10^4
 * ! num consists of only 6 and 9 digits.
 */

class Solution
{
public:
    int maximum69Number(int num)
    {
        auto s = std::to_string(num);
        for (auto& c : s) {
            if (c == '6') {
                c = '9';
                break;
            }
        }
        return std::stoi(s);
    }
};