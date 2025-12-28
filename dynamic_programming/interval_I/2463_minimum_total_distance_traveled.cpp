#include <algorithm>
#include <vector>

/**
 * There are some robots and factories on the X-axis. You are given an integer array robot where
 * robot[i] is the position of the ith robot. You are also given a 2D integer array factory where
 * factory[j] = [positionj, limitj] indicates that positionj is the position of the jth factory and
 * that the jth factory can repair at most limitj robots.
 *
 * The positions of each robot are unique. The positions of each factory are also unique. Note that
 * a robot can be in the same position as a factory initially.
 *
 * All the robots are initially broken; they keep moving in one direction. The direction could be
 * the negative or the positive direction of the X-axis. When a robot reaches a factory that did not
 * reach its limit, the factory repairs the robot, and it stops moving.
 *
 * At any moment, you can set the initial direction of moving for some robot. Your target is to
 * minimize the total distance traveled by all the robots.
 *
 * Return the minimum total distance traveled by all the robots. The test cases are generated such
 * that all the robots can be repaired.
 *
 * Note that
 *
 * - All robots move at the same speed.
 *
 * - If two robots move in the same direction, they will never collide.
 *
 * - If two robots move in opposite directions and they meet at some point, they do not collide.
 * They cross each other.
 *
 * - If a robot passes by a factory that reached its limits, it crosses it as if it does not exist.
 *
 * - If the robot moved from a position x to a position y, the distance it moved is |y - x|.
 *
 * ! 1 <= robot.length, factory.length <= 100
 * ! factory[j].length == 2
 * ! -10^9 <= robot[i], positionj <= 10^9
 * ! 0 <= limitj <= robot.length
 * ! The input will be generated such that it is always possible to repair every robot.
 */

class Solution {
public:
    long long minimumTotalDistance(std::vector<int>& robot, std::vector<std::vector<int>>& factory)
    {
        std::sort(robot.begin(), robot.end());
        std::sort(factory.begin(), factory.end(), [](const auto& f1, const auto& f2) { return f1[0] < f2[0]; });
        const int m = robot.size();
        const int n = factory.size();
        // dist[i][j][k] = total dist of robot[i-k:i-1] to factory[j-1]
        std::vector<std::vector<std::vector<long long>>> dist(
            m + 1, std::vector<std::vector<long long>>(n + 1, std::vector<long long>(m + 1, 0)));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                long long sum = 0;
                for (int k = 1; k <= i; ++k) {
                    sum += std::abs(factory[j - 1][0] - robot[i - k]);
                    dist[i][j][k] = sum;
                }
            }
        }
        // dp[i][j] = min total distance of arranging robot[0:i-1] and factory[0:j-1]
        std::vector<std::vector<long long>> dp(m + 1, std::vector<long long>(n + 1, LLONG_MAX / 2));
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = 0;
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int k = 0; k <= std::min(i, factory[j - 1][1]); ++k) {
                    dp[i][j] = std::min(dp[i][j], dp[i - k][j - 1] + dist[i][j][k]);
                }
            }
        }
        return dp[m][n];
    }
};