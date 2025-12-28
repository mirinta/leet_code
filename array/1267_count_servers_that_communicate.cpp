#include <vector>

/**
 * You are given a map of a server center, represented as a m * n integer matrix grid, where 1 means
 * that on that cell there is a server and 0 means that it is no server. Two servers are said to
 * communicate if they are on the same row or on the same column.
 *
 * Return the number of servers that communicate with any other server.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m <= 250
 * ! 1 <= n <= 250
 * ! grid[i][j] == 0 or 1
 */

class Solution {
public:
    int countServers(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<int> rowCount(m, 0);
        std::vector<int> colCount(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                rowCount[i] += grid[i][j];
                colCount[j] += grid[i][j];
            }
        }
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0)
                    continue;

                result += rowCount[i] > 1 || colCount[j] > 1;
            }
        }
        return result;
    }
};
