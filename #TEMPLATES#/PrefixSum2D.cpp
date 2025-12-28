#include <vector>

class PrefixSum2D {
public:
    explicit PrefixSum2D(const std::vector<std::vector<int>>& mat)
        : presum(mat.size() + 1, std::vector<int>(mat[0].size() + 1, 0))
    {
        for (int i = 1; i <= mat.size(); ++i) {
            for (int j = 1; j <= mat[0].size(); ++j) {
                presum[i][j] = presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1] + mat[i - 1][j - 1];
            }
        }
    }

    /**
     * @brief Return the sum of the elements in the submatrix mat[x1:x2][y1:y2].
     *
     * @note x1, y1, x2 and y2 are 0-indexed.
     */
    int query(int x1, int y1, int x2, int y2) const
    {
        return presum[x2 + 1][y2 + 1] - presum[x2 + 1][y1] - presum[x1][y2 + 1] + presum[x1][y1];
    }

private:
    std::vector<std::vector<int>> presum; // presum[i][j] = sum of elements in mat[0:i-1][0:j-1]
};