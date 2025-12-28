#include <vector>

/**
 * Given a 0-indexed 2D integer matrix grid of size n * m, we define a 0-indexed 2D matrix p of size
 * n * m as the product matrix of grid if the following condition is met:
 *
 * Each element p[i][j] is calculated as the product of all elements in grid except for the element
 * grid[i][j]. This product is then taken modulo 12345. Return the product matrix of grid.
 *
 * ! 1 <= n == grid.length <= 10^5
 * ! 1 <= m == grid[i].length <= 10^5
 * ! 2 <= n * m <= 10^5
 * ! 1 <= grid[i][j] <= 10^9
 */

class Solution {
public:
    std::vector<std::vector<int>> constructProductMatrix(std::vector<std::vector<int>>& grid)
    {
        // (a * b) % c = [(a % c) * (b % c)] %c
        const int m = grid.size();
        const int n = grid[0].size();
        constexpr int kMod = 12345;
        std::vector<long> nums(m * n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                nums[i * n + j] = grid[i][j];
            }
        }
        std::vector<long> prefix(m * n, 1);
        std::vector<long> suffix(m * n, 1);
        for (int i = 1; i < prefix.size(); ++i) {
            prefix[i] = prefix[i - 1] * nums[i - 1] % kMod;
        }
        for (int j = suffix.size() - 2; j >= 0; --j) {
            suffix[j] = suffix[j + 1] * nums[j + 1] % kMod;
        }
        std::vector<std::vector<int>> result(m, std::vector<int>(n, 1));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result[i][j] = prefix[i * n + j] * suffix[i * n + j] % kMod;
            }
        }
        return result;
    }
};
