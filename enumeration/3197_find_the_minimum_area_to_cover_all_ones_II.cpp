#include <vector>

/**
 * You are given a 2D binary array grid. You need to find 3 non-overlapping rectangles having
 * non-zero areas with horizontal and vertical sides such that all the 1's in grid lie inside these
 * rectangles.
 *
 * Return the minimum possible sum of the area of these rectangles.
 *
 * Note that the rectangles are allowed to touch.
 *
 * ! 1 <= grid.length, grid[i].length <= 30
 * ! grid[i][j] is either 0 or 1.
 * ! The input is generated such that there are at least three 1's in grid.
 */

class Solution {
public:
    int minimumSum(std::vector<std::vector<int>>& grid)
    {
        /*
         *    case 1       case 2       case 3
         *    +---------+  +---------+  +---+-----+
         *    |         |  |         |  |   |     |
         *    +---------+  +---+-----+  |   |     |
         *    |         |  |   |     |  |   |     |
         *    +---------+  |   |     |  +---+-----+
         *    |         |  |   |     |  |         |
         *    +---------+  +---+-----+  +---------+
         *
         *    case 4       case 5       case 6
         *    +--+---+--+  +-----+---+  +---+-----+
         *    |  |   |  |  |     |   |  |   |     |
         *    |  |   |  |  |     |   |  |   |     |
         *    |  |   |  |  +-----+   |  |   +-----+
         *    |  |   |  |  |     |   |  |   |     |
         *    |  |   |  |  |     |   |  |   |     |
         *    +--+---+--+  +-----+---+  +---+-----+
         */
        const int m = grid.size();
        const int n = grid[0].size();
        int result = INT_MAX;
        // case 1
        for (int i = 0; i + 1 < m; ++i) {
            for (int j = i + 1; j + 1 < m; ++j) {
                const int area1 = solve(0, 0, i, n - 1, grid);
                const int area2 = solve(i + 1, 0, j, n - 1, grid);
                const int area3 = solve(j + 1, 0, m - 1, n - 1, grid);
                result = std::min(result, area1 + area2 + area3);
            }
        }
        // case 2
        for (int i = 0; i + 1 < m; ++i) {
            for (int j = 0; j + 1 < n; ++j) {
                const int area1 = solve(0, 0, i, n - 1, grid);
                const int area2 = solve(i + 1, 0, m - 1, j, grid);
                const int area3 = solve(i + 1, j + 1, m - 1, n - 1, grid);
                result = std::min(result, area1 + area2 + area3);
            }
        }
        // case 3
        for (int i = 0; i + 1 < m; ++i) {
            for (int j = 0; j + 1 < n; ++j) {
                const int area1 = solve(0, 0, i, j, grid);
                const int area2 = solve(0, j + 1, i, n - 1, grid);
                const int area3 = solve(i + 1, 0, m - 1, n - 1, grid);
                result = std::min(result, area1 + area2 + area3);
            }
        }
        // case 4
        for (int i = 0; i + 1 < n; ++i) {
            for (int j = i + 1; j + 1 < n; ++j) {
                const int area1 = solve(0, 0, m - 1, i, grid);
                const int area2 = solve(0, i + 1, m - 1, j, grid);
                const int area3 = solve(0, j + 1, m - 1, n - 1, grid);
                result = std::min(result, area1 + area2 + area3);
            }
        }
        // case 5
        for (int i = 0; i + 1 < m; ++i) {
            for (int j = 0; j + 1 < n; ++j) {
                const int area1 = solve(0, 0, i, j, grid);
                const int area2 = solve(i + 1, 0, m - 1, j, grid);
                const int area3 = solve(0, j + 1, m - 1, n - 1, grid);
                result = std::min(result, area1 + area2 + area3);
            }
        }
        // case 6
        for (int i = 0; i + 1 < m; ++i) {
            for (int j = 0; j + 1 < n; ++j) {
                const int area1 = solve(0, 0, m - 1, j, grid);
                const int area2 = solve(0, j + 1, i, n - 1, grid);
                const int area3 = solve(i + 1, j + 1, m - 1, n - 1, grid);
                result = std::min(result, area1 + area2 + area3);
            }
        }
        return result;
    }

private:
    // given a submatrix of grid, find the area of the min rectangle that contains all the 1's in
    // that submatrix similar to LC.3195
    int solve(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, const std::vector<std::vector<int>>& grid)
    {
        int minX = INT_MAX;
        int maxX = 0;
        int minY = INT_MAX;
        int maxY = 0;
        int count = 0;
        for (int i = topLeftX; i <= bottomRightX; ++i) {
            for (int j = topLeftY; j <= bottomRightY; ++j) {
                if (grid[i][j] == 1) {
                    minX = std::min(minX, i);
                    maxX = std::max(maxX, i);
                    minY = std::min(minY, j);
                    maxY = std::max(maxY, j);
                    count++;
                }
            }
        }
        if (count == 0)
            return 1;

        return (maxX - minX + 1) * (maxY - minY + 1);
    }
};