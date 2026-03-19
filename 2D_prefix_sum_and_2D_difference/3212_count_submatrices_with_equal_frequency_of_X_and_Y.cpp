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

class Solution {
public:
    int numberOfSubmatrices(std::vector<std::vector<char>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<std::pair<int, int>>> presum(m + 1, std::vector<std::pair<int, int>>(n + 1, {0, 0}));
        int result = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                presum[i][j].first = presum[i - 1][j].first + presum[i][j - 1].first + (grid[i - 1][j - 1] == 'X') -
                                     presum[i - 1][j - 1].first;
                presum[i][j].second = presum[i - 1][j].second + presum[i][j - 1].second + (grid[i - 1][j - 1] == 'Y') -
                                      presum[i - 1][j - 1].second;
                result += presum[i][j].first > 0 && presum[i][j].first == presum[i][j].second;
            }
        }
        return result;
    }
};
