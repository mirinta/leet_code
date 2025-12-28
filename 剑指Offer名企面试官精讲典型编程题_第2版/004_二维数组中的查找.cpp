#include <vector>

/**
 * 在一个 n * m
 * 的二维数组中，每一行都按照从左到右非递减的顺序排序，每一列都按照从上到下非递减的顺序排序。
 * 请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
 *
 * ! 本题与LC 240相同。
 */

class Solution {
public:
    bool findNumberIn2DArray(const std::vector<std::vector<int>>& matrix, int target)
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
            else if (pivot > target) {
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
