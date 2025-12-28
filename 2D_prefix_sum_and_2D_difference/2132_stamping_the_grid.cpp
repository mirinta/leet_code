#include <vector>

/**
 * You are given an m x n binary matrix grid where each cell is either 0 (empty) or 1 (occupied).
 *
 * You are then given stamps of size stampHeight x stampWidth. We want to fit the stamps such that
 * they follow the given restrictions and requirements:
 *
 * 1. Cover all the empty cells.
 *
 * 2. Do not cover any of the occupied cells.
 *
 * 3. We can put as many stamps as we want.
 *
 * 4. Stamps can overlap with each other.
 *
 * 5. Stamps are not allowed to be rotated.
 *
 * 6. Stamps must stay completely inside the grid.
 *
 * Return true if it is possible to fit the stamps while following the given restrictions and
 * requirements. Otherwise, return false.
 *
 * ! m == grid.length
 * ! n == grid[r].length
 * ! 1 <= m, n <= 10^5
 * ! 1 <= m * n <= 2 * 10^5
 * ! grid[r][c] is either 0 or 1.
 * ! 1 <= stampHeight, stampWidth <= 105
 */

class PrefixSum2D {
public:
    explicit PrefixSum2D(const std::vector<std::vector<int>>& mat)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        presum = std::vector<std::vector<int>>(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                presum[i][j] = presum[i][j - 1] + presum[i - 1][j] - presum[i - 1][j - 1] + mat[i - 1][j - 1];
            }
        }
    }

    int query(int x1, int y1, int x2, int y2)
    {
        return presum[x2 + 1][y2 + 1] - presum[x2 + 1][y1] - presum[x1][y2 + 1] + presum[x1][y1];
    }

private:
    std::vector<std::vector<int>> presum;
};

class Diff2D {
public:
    Diff2D(int m, int n) : m(m), n(n), diff(m + 1, std::vector<int>(n + 1, 0)), total(diff) {}

    void add(int x1, int y1, int x2, int y2, int delta)
    {
        diff[x1][y1] += 1;
        diff[x2 + 1][y1] -= 1;
        diff[x1][y2 + 1] -= 1;
        diff[x2 + 1][y2 + 1] += 1;
        processed = false;
    }

    int query(int x, int y)
    {
        process();
        return total[x][y];
    }

private:
    void process()
    {
        if (processed)
            return;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                total[i][j] = diff[i][j];
                if (i > 0) {
                    total[i][j] += total[i - 1][j];
                }
                if (j > 0) {
                    total[i][j] += total[i][j - 1];
                }
                if (i > 0 && j > 0) {
                    total[i][j] -= total[i - 1][j - 1];
                }
            }
        }
        processed = true;
    }

private:
    bool processed{false};
    const int m;
    const int n;
    std::vector<std::vector<int>> diff;
    std::vector<std::vector<int>> total;
};

class Solution {
public:
    bool possibleToStamp(std::vector<std::vector<int>>& grid, int stampHeight, int stampWidth)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        PrefixSum2D presum(grid);
        Diff2D diff(m, n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                const int x = i + stampHeight - 1;
                const int y = j + stampWidth - 1;
                if (x < m && y < n && presum.query(i, j, x, y) == 0) {
                    diff.add(i, j, x, y, 1);
                }
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0 && diff.query(i, j) == 0)
                    return false;
            }
        }
        return true;
    }
};