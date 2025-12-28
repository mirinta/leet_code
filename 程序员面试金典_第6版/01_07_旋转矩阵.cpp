#include <vector>

/**
 * 给你一幅由 N × N 矩阵表示的图像，其中每个像素的大小为 4 字节。请你设计一种算法，将图像旋转 90
 * 度。
 *
 * 不占用额外内存空间能否做到？
 *
 * ! 本题与LC.48相同。
 */

class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix)
    {
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