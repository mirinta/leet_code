#include <vector>

/**
 * Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 1 <= m, n <= 10^4
 * ! 1 <= m * n <= 10^4
 * ! -10^5 <= mat[i][j] <= 10^5
 */

class Solution {
public:
    std::vector<int> findDiagonalOrder(std::vector<std::vector<int>>& mat)
    {
        // start from mat[i][j]
        // - go upper right: mat[i-1][j+1], ...
        // - go bottom left: mat[i+1][j-1], ...
        const int m = mat.size();
        const int n = mat[0].size();
        const int total = m * n;
        int direction = 1; // 1 for upper right, -1 for bottom left
        int x = 0;
        int y = 0;
        std::vector<int> result;
        result.reserve(total);
        while (result.size() < total) {
            while (x >= 0 && x < m && y >= 0 && y < n) {
                result.push_back(mat[x][y]);
                x -= direction;
                y += direction;
            }
            if (direction > 0) {
                x = y < n ? 0 : x + 2;
                y = y < n ? y : n - 1;
            } else {
                y = x < m ? 0 : y + 2;
                x = x < m ? x : m - 1;
            }
            direction *= -1;
        }
        return result;
    }
};
