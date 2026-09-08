#include <algorithm>

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
 * ! 1 <= n <= 10^5
 */

class Solution {
public:
    int countCommas(int n)
    {
        return std::max(n - 999, 0);
    }
};
