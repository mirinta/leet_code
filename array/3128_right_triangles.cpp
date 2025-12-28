#include <vector>

/**
 * You are given a 2D boolean matrix grid.
 *
 * Return an integer that is the number of right triangles that can be made with the 3 elements of
 * grid such that all of them have a value of 1.
 *
 * Note:
 *
 * A collection of 3 elements of grid is a right triangle if one of its elements is in the same row
 * with another element and in the same column with the third element. The 3 elements do not have to
 * be next to each other.
 *
 * ! 1 <= grid.length <= 1000
 * ! 1 <= grid[i].length <= 1000
 * ! 0 <= grid[i][j] <= 1
 */

class Solution {
public:
    long long numberOfRightTriangles(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<int> row(m, 0);
        std::vector<int> col(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                row[i] += grid[i][j];
                col[j] += grid[i][j];
            }
        }
        long long result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0)
                    continue;

                // choose grid[i][j] as the turning point
                result += (col[j] - 1) * (row[i] - 1);
            }
        }
        return result;
    }
};