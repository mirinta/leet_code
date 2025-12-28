#include <string>

/**
 * Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer
 * (similar to C/C++'s atoi function).
 *
 * The algorithm for myAtoi(string s) is as follows:
 *
 * Read in and ignore any leading whitespace.
 *
 * Check if the next character (if not already at the end of the string) is '-' or '+'. Read this
 * character in if it is either. This determines if the final result is negative or positive
 * respectively. Assume the result is positive if neither is present.
 *
 * Read in next the characters until the next non-digit character or the end of the input is
 * reached. The rest of the string is ignored.
 *
 * Convert these digits into an integer (i.e., "123" -> 123, "0032" -> 32). If no digits were read,
 * then the integer is 0. Change the sign as necessary (from step 2).
 *
 * If the integer is out of the 32-bit signed integer range [-2^32, 2^31-1], then clamp the integer
 * so that it remains in the range. Specifically, integers less that -2^32 should be clamped to
 * -2^31, and integers greater than 2^31-1 should be clamped to 2^31-1.
 *
 * Return the integer as the final result.
 *
 * Note:
 *
 * - Only the space character ' ' is considered a whitespace character.
 *
 * - Do not ignore any characters other than the leading whitespace or the rest of the string after
 * the digits.
 *
 * ! 0 <= s.length <= 200
 * ! s consists of English letters, digits (0-9), ' ', '+', '-', and '.'.
 */

class Solution {
public:
    int myAtoi(const std::string& s)
    {
        if (s.empty())
            return 0;

        const auto n = s.size();
        int i = 0;
        while (i < n && s[i] == ' ') {
            i++;
        }
        if (i == n)
            return 0;

        int sign = 1;
        if (s[i] == '+') {
            i++;
        } else if (s[i] == '-') {
            i++;
            sign = -1;
        }
        if (i == n)
            return 0;

        long result = 0;
        while (i < n && s[i] >= '0' && s[i] <= '9') {
            result = result * 10 + (s[i] - '0');
            if (result > INT_MAX)
                break;

            i++;
        }
        if (static_cast<int>(result) != result)
            return sign == 1 ? INT_MAX : INT_MIN;

        return sign * result;
    }
};