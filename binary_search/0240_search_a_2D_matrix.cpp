#include <vector>

/**
 * Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix.
 *
 * This matrix has the following properties:
 *
 * - Integers in each row are sorted in ascending from left to right.
 *
 * - Integers in each column are sorted in ascending from top to bottom.
 *
 * ! m == matrix.length
 * ! n == matrix[i].length
 * ! 1 <= n, m <= 300
 * ! -10^9 <= matrix[i][j] <= 10^9
 * ! All the integers in each row are sorted in ascending order.
 * ! All the integers in each column are sorted in ascending order.
 * ! -10^9 <= target <= 10^9
 */

class Solution {
public:
    bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target)
    {
        return approach2(matrix, target);
    }

private:
    // use top-right value as pivot
    bool approach1(const std::vector<std::vector<int>>& matrix, int target)
    {
        if (matrix.empty() || matrix[0].empty())
            return false;

        // m x n matrix
        const auto m = matrix.size();
        const auto n = matrix[0].size();
        // top-left is the min value, and bottom-right is the max value
        if (target < matrix[0][0] || target > matrix[m - 1][n - 1])
            return false;

        // use top-right as a pivot
        // - pivot is the min value of that column
        // - pivot is the max value of that row
        int pivotRow = 0;
        int pivotCol = n - 1;
        while (pivotRow < m && pivotCol >= 0) {
            const auto& pivot = matrix[pivotRow][pivotCol];
            if (pivot == target)
                return true;

            if (pivot > target) {
                pivotCol--;
            } else {
                pivotRow++;
            }
        }
        return false;
    }

    // use bottom-left value as pivot
    bool approach2(const std::vector<std::vector<int>>& matrix, int target)
    {
        if (matrix.empty() || matrix[0].empty())
            return false;

        // m x n matrix
        const auto m = matrix.size();
        const auto n = matrix[0].size();
        // top-left is the min value, and bottom-right is the max value
        if (target < matrix[0][0] || target > matrix[m - 1][n - 1])
            return false;

        // use bottom-left as a pivot
        // - pivot is the min value of that row
        // - pivot is the max value of that column
        int pivotRow = m - 1;
        int pivotCol = 0;
        while (pivotRow >= 0 && pivotCol < n) {
            const auto& pivot = matrix[pivotRow][pivotCol];
            if (pivot == target)
                return true;

            if (pivot > target) {
                pivotRow--;
            } else {
                pivotCol++;
            }
        }
        return false;
    }
};
