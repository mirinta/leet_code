#include <functional>
#include <vector>

/**
 * You are given two jugs with capacities x liters and y liters. You have an infinite water supply.
 * Return whether the total amount of water in both jugs may reach target using the following
 * operations:
 *
 * - Fill either jug completely with water.
 *
 * - Completely empty either jug.
 *
 * - Pour water from one jug into another until the receiving jug is full, or the transferring jug
 * is empty.
 *
 * ! 1 <= x, y, target <= 10^3
 */

class Solution {
public:
    bool canMeasureWater(int x, int y, int target)
    {
        if (x + y < target)
            return false;

        std::vector<std::vector<bool>> visited(x + 1, std::vector<bool>(y + 1, false));
        std::function<bool(int, int)> dfs = [&](int jug1, int jug2) {
            if (jug1 + jug2 == target)
                return true;

            if (visited[jug1][jug2])
                return false;

            visited[jug1][jug2] = true;
            if (dfs(x, jug2) || dfs(jug1, y) || dfs(0, jug2) || dfs(jug1, 0))
                return true;

            const int from1to2 = std::min(jug1, y - jug2);
            const int from2to1 = std::min(jug2, x - jug1);
            return dfs(jug1 - from1to2, jug2 + from1to2) || dfs(jug1 + from2to1, jug2 - from2to1);
        };
        return dfs(0, 0);
    }
};