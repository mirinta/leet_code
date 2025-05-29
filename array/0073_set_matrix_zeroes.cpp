#include <unordered_set>
#include <vector>

/**
 * Given an m x n integer matrix, if an element is 0, ste its entire row and column to 0's.
 * 
 * You must do it in place.
 *
 * ! m == matrix.length
 * ! n == matrix[0].length
 * ! 1 <= m, n <= 200
 * ! -2^31 <= matrix[i][j] <= 2^31 - 1
 */

class Solution
{
public:
    void setZeroes(std::vector<std::vector<int>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        bool firstRowHasZero = false;
        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == 0) {
                firstRowHasZero = true;
                break;
            }
        }
        bool firstColHasZero = false;
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) {
                firstColHasZero = true;
                break;
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        for (int j = 0; j < n && firstRowHasZero; ++j) {
            matrix[0][j] = 0;
        }
        for (int i = 0; i < m && firstColHasZero; ++i) {
            matrix[i][0] = 0;
        }
    }
};
