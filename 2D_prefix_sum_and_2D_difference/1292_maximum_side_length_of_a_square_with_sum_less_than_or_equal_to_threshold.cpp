#include <vector>

/**
 * Given a m x n matrix mat and an integer threshold, return the maximum side-length of a square
 * with a sum less than or equal to threshold or return 0 if there is no such square.
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 1 <= m, n <= 300
 * ! 0 <= mat[i][j] <= 10^4
 * ! 0 <= threshold <= 10^5
 */

class Presum2D {
public:
    explicit Presum2D(const std::vector<std::vector<int>>& mat)
        : presum(mat.size() + 1, std::vector<int>(mat[0].size() + 1, 0))
    {
        for (int i = 1; i <= mat.size(); ++i) {
            for (int j = 1; j <= mat[0].size(); ++j) {
                presum[i][j] = mat[i - 1][j - 1] + presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1];
            }
        }
    }

    int query(int x1, int y1, int x2, int y2) const
    {
        return presum[x2 + 1][y2 + 1] - presum[x2 + 1][y1] - presum[x1][y2 + 1] + presum[x1][y1];
    }

private:
    std::vector<std::vector<int>> presum;
};

class Solution {
public:
    int maxSideLength(std::vector<std::vector<int>>& mat, int threshold)
    {
        Presum2D presum(mat);
        const int m = mat.size();
        const int n = mat[0].size();
        int lo = 0;
        int hi = std::min(m, n);
        while (lo < hi) {
            const int mid = hi - (hi - lo) / 2;
            if (isValid(m, n, mid, threshold, presum)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return hi;
    }

private:
    bool isValid(int m, int n, int length, int threshold, const Presum2D& presum)
    {
        for (int i = 0; i + length <= m; ++i) {
            for (int j = 0; j + length <= n; ++j) {
                if (presum.query(i, j, i + length - 1, j + length - 1) <= threshold)
                    return true;
            }
        }
        return false;
    }
};
