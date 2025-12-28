#include <algorithm>

/**
 * You are given two positive integers n and limit.
 *
 * Return the total number of ways to distribute n candies among 3 children such that no child gets
 * more than limit candies.
 *
 * ! 1 <= n <= 50
 * ! 1 <= limit <= 50
 */

class Solution {
public:
    int distributeCandies(int n, int limit)
    {
        int result = 0;
        for (int i = 0; i <= std::min(limit, n); ++i) {
            for (int j = 0; j <= limit && i + j <= n; ++j) {
                const int k = n - i - j;
                if (k <= limit && k >= 0) {
                    result++;
                }
            }
        }
        return result;
    }
};