/**
 * Given an integer "num", repeatedly add all its digits until the result has only one digit, and
 * return it.
 */

class Solution {
public:
    int addDigits(int num)
    {
        constexpr int base = 10;
        if (num < base)
            return num;

        int result = 0;
        while (num) {
            result += num % base;
            num /= base;
            if (!num && result >= base) {
                num = result;
                result = 0;
            }
        }
        return result;
    }
};