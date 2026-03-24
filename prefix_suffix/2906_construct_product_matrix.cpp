#include <array>
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
        const int m = grid.size();
        const int n = grid[0].size();
        auto encode = [&](int i, int j) { return i * n + j; };
        std::vector<std::array<long long, 3>> data(m * n, {0, 1, 1}); // <origin, prefix, suffix>
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                data[encode(i, j)][0] = grid[i][j];
            }
        }
        for (int i = 1, j = m * n - 2; i < m * n && j >= 0; ++i, --j) {
            data[i][1] = data[i - 1][1] * data[i - 1][0] % kMod;
            data[j][2] = data[j + 1][2] * data[j + 1][0] % kMod;
        }
        std::vector<std::vector<int>> result(m, std::vector<int>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                const int k = encode(i, j);
                result[i][j] = data[k][1] * data[k][2] % kMod;
            }
        }
        return result;
    }

private:
    static constexpr long long kMod = 12345;
};
