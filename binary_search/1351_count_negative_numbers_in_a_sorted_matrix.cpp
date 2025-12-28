#include <algorithm>
#include <vector>

/**
 * Given a m x n matrix "grid" which is sorted in non-increasing order both row-wise and
 * column-wise, return the number of negative numbers in "grid".
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 100
 * ! -100 <= grid[i][j] <= 100
 */

class Solution {
public:
    int countNegatives(std::vector<std::vector<int>>& grid)
    {
        // always check the top-right element grid[i][j]
        // if grid[i][j] >= 0, then the ith row can be skipped
        // otherwise, the grid[i:m-1][j] are all negative numbers
        const int m = grid.size();
        const int n = grid[0].size();
        int i = 0;
        int j = n - 1;
        int result = 0;
        while (i < m && j >= 0) {
            if (grid[i][j] >= 0) {
                i++;
            } else {
                result += m - i;
                j--;
            }
        }
        return result;
    }
};
