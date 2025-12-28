#include <vector>

/**
 * Given an m x n binary matrix mat, return the number of special positions in mat.
 *
 * A position (i, j) is called special if mat[i][j] == 1 and all other elements in row i and column
 * j are 0 (rows and columns are 0-indexed).
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 1 <= m, n <= 100
 * ! mat[i][j] is either 0 or 1.
 */

class Solution {
public:
    int numSpecial(std::vector<std::vector<int>>& mat)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        std::vector<int> rowSum(m, 0);
        std::vector<int> colSum(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                rowSum[i] += mat[i][j];
                colSum[j] += mat[i][j];
            }
        }
        int result = 0;
        for (int i = 0; i < m; ++i) {
            if (rowSum[i] != 1)
                continue;

            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 1 && colSum[j] == 1) {
                    result++;
                }
            }
        }
        return result;
    }
};