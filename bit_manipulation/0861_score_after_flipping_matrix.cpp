#include <numeric>
#include <vector>

/**
 * You are given an m x n binary matrix grid.
 *
 * A move consists of choosing any row or column and toggling each value in that row or column
 * (i.e., changing all 0's to 1's, and all 1's to 0's).
 *
 * Every row of the matrix is interpreted as a binary number, and the score of the matrix is the sum
 * of these numbers.
 *
 * Return the highest possible score after making any number of moves (including zero moves).
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 20
 * ! grid[i][j] is either 0 or 1.
 */

class Solution {
public:
    int matrixScore(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<int> nums(m);
        for (int i = 0; i < m; ++i) {
            int val = 0;
            for (int j = 0; j < n; ++j) {
                val = 2 * val + grid[i][j];
            }
            const int flipped = flip(val, n);
            nums[i] = flipped > val ? flipped : val;
        }
        for (int j = 0; j < n; ++j) {
            int ones = 0;
            for (const auto& val : nums) {
                ones += val >> (n - j - 1) & 1;
            }
            if (ones > m - ones)
                continue;

            for (auto& val : nums) {
                val ^= 1 << (n - j - 1);
            }
        }
        return std::accumulate(nums.begin(), nums.end(), 0);
    }

private:
    int flip(int val, int bits)
    {
        return (1 << bits) - 1 & (~val);
    }
};