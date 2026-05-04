#include <algorithm>
#include <vector>

/**
 * You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees
 * (clockwise).
 *
 * You have to rotate the image in-place, which means you have to modify the input 2D matrix
 * directly. DO NOT allocate another 2D matrix and do the rotation.
 *
 * ! n == matrix.length == matrix[i].length
 * ! 1 <= n <= 20
 * ! -1000 <= matrix[i][j] <= 1000
 */

class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix)
    {
        // rotate 90 degrees = transpose + reverse by row
        const int n = matrix.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
        for (auto& row : matrix) {
            std::reverse(row.begin(), row.end());
        }
    }
};
