#include <algorithm>
#include <vector>

/**
 * Given an m x n binary grid grid where each 1 marks the home of one friend, return the minimal
 * total travel distance.
 *
 * The total travel distance is the sum of the distances between the houses of the friends and the
 * meeting point.
 *
 * The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| +
 * |p2.y - p1.y|.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 200
 * ! grid[i][j] is either 0 or 1.
 * ! There will be at least two friends in the grid.
 */

class Solution {
public:
    int minTotalDistance(std::vector<std::vector<int>>& grid)
    {
        // given a sequence {x1, x2, ..., xn}
        // we need to find xk to minimize |x1-xk| + |x2-xk| + ... + |xn-xk|
        // xk >= x1, ..., xk-1 and xk <= xk+1, ..., xn
        // xk is the median of the given sequence
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<int> rows;
        std::vector<int> cols;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    rows.push_back(i);
                    cols.push_back(j);
                }
            }
        }
        std::sort(cols.begin(), cols.end());
        const int originX = rows[rows.size() / 2];
        const int originY = cols[cols.size() / 2];
        int result = 0;
        for (int i = 0; i < rows.size(); ++i) {
            result += manhattan(rows[i], cols[i], originX, originY);
        }
        return result;
    }

private:
    int manhattan(int x1, int y1, int x2, int y2)
    {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }
};