#include <vector>

/**
 * You are given a 2D binary array grid. Find a rectangle with horizontal and vertical sides with
 * the smallest area, such that all the 1's in grid lie inside this rectangle.
 *
 * Return the minimum possible area of the rectangle.
 *
 * ! 1 <= grid.length, grid[i].length <= 1000
 * ! grid[i][j] is either 0 or 1.
 * ! The input is generated such that there is at least one 1 in grid.
 */

class Solution {
public:
    int minimumArea(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        int topLeftX = INT_MAX;
        int topLeftY = INT_MAX;
        int bottomRightX = 0;
        int bottomRightY = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    topLeftX = std::min(topLeftX, i);
                    topLeftY = std::min(topLeftY, j);
                    bottomRightX = std::max(bottomRightX, i);
                    bottomRightY = std::max(bottomRightY, j);
                }
            }
        }
        return (bottomRightX - topLeftX + 1) * (bottomRightY - topLeftY + 1);
    }
};