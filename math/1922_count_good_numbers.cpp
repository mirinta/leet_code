/**
 * A digit string is good if the digits (0-indexed) at even indices are even and the digits at odd
 * indices are prime (2, 3, 5, or 7).
 *
 * - For example, "2582" is good because the digits (2 and 8) at even positions are even and the
 * digits (5 and 2) at odd positions are prime. However, "3245" is not good because 3 is at an even
 * index but is not even.
 *
 * Given an integer n, return the total number of good digit strings of length n. Since the answer
 * may be large, return it modulo 10^9 + 7.
 *
 * A digit string is a string consisting of digits 0 through 9 that may contain leading zeros.
 *
 * ! 1 <= n <= 10^15
 */

class Solution {
public:
    int countGoodNumbers(long long n)
    {
        return fastPowMod(4, n / 2) * fastPowMod(5, (n + 1) / 2) % kMod;
    }

private:
    static const long long kMod = 1e9 + 7;

    long long fastPowMod(long long a, long long b)
    {
        long long result = 1;
        long long base = a;
        while (b > 0) {
            if (b & 1) {
                result = result * base % kMod;
            }
            base = base * base % kMod;
            b >>= 1;
        }
        return result;
    }
};
