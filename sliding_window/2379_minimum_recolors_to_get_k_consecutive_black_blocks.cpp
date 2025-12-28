#include <string>

/**
 * You are given a 0-indexed string blocks of length n, where blocks[i] is either 'W' or 'B',
 * representing the color of the ith block. The characters 'W' and 'B' denote the colors white and
 * black, respectively.
 *
 * You are also given an integer k, which is the desired number of consecutive black blocks.
 *
 * In one operation, you can recolor a white block such that it becomes a black block.
 *
 * Return the minimum number of operations needed such that there is at least one occurrence of k
 * consecutive black blocks.
 *
 * ! n == blocks.length
 * ! 1 <= n <= 100
 * ! blocks[i] is either 'W' or 'B'.
 * ! 1 <= k <= n
 */

class Solution {
public:
    int minimumRecolors(std::string blocks, int k)
    {
        const int n = blocks.size();
        int result = n;
        for (int left = 0, right = 0, blacks = 0; right < n; ++right) {
            blacks += blocks[right] == 'B';
            if (right >= k) {
                blacks -= blocks[left++] == 'B';
            }
            if (right >= k - 1) {
                result = std::min(result, k - blacks);
            }
        }
        return result;
    }
};
