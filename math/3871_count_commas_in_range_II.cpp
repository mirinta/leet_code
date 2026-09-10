/**
 * You are given an integer n.
 *
 * Return the total number of commas used when writing all integers from [1, n] (inclusive) in standard number
 * formatting.
 *
 * In standard formatting:
 *
 * - A comma is inserted after every three digits from the right.
 *
 * - Numbers with fewer than 4 digits contain no commas.
 *
 * ! 1 <= n <= 10^15
 */

class Solution {
public:
    long long countCommas(long long n)
    {
        // 1000-9999, #comma = 1
        // 10000-99999, #comma = 2 = 1 + 1
        // 100000-99999, #comma = 3 = 1 + 1 + 1
        long long x = 1000;
        long long result = 0;
        while (x <= n) {
            result += n - x + 1;
            x *= 1000;
        }
        return result;
    }
};
