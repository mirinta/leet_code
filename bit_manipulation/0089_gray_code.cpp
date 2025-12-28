#include <vector>

/**
 * An n-bit gray code sequence is a sequence of 2n integers where:
 *
 * - Every integer is in the inclusive range [0, 2n - 1],
 *
 * - The first integer is 0,
 *
 * - An integer appears no more than once in the sequence,
 *
 * - The binary representation of every pair of adjacent integers differs by exactly one bit, and
 *
 * - The binary representation of the first and last integers differs by exactly one bit.
 *
 * Given an integer n, return any valid n-bit gray code sequence.
 *
 * ! 1 <= n <= 16
 */

class Solution {
public:
    std::vector<int> grayCode(int n)
    {
        if (n <= 0)
            return {};

        std::vector<int> result{0, 1}; // n = 1
        for (int i = 2; i <= n; ++i) {
            const int size = result.size();
            for (int j = size - 1; j >= 0; --j) {
                result.push_back(result[j] + (1 << (i - 1)));
            }
        }
        return result;
    }
};