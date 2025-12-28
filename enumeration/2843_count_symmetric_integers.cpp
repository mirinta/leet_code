/**
 * You are given two positive integers low and high.
 *
 * An integer x consisting of 2 * n digits is symmetric if the sum of the first n digits of x is
 * equal to the sum of the last n digits of x. Numbers with an odd number of digits are never
 * symmetric.
 *
 * Return the number of symmetric integers in the range [low, high].
 *
 * ! 1 <= low <= high <= 10^4
 */

class Solution {
public:
    int countSymmetricIntegers(int low, int high)
    {
        int result = 0;
        for (int i = low; i <= high; ++i) {
            result += isValid(i);
        }
        return result;
    }

private:
    bool isValid(int x)
    {
        const int n = numOfDigits(x);
        if (n % 2)
            return false;

        int half = 0;
        int total = 0;
        for (int i = 0; i < n; ++i) {
            const int d = x % 10;
            total += d;
            if (i < n / 2) {
                half += d;
            }
            x /= 10;
        }
        return 2 * half == total;
    }

    int numOfDigits(int x)
    {
        if (x == 0)
            return 1;

        int result = 0;
        while (x) {
            result++;
            x /= 10;
        }
        return result;
    }
};
