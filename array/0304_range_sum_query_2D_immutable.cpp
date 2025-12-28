#include <vector>

/**
 * Given a 2D matrix "matrix", handle multiple queries of the following type:
 *
 * - Calculate the sum of the elements of "matrix" inside the rectangle defined by its upper left
 * corner "(row1, col1)" and lower right corner "(row2, col2)".
 *
 * Implement the "NumMatrix" class:
 *
 * - "NumMatrix(int[][] matrix)" initializes the object with the integer matrix "matrix".
 *
 * - "int sumRegion(int row1, int col1, int row2, int col2)" returns the sum of the elements of
 * "matrix" inside the rectangle defined by its upper left corner "(row1, col1)" and lower right
 * corner "(row2, col2)".
 *
 * ! You must design an algorithm where "sumRegion" works on O(1) time complexity.
 */

class NumMatrix {
    // suppose the origin is a 3x3 matrix:
    // x00      x01     x02
    // x10      x11     x12
    // x20      x21     x22
    // then our _preSums is a 4x4 matrix:
    // 0        0               0                           0
    // 0        x00             x00+x01                     x00+x01+x02
    // 0        x00+x10         x00+x01+x10+x11             x00+x01+x02+x10+x11+x12
    // 0        x00+x10+x20     x00+x01+x10+x11+x20+x21     x00+x01+x02+x10+x11+x12+x20+x21+x22
    using Matrix = std::vector<std::vector<int>>;
    const Matrix _preSums;

    static Matrix createPreSums(const Matrix& matrix)
    {
        Matrix result(matrix.size() + 1, std::vector<int>(matrix[0].size() + 1, 0));
        for (size_t row = 0; row < matrix.size(); ++row) {
            for (size_t col = 0; col < matrix[row].size(); ++col) {
                result[row + 1][col + 1] =
                    result[row][col + 1] + result[row + 1][col] + matrix[row][col] - result[row][col];
            }
        }
        return result;
    }

public:
    NumMatrix(Matrix& matrix) : _preSums(createPreSums(matrix)) {}

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        return _preSums[row1][col1] + _preSums[row2 + 1][col2 + 1] - _preSums[row1][col2 + 1] -
               _preSums[row2 + 1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */