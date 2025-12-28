#include <vector>

/**
 * 输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。
 *
 * ! 0 <= matrix.length <= 100
 * ! 0 <= matrix[i].length <= 100
 *
 * ! 本题与LC 54相同。
 */

class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix)
    {
        if (matrix.empty() || matrix[0].empty())
            return {};

        const int m = matrix.size();
        const int n = matrix[0].size();
        int left = 0;
        int right = n - 1;
        int top = 0;
        int bottom = m - 1;
        std::vector<int> result;
        result.reserve(m * n);
        while (left <= right && top <= bottom) {
            // from left to right:
            for (int i = left; i <= right && top <= bottom; ++i) {
                result.push_back(matrix[top][i]);
            }
            top++;
            // from top to bottom:
            for (int i = top; i <= bottom && left <= right; ++i) {
                result.push_back(matrix[i][right]);
            }
            right--;
            // from right to left:
            for (int i = right; i >= left && top <= bottom; --i) {
                result.push_back(matrix[bottom][i]);
            }
            bottom--;
            // from bottom to top:
            for (int i = bottom; i >= top && left <= right; --i) {
                result.push_back(matrix[i][left]);
            }
            left++;
        }
        return result;
    }
};