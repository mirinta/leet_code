#include <vector>

/**
 * You are given a 0-indexed m x n integer matrix mat and an integer k. You have to cyclically right
 * shift odd indexed rows k times and cyclically left shift even indexed rows k times.
 *
 * Return true if the initial and final matrix are exactly the same and false otherwise.
 *
 * ! 1 <= mat.length <= 25
 * ! 1 <= mat[i].length <= 25
 * ! 1 <= mat[i][j] <= 25
 * ! 1 <= k <= 50
 */

class Solution {
public:
    bool areSimilar(std::vector<std::vector<int>>& mat, int k)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        k %= n;
        if (k == 0)
            return true;

        for (int i = 0; i < m; ++i) {
            const int shift = i % 2 ? -1 : 1;
            for (int j = 0; j < n; ++j) {
                const int t = (j + k * shift) % n;
                if (mat[i][j] != mat[i][t < 0 ? n + t : t])
                    return false;
            }
        }
        return true;
    }
};