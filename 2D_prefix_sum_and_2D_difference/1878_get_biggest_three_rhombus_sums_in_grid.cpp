#include <set>
#include <vector>

/**
 * You are given an m x n integer matrix grid​​​.
 *
 * A rhombus sum is the sum of the elements that form the border of a regular rhombus shape in grid​​​. The
 * rhombus must have the shape of a square rotated 45 degrees with each of the corners centered in a grid cell. Below is
 * an image of four valid rhombus shapes with the corresponding colored cells that should be included in each rhombus
 * sum:
 *
 * Note that the rhombus can have an area of 0, which is depicted by the purple rhombus in the bottom right corner.
 *
 * Return the biggest three distinct rhombus sums in the grid in descending order. If there are less than three distinct
 * values, return all of them.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 50
 * ! 1 <= grid[i][j] <= 10^5
 */

class Solution {
public:
    std::vector<int> getBiggestThree(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        // diagonal, top-left to bottom-right
        std::vector<std::vector<int>> presum1(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                presum1[i][j] = presum1[i - 1][j - 1] + grid[i - 1][j - 1];
            }
        }
        auto query1 = [&presum1](int x1, int y1, int x2, int y2) { return presum1[x2 + 1][y2 + 1] - presum1[x1][y1]; };
        // anti-diagonal, top-right to bottom-left
        std::vector<std::vector<int>> presum2(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j < n; ++j) {
                presum2[i][j] = presum2[i - 1][j + 1] + grid[i - 1][j];
            }
        }
        auto query2 = [&presum2](int x1, int y1, int x2, int y2) { return presum2[x2 + 1][y2] - presum2[x1][y1 + 1]; };
        std::set<int> set;
        auto update = [&set](int val) {
            set.insert(val);
            if (set.size() > 3) {
                set.erase(set.begin());
            }
        };
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                update(grid[i][j]);
                for (int len = 1; len <= std::min({j, n - j - 1, i, m - i - 1}); ++len) {
                    const int topX = i - len;
                    const int topY = j;
                    const int leftX = i;
                    const int leftY = j - len;
                    const int rightX = i;
                    const int rightY = j + len;
                    const int bottomX = i + len;
                    const int bottomY = j;
                    int sum = 0;
                    sum += query1(topX, topY, rightX, rightY) + query1(leftX, leftY, bottomX, bottomY);
                    sum += query2(topX, topY, leftX, leftY) + query2(rightX, rightY, bottomX, bottomY);
                    sum -= grid[topX][topY] + grid[leftX][leftY] + grid[rightX][rightY] + grid[bottomX][bottomY];
                    update(sum);
                }
            }
        }
        return {set.rbegin(), set.rend()};
    }
};
