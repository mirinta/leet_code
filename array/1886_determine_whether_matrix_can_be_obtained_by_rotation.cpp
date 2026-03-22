#include <algorithm>
#include <vector>

/**
 * Given two m x n binary matrices mat and target, return true if it is possible to make mat equal to target by rotating
 * mat in 90-degree increments, or false otherwise.
 *
 * ! n == mat.length == target.length
 * ! n == mat[i].length == target[i].length
 * ! 1 <= n <= 10
 * ! mat[i][j] and target[i][j] are either 0 or 1.
 */

class Solution {
public:
    bool findRotation(std::vector<std::vector<int>>& mat, std::vector<std::vector<int>>& target)
    {
        // mat.rotate().reverseByRow() = mat.transpose()
        for (int r = 0; r < 4; ++r) {
            rotate(mat);
            if (mat == target)
                return true;
        }
        return false;
    }

private:
    void rotate(std::vector<std::vector<int>>& mat)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(mat[i][j], mat[j][i]);
            }
        }
        for (auto& row : mat) {
            std::reverse(row.begin(), row.end());
        }
    }
};