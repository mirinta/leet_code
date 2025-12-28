#include <string>
#include <vector>

/**
 * Given a rectangular pizza represented as a rows x cols matrix containing the following
 * characters: 'A' (an apple) and '.' (empty cell) and given the integer k. You have to cut the
 * pizza into k pieces using k-1 cuts.
 *
 * For each cut you choose the direction: vertical or horizontal, then you choose a cut position at
 * the cell boundary and cut the pizza into two pieces. If you cut the pizza vertically, give the
 * left part of the pizza to a person. If you cut the pizza horizontally, give the upper part of the
 * pizza to a person. Give the last piece of pizza to the last person.
 *
 * Return the number of ways of cutting the pizza such that each piece contains at least one apple.
 * Since the answer can be a huge number, return this modulo 10^9 + 7.
 *
 * ! 1 <= rows, cols <= 50
 * ! rows == pizza.length
 * ! cols == pizza[i].length
 * ! 1 <= k <= 10
 * ! pizza consists of characters 'A' and '.' only.
 */

class PrefixSum2D {
public:
    PrefixSum2D(int m, int n, const std::vector<std::string>& mat) : presum(m + 1, std::vector<int>(n + 1, 0))
    {
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                const int val = mat[i - 1][j - 1] == 'A';
                presum[i][j] = val + presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1];
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
    int ways(std::vector<std::string>& pizza, int k)
    {
        const int m = pizza.size();
        const int n = pizza[0].size();
        const PrefixSum2D presum2D(m, n, pizza);
        Memo memo(m, std::vector<std::vector<int>>(n, std::vector<int>(k + 1, -1)));
        return dfs(memo, 0, 0, k, m, n, presum2D);
    }

private:
    using Memo = std::vector<std::vector<std::vector<int>>>;
    static constexpr int kMod = 1e9 + 7;

    // num of ways to cut pizza[i:m-1][j:n-1] into k pieces
    // such that each piece contains at least one apple
    int dfs(Memo& memo, int i, int j, int k, int m, int n, const PrefixSum2D& presum2D)
    {
        if (presum2D.query(i, j, m - 1, n - 1) < k)
            return 0;

        if (k == 1)
            return 1;

        if (memo[i][j][k] != -1)
            return memo[i][j][k];

        int result = 0;
        for (int x = i + 1; x < m; ++x) {
            if (presum2D.query(i, j, x - 1, n - 1) > 0) {
                result = (result + dfs(memo, x, j, k - 1, m, n, presum2D)) % kMod;
            }
        }
        for (int y = j + 1; y < n; ++y) {
            if (presum2D.query(i, j, m - 1, y - 1) > 0) {
                result = (result + dfs(memo, i, y, k - 1, m, n, presum2D)) % kMod;
            }
        }
        return memo[i][j][k] = result;
    }
};