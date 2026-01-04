#include <unordered_map>

/**
 * You have a grid of size n x 3 and you want to paint each cell of the grid with exactly one of the three colors: Red,
 * Yellow, or Green while making sure that no two adjacent cells have the same color (i.e., no two cells that share
 * vertical or horizontal sides have the same color).
 *
 * Given n the number of rows of the grid, return the number of ways you can paint this grid. As the answer may grow
 * large, the answer must be computed modulo 10^9 + 7.
 *
 * ! n == grid.length
 * ! 1 <= n <= 5000
 */

class Solution {
public:
    int numOfWays(int n)
    {
        std::unordered_map<int, int> memo;
        return dfs(memo, 0, 0, 0, 0, n);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    // NONE = (00), RED = (01), YELLOW = (10), GREEN = (11)
    int dfs(std::unordered_map<int, int>& memo, int i, int j, int prev, int curr, int n)
    {
        if (i == n)
            return 1;

        if (j == 3)
            return dfs(memo, i + 1, 0, curr, 0, n);

        const int key = curr | (prev << 6) | (j << 12) | (i << 14);
        if (memo.count(key))
            return memo[key];

        const int left = getColor(curr, j - 1);
        const int top = getColor(prev, j);
        int result = 0;
        for (int c = 1; c <= 3; ++c) {
            if (c == left || c == top)
                continue;

            result = (result + dfs(memo, i, j + 1, prev, addColor(curr, j, c), n)) % kMod;
        }
        return memo[key] = result;
    };

    int getColor(int mask, int col)
    {
        if (col < 0 || mask == 0)
            return 0;

        return (mask >> (2 * col)) & 3;
    }

    int addColor(int mask, int col, int color)
    {
        return mask | (color << (2 * col));
    }
};