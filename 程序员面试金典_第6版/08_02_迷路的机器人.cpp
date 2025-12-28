#include <algorithm>
#include <vector>

/**
 * 设想有个机器人坐在一个网格的左上角，网格 r 行 c
 * 列。机器人只能向下或向右移动，但不能走到一些被禁止的网格（有障碍物）。设计一种算法，寻找机器人从左上角移动到右下角的路径。
 *
 * 网格中的障碍物和空位置分别用 1 和 0 来表示。
 *
 * 返回一条可行的路径，路径由经过的网格的行号和列号组成。左上角为 0 行 0
 * 列。如果没有可行的路径，返回空数组。
 *
 * ! r 和 c 的值均不超过 100。
 */

class Solution {
public:
    std::vector<std::vector<int>> pathWithObstacles(std::vector<std::vector<int>>& obstacleGrid)
    {
        // dp[i][j] = whether the robot can move from (0,0) to (i,j)
        const int m = obstacleGrid.size();
        const int n = obstacleGrid[0].size();
        if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1)
            return {};

        std::vector<std::vector<bool>> dp(m, std::vector<bool>(n, false));
        dp[0][0] = true;
        for (int i = 1; i < m; ++i) {
            dp[i][0] = obstacleGrid[i][0] == 0 && dp[i - 1][0];
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = obstacleGrid[0][j] == 0 && dp[0][j - 1];
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = obstacleGrid[i][j] == 0 && (dp[i - 1][j] || dp[i][j - 1]);
            }
        }
        if (!dp[m - 1][n - 1])
            return {};

        std::vector<std::vector<int>> result;
        int i = m - 1;
        int j = n - 1;
        while (i >= 0 && j >= 0) {
            result.push_back({i, j});
            if (i - 1 >= 0 && dp[i - 1][j]) {
                i--;
            } else {
                j--;
            }
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};