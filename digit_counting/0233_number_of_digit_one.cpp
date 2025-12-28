#include <cmath>
#include <string>

/**
 * Given an integer n, count the total number of digit 1 appearing in all non-negative integers less
 * than or equal to n.
 *
 * ! 0 <= n <= 10^9
 */

class Solution {
public:
    int countDigitOne(int n)
    {
        // given the ith digit of n = n[i]
        // count the num of x such that x <= n and x[i] = 1
        // n (decimal): |<--LEFT-->| i |<--RIGHT-->|
        // x (decimal): |<-x_left->| 1 |<-x_right->|
        // if n[i] >= 2,
        // - x_left can be [0,LEFT], x_right can be any number with digits(RIGHT)
        // - e.g. digits of RIGHT = 3, then x_right can be [0,999]
        // - count = (LEFT+1) * 10^(digits of RIGHT)
        // if n[i] = 1,
        // - x_left can be [0,LEFT-1], x_right can be any number with digits(RIGHT)
        // - x_left can be LEFT, x_right can be [0,RIGHT]
        // - count = LEFT * 10^(digits of RIGHT) + (RIGHT+1)
        // if n[i] = 0,
        // - x_left can be [0,LEFT-1], x_right can be any number with digits(RIGHT)
        // - count = LEFT * 10^(digits of RIGHT)
        const auto s = std::to_string(n);
        int result = 0;
        long long powerOf10 = 1;
        for (int i = 0; i < s.size(); ++i, powerOf10 *= 10) {
            const int left = i == s.size() - 1 ? 0 : n / (powerOf10 * 10);
            const int right = i == 0 ? 0 : n % powerOf10;
            const int digit = s[s.size() - 1 - i] - '0';
            if (digit >= 2) {
                result += (left + 1) * powerOf10;
            } else if (digit == 1) {
                result += left * powerOf10 + right + 1;
            } else {
                result += left * powerOf10;
            }
        }
        return result;
    }
};