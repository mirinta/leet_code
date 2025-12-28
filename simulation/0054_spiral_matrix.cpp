#include <vector>

/**
 * Given an "mxn" "matrix", return all elements of the matrix in spiral order.
 *
 * ! m == matrix.length
 * ! n == matrix[i].length
 * ! 1 <= m, n <= 10
 * ! -100 <= matrix[i][j] <= 100
 */

class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix)
    {
        //      -----top---->
        //   ^  + + + + + + +  |
        //   |  +           +  |
        // left +           + right
        //   |  +           +  |
        //   |  + + + + + + +  v
        //      <---bottom---
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::vector<int> result;
        result.reserve(m * n);
        int top = 0;
        int bottom = m - 1;
        int left = 0;
        int right = n - 1;
        while (result.size() < m * n) {
            for (int i = left; i <= right && top <= bottom; ++i) {
                result.push_back(matrix[top][i]);
            }
            top++;
            for (int i = top; i <= bottom && left <= right; ++i) {
                result.push_back(matrix[i][right]);
            }
            right--;
            for (int i = right; i >= left && top <= bottom; --i) {
                result.push_back(matrix[bottom][i]);
            }
            bottom--;
            for (int i = bottom; i >= top && left <= right; --i) {
                result.push_back(matrix[i][left]);
            }
            left++;
        }
        return result;
    }
};