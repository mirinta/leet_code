#include <climits>
#include <functional>
#include <vector>

/**
 * There is a game dungeon comprised of n x n rooms arranged in a grid.
 *
 * You are given a 2D array fruits of size n x n, where fruits[i][j] represents the number of fruits
 * in the room (i, j). Three children will play in the game dungeon, with initial positions at the
 * corner rooms (0, 0), (0, n - 1), and (n - 1, 0).
 *
 * The children will make exactly n - 1 moves according to the following rules to reach the room
 * (n - 1, n - 1):
 *
 * The child starting from (0, 0) must move from their current room (i, j) to one of the rooms (i +
 * 1, j + 1), (i + 1, j), and (i, j + 1) if the target room exists.
 *
 * The child starting from (0, n - 1) must move from their current room (i, j) to one of the rooms
 * (i + 1, j - 1), (i + 1, j), and (i + 1, j + 1) if the target room exists.
 *
 * The child starting from (n - 1, 0) must move from their current room (i, j) to one of the rooms
 * (i - 1, j + 1), (i, j + 1), and (i + 1, j + 1) if the target room exists.
 *
 * When a child enters a room, they will collect all the fruits there. If two or more children
 * enter the same room, only one child will collect the fruits, and the room will be emptied after
 * they leave.
 *
 * Return the maximum number of fruits the children can collect from the dungeon.
 *
 * ! 2 <= n == fruits.length == fruits[i].length <= 1000
 * ! 0 <= fruits[i][j] <= 1000
 */

class Solution
{
public:
    int maxCollectedFruits(std::vector<std::vector<int>>& fruits)
    {
        // exactly n-1 moves:
        // - child at (0,0) must move along the primary diagonal
        // - child at (0,n-1) must move above the primary diagonal
        // - child at (n-1,0) must move below the primary diagonal
        const int n = fruits.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += fruits[i][i];
        }
        result += solve(fruits);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(fruits[i][j], fruits[j][i]);
            }
        }
        result += solve(fruits);
        return result;
    }

private:
    // max fruits the child can collect starting from (0,n-1)
    int solve(const std::vector<std::vector<int>>& fruits)
    {
        const int n = fruits.size();
        std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1));
        std::function<int(int, int)> dfs = [&](int x, int y) {
            if (x < 0 || x >= n || y < 0 || y >= n)
                return INT_MIN;

            if (x == n - 1 && y == n - 1)
                return 0; // already collected by the child at (0,0)

            if (y <= x)
                return INT_MIN;

            if (memo[x][y] != -1)
                return memo[x][y];

            const int case1 = dfs(x + 1, y - 1);
            const int case2 = dfs(x + 1, y);
            const int case3 = dfs(x + 1, y + 1);
            return memo[x][y] = fruits[x][y] + std::max({case1, case2, case3});
        };
        return dfs(0, n - 1);
    }
};
