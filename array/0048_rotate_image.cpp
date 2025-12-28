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
        // 1 2 3           7 4 1                 1 4 7
        // 4 5 6 -ROTATE-> 8 5 2 -REVERSE ROWS-> 2 5 8
        // 7 8 9           9 6 3                 3 6 9
        //   |                                     |
        //   |---------------TRANSPOSE------------>|
        const int m = matrix.size();
        // transpose
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < i; ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
        // reverse each row
        for (auto& row : matrix) {
            std::reverse(row.begin(), row.end());
        }
    }
};
