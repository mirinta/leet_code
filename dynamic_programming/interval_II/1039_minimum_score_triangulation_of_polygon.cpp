#include <climits>
#include <vector>

/**
 * You have a convex n-sided polygon where each vertex has an integer value. You are given an
 * integer array values where values[i] is the value of the ith vertex (i.e., clockwise order).
 *
 * You will triangulate the polygon into n - 2 triangles. For each triangle, the value of that
 * triangle is the product of the values of its vertices, and the total score of the triangulation
 * is the sum of these values over all n - 2 triangles in the triangulation.
 *
 * Return the smallest possible total score that you can achieve with some triangulation of the
 * polygon.
 *
 * ! n == values.length
 * ! 3 <= n <= 50
 * ! 1 <= values[i] <= 100
 */

class Solution
{
public:
    int minScoreTriangulation(std::vector<int>& values)
    {
        const int n = values.size();
        std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1));
        return dfs(memo, 0, values.size() - 1, values);
    }

private:
    // min score of triangulating polygon[i:j]
    int dfs(std::vector<std::vector<int>>& memo, int i, int j, const std::vector<int>& values)
    {
        if (j - i < 2)
            return 0;

        if (memo[i][j] != -1)
            return memo[i][j];

        int result = INT_MAX;
        for (int k = i + 1; k < j; ++k) {
            const int score = values[i] * values[j] * values[k];
            result = std::min(result, dfs(memo, i, k, values) + dfs(memo, k, j, values) + score);
        }
        return memo[i][j] = result;
    }
};
