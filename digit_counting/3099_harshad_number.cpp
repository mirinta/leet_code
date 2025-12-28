/**
 * An integer divisible by the sum of its digits is said to be a Harshad number. You are given an
 * integer x. Return the sum of the digits of x if x is a Harshad number, otherwise, return -1.
 *
 * ! 1 <= x <= 100
 */

class Solution {
public:
    int sumOfTheDigitsOfHarshadNumber(int x)
    {
        const int sum = sumOfDigits(x);
        return (x % sum) ? -1 : sum;
    }

private:
    int sumOfDigits(int x)
    {
        int result = 0;
        while (x) {
            result += x % 10;
            x /= 10;
        }
        return result;
    }
};