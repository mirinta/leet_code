#include <string>

/**
 * A valid number can be split up into these components (in order):
 *
 * A decimal number or an integer.
 *
 * (Optional) An 'e' or 'E', followed by an integer.
 *
 * A decimal number can be split up into these components (in order):
 *
 * (Optional) A sign character (either '+' or '-').
 *
 * One of the following formats:
 * One or more digits, followed by a dot '.'.
 *
 * One or more digits, followed by a dot '.', followed by one or more digits.
 *
 * A dot '.', followed by one or more digits.
 *
 * An integer can be split up into these components (in order):
 *
 * (Optional) A sign character (either '+' or '-').
 *
 * One or more digits.
 *
 * Given a string s, return true if s is a valid number.
 *
 * For example, the following are valid numbers:
 * [2, 0089, -0.1, +3.14, 4., -.9, 2e10, -90E3, 3e+7, +6e-1, 53.5e93, -123.456e789]
 *
 * The following are not valid numbers:
 * [abc, 1a, 1e, e3, 99e2.5, --6, -+3, 95a54e53]
 *
 *  ! 1 <= s.length <= 20
 *  ! s consists of only English letters, digits, plus, minus, or dot.
 */

class Solution {
public:
    bool isNumber(const std::string& s)
    {
        if (s.empty())
            return false;

        // [sign][0-9][.][0-9][E][sign][0-9]
        bool seenDigit = false;
        bool seenExponent = false;
        bool seenDot = false;
        for (size_t i = 0; i < s.size(); ++i) {
            const auto& c = s[i];
            if (c >= '0' && c <= '9') {
                seenDigit = true;
            } else if (c == '+' || c == '-') {
                // valid position: the very beginning, or after exponent
                if (i > 0 && s[i - 1] != 'E' && s[i - 1] != 'e')
                    return false;

            } else if (c == 'E' || c == 'e') {
                // valid position: appear once and after digits
                if (seenExponent || !seenDigit)
                    return false;

                seenExponent = true;
                seenDigit = false; // check if there are digits following exponent
            } else if (c == '.') {
                // valid position: appear once and before exponent
                if (seenDot || seenExponent)
                    return false;

                seenDot = true;
            } else {
                // other characters are not valid
                return false;
            }
        }
        return seenDigit;
    }
};