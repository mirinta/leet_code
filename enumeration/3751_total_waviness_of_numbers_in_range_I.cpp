#include <string>

/**
 * You are given two integers num1 and num2 representing an inclusive range [num1, num2].
 *
 * The waviness of a number is defined as the total count of its peaks and valleys:
 *
 * - A digit is a peak if it is strictly greater than both of its immediate neighbors.
 *
 * - A digit is a valley if it is strictly less than both of its immediate neighbors.
 *
 * - The first and last digits of a number cannot be peaks or valleys.
 *
 * - Any number with fewer than 3 digits has a waviness of 0.
 *
 * Return the total sum of waviness for all numbers in the range [num1, num2].
 *
 * ! 1 <= num1 <= num2 <= 10^5
 */

class Solution {
public:
    int totalWaviness(int num1, int num2)
    {
        int result = 0;
        for (int val = num1; val <= num2; ++val) {
            result += helper(val);
        }
        return result;
    }

private:
    int helper(int n)
    {
        const auto s = std::to_string(n);
        if (s.size() < 3)
            return 0;

        int count = 0;
        for (int i = 1; i < s.size() - 1; ++i) {
            const bool isPeak = s[i] > s[i + 1] && s[i] > s[i - 1];
            const bool isValley = s[i] < s[i + 1] && s[i] < s[i - 1];
            count += isPeak || isValley;
        }
        return count;
    }
};
