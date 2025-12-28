#include <vector>

/**
 * Given a 2D character matrix grid, where grid[i][j] is either 'X', 'Y', or '.', return the number
 * of submatrices that contain:
 *
 * - grid[0][0]
 *
 * - an equal frequency of 'X' and 'Y'.
 *
 * - at least one 'X'.
 *
 * ! 1 <= grid.length, grid[i].length <= 1000
 * ! grid[i][j] is either 'X', 'Y', or '.'.
 */

class Prefix2D {
public:
    Prefix2D(char c, int m, int n, const std::vector<std::vector<char>>& grid)
        : presum(m + 1, std::vector<int>(n + 1, 0))
    {
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                presum[i][j] = presum[i][j - 1] + presum[i - 1][j] - presum[i - 1][j - 1] + (grid[i - 1][j - 1] == c);
            }
        }
    }

    int query(int x1, int y1, int x2, int y2) const
    {
        return presum[x2 + 1][y2 + 1] - presum[x2 + 1][y1] - presum[x1][y2 + 1] + presum[x1][y1];
    }

private:
    std::vector<std::vector<int>> presum;
};

class Solution {
public:
    int numberOfSubmatrices(std::vector<std::vector<char>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        Prefix2D prefix2DX('X', m, n, grid);
        Prefix2D prefix2DY('Y', m, n, grid);
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                const int countX = prefix2DX.query(0, 0, i, j);
                const int countY = prefix2DY.query(0, 0, i, j);
                if (countX >= 1 && countX == countY) {
                    result++;
                }
            }
        }
        return result;
    }
};
