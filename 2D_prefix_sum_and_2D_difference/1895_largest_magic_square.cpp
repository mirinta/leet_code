#include <vector>

/**
 * A k x k magic square is a k x k grid filled with integers such that every row sum, every column sum, and both
 * diagonal sums are all equal. The integers in the magic square do not have to be distinct. Every 1 x 1 grid is
 * trivially a magic square.
 *
 * Given an m x n integer grid, return the size (i.e., the side length k) of the largest magic square that can be found
 * within this grid.
 *
 * ! m == grid.length
 * !n == grid[i].length
 * !1 <= m, n <= 50
 * !1 <= grid[i][j] <= 10^6
 */

class Presum2D {
public:
    explicit Presum2D(const std::vector<std::vector<int>>& mat)
        : presum(mat.size() + 1, std::vector<int>(mat[0].size() + 1, 0))
    {
        for (int i = 1; i <= mat.size(); ++i) {
            for (int j = 1; j <= mat[0].size(); ++j) {
                presum[i][j] = presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1] + mat[i - 1][j - 1];
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
    int largestMagicSquare(std::vector<std::vector<int>>& grid)
    {
        Presum2D presum(grid);
        const int m = grid.size();
        const int n = grid[0].size();
        for (int k = std::min(m, n); k > 1; --k) {
            for (int i = 0; i + k <= m; ++i) {
                for (int j = 0; j + k <= n; ++j) {
                    if (isValid(i, j, k, grid, presum))
                        return k;
                }
            }
        }
        return 1;
    }

private:
    bool isValid(int x, int y, int k, const std::vector<std::vector<int>>& grid, const Presum2D& presum)
    {
        const int total = presum.query(x, y, x + k - 1, y + k - 1);
        if (total % k)
            return false;

        const int target = total / k;
        int diagonal = 0;
        int antiDiagonal = 0;
        for (int i = 0; i < k; ++i) {
            if (presum.query(x + i, y, x + i, y + k - 1) != target)
                return false;

            if (presum.query(x, y + i, x + k - 1, y + i) != target)
                return false;

            diagonal += grid[x + i][y + i];
            antiDiagonal += grid[x + i][y + k - i - 1];
        }
        return diagonal == target && antiDiagonal == target;
    }
};