#include <vector>

/**
 * You are given an m x n integer matrix grid​​​, where m and n are both even integers, and an integer k.
 *
 * The matrix is composed of several layers, which is shown in the below image, where each color is its own layer:
 *
 * A cyclic rotation of the matrix is done by cyclically rotating each layer in the matrix. To cyclically rotate a layer
 * once, each element in the layer will take the place of the adjacent element in the counter-clockwise direction. An
 * example rotation is shown below:
 *
 * Return the matrix after applying k cyclic rotations to it.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 2 <= m, n <= 50
 * ! Both m and n are even integers.
 * ! 1 <= grid[i][j] <= 5000
 * ! 1 <= k <= 10^9
 */

class Solution {
public:
    std::vector<std::vector<int>> rotateGrid(std::vector<std::vector<int>>& grid, int k)
    {
        // k = 1
        // 40 30 20 [10] -> 10 40 30 20
        //
        // k = 2
        // 06 10 [11] 07 -> 11 07 06 10
        const int m = grid.size();
        const int n = grid[0].size();
        int top = 0;
        int bottom = m - 1;
        int left = 0;
        int right = n - 1;
        std::vector<std::vector<int>> result(m, std::vector<int>(n));
        for (int layer = 0; layer < std::min(m / 2, n / 2); ++layer) {
            std::vector<std::pair<int, int>> coords;
            std::vector<int> values;
            // go down
            for (int i = top; i <= bottom; ++i) {
                coords.emplace_back(i, left);
                values.emplace_back(grid[i][left]);
            }
            left++;
            // go right
            for (int i = left; i <= right; ++i) {
                coords.emplace_back(bottom, i);
                values.emplace_back(grid[bottom][i]);
            }
            bottom--;
            // go up
            for (int i = bottom; i >= top; --i) {
                coords.emplace_back(i, right);
                values.emplace_back(grid[i][right]);
            }
            right--;
            // go left
            for (int i = right; i >= left; --i) {
                coords.emplace_back(top, i);
                values.emplace_back(grid[top][i]);
            }
            top++;
            // rearrange
            const int count = coords.size();
            for (int i = 0, j = count - k % count; i < count; ++i) {
                const auto& [x, y] = coords[i];
                result[x][y] = values[(j + i) % count];
            }
        }
        return result;
    }
};