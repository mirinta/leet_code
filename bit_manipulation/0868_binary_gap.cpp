#include <utility>

/**
 * Given a positive integer n, find and return the longest distance between any two adjacent 1's in
 * the binary representation of n. If there are no two adjacent 1's, return 0.
 *
 * Two 1's are adjacent if there are only 0's separating them (possibly no 0's). The distance
 * between two 1's is the absolute difference between their bit positions. For example, the two 1's
 * in "1001" have a distance of 3.
 *
 * ! 1 <= n <= 10^9
 */

class Solution {
public:
    int binaryGap(int n)
    {
        int prev = -1;
        int result = 0;
        for (int i = 0; n; ++i, n >>= 1) {
            if (n & 1) {
                if (prev >= 0) {
                    result = std::max(result, i - prev);
                }
                prev = i;
            }
        }
        return result;
    }
};