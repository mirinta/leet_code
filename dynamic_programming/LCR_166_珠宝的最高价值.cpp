#include <vector>

/**
 * 现有一个记作二维矩阵 frame 的珠宝架，其中 frame[i][j] 为该位置珠宝的价值。拿取珠宝的规则为：
 *
 * - 只能从架子的左上角开始拿珠宝
 *
 * - 每次可以移动到右侧或下侧的相邻位置
 *
 * - 到达珠宝架子的右下角时，停止拿取
 *
 * 注意：珠宝的价值都是大于 0 的。除非这个架子上没有任何珠宝，比如 frame = [[0]]
 *
 * ! 0 < frame.length <= 200
 * ! 0 < frame[0].length <= 200
 */

class Solution {
public:
    int jewelleryValue(std::vector<std::vector<int>>& frame)
    {
        return approach2(frame);
    }

private:
    int approach2(const std::vector<std::vector<int>>& frame)
    {
        const int m = frame.size();
        const int n = frame[0].size();
        std::vector<int> dp(n);
        dp[0] = frame[0][0];
        for (int j = 1; j < n; ++j) {
            dp[j] = frame[0][j] + dp[j - 1];
        }
        for (int i = 1; i < m; ++i) {
            dp[0] = frame[i][0] + dp[0];
            for (int j = 1; j < n; ++j) {
                dp[j] = frame[i][j] + std::max(dp[j], dp[j - 1]);
            }
        }
        return dp[n - 1];
    }

    int approach1(const std::vector<std::vector<int>>& frame)
    {
        // dp[i][i] = max value moving from (0,0) to (i,j)
        const int m = frame.size();
        const int n = frame[0].size();
        std::vector<std::vector<int>> dp(m, std::vector<int>(n));
        dp[0][0] = frame[0][0];
        for (int i = 1; i < m; ++i) {
            dp[i][0] = dp[i - 1][0] + frame[i][0];
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = dp[0][j - 1] + frame[0][j];
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = frame[i][j] + std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m - 1][n - 1];
    }
};