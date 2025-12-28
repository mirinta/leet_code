#include <vector>

/**
 * You are given a 0-indexed m x n binary matrix grid.
 *
 * A 0-indexed m x n difference matrix diff is created with the following procedure:
 *
 * - Let the number of ones in the ith row be onesRowi.
 *
 * - Let the number of ones in the jth column be onesColj.
 *
 * - Let the number of zeros in the ith row be zerosRowi.
 *
 * - Let the number of zeros in the jth column be zerosColj.
 *
 * - diff[i][j] = onesRowi + onesColj - zerosRowi - zerosColj
 *
 * Return the difference matrix diff.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 10^5
 * ! 1 <= m * n <= 10^5
 * ! grid[i][j] is either 0 or 1.
 */

class Solution {
public:
    std::vector<std::vector<int>> onesMinusZeros(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<int> row(m); // #ones - #zeros
        std::vector<int> col(n); // #ones - #zeros
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    row[i]++;
                    col[j]++;
                } else if (grid[i][j] == 0) {
                    row[i]--;
                    col[j]--;
                }
            }
        }
        std::vector<std::vector<int>> result(m, std::vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result[i][j] = row[i] + col[j];
            }
        }
        return result;
    }
};